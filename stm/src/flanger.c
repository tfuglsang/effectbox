#include <flanger.h>
#include <arm_math.h>

float FLANGER_RATE_INIT = 0.9;
float FLANGER_DELAY_INIT = 0.01;

int flanger_init(t_flanger_data *data, int blocksize, int sampling_rate) {
    // error handling
    data->init_ok = 0;
    if (blocksize>FLANGER_MAX_BLOCKSIZE) return 1;

    // no errors, go on..
    //data->enable = 1;
    data->blocksize = blocksize;
    data->sampling_rate = sampling_rate;
    data->delay_offset = FLANGER_DELAY_INIT / 2;
    data->max_delayunits = ceil(0.015*data->sampling_rate);
    data->rate = FLANGER_RATE_INIT;
    data->sin_inc = (data->rate/data->sampling_rate)*2*PI;  
    float tmp = floor( 1 / (data->rate / sampling_rate));
    data->pi_reset = (int)tmp; // (2*PI)/data->sin_inc;
   
    flanger_reset(data);
    data->init_ok = 1;

    return 0;
}

int flanger_set_parameters(t_flanger_data *data){
    data->sin_inc = (data->rate/data->sampling_rate)*2*PI;
    float tmp = floor( 1 / (data->rate / data->sampling_rate));
    data->pi_reset = (int)tmp; // (2*PI)/data->sin_inc;
    return 0;
}

void flanger_reset(t_flanger_data *data) {
    arm_fill_f32(0.0f, data->output, data->blocksize);
    arm_fill_f32(0.0f, data->delay_buffer, FLANGER_DELAYLINE_SIZE);

    data->sin_term = 0;
    data->pi_cnt = 0;
    data->wr_ptr = 0;
}

void flanger_apply(t_flanger_data *data, float *input) {

	if(data->enable == FLANGER_PASSTHROUGH)
	{
		arm_copy_f32(input, data->output, data->blocksize);
	}
	else if(data->enable == FLANGER_ENABLE)
	{
		// check if new input block fits in delay_buffer
		int space_in_buffer = FLANGER_DELAYLINE_SIZE - (data->wr_ptr + data->blocksize);

		if(space_in_buffer < 0){ // data doesnt fit
			// first write the amount that fits
			int amount_to_copy = data->blocksize + space_in_buffer;
			arm_copy_f32(input, &data->delay_buffer[data->wr_ptr], amount_to_copy); //data->delay_buffer(data->wr_ptr:obj.wr_ptr+obj.input_blocksize+space - 1) = input_block(1:obj.input_blocksize+space);

			// then rewind wr pointer and write the rest of the block
			data->wr_ptr = 0;
			arm_copy_f32(input + amount_to_copy, &data->delay_buffer[data->wr_ptr], data->blocksize - amount_to_copy);
			// obj.delay_buffer(obj.wr_ptr:obj.wr_ptr - space -1) = input_block(obj.input_blocksize+space + 1:obj.input_blocksize);
			data->wr_ptr = data->wr_ptr - space_in_buffer;
		}
		else
		{
			// if it fits, append it
			arm_copy_f32(input, &data->delay_buffer[data->wr_ptr], data->blocksize);
			data->wr_ptr = data->wr_ptr + data->blocksize;

			if(data->wr_ptr == FLANGER_DELAYLINE_SIZE)
			{
				data->wr_ptr = 0;
			}
		}


		for(int i = 0; i < data->blocksize; i++)
		{
			data->sin_term = data->sin_term + data->sin_inc;
			data->pi_cnt++;
			if(data->pi_cnt >= data->pi_reset)
			{
				data->pi_cnt = 0;
				data->sin_term = 0;
			}

			float time_delay = data->delay_offset * sin(data->sin_term)+data->delay_offset;

			data->n = (int)ceil(data->sampling_rate*time_delay);
			int time_shift_idx = data->wr_ptr - data->n + i - data->blocksize; // idx of delayed sample with reference to current write pointer

			if (time_shift_idx < 0) // if idx is under lower limit, wrap backwards to end of buffer
			{
				time_shift_idx = FLANGER_DELAYLINE_SIZE + time_shift_idx;
			}
			if(time_shift_idx >= FLANGER_DELAYLINE_SIZE) // if idx is larger than length of delaybuffer, start fresh from beginning of buffer
			{
				time_shift_idx = time_shift_idx - FLANGER_DELAYLINE_SIZE;
			}

			data->time_shift_idx = time_shift_idx;
			data->output[i] = input[i] +  data->delay_buffer[time_shift_idx];
		}
    }
}
