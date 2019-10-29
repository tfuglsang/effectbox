#include <modules.h>
#include <arm_math.h>

int wah_init(t_wah_data *data, int blocksize, int sampling_rate, float freq_low, float freq_high, float freq_delta, float Q) {
    // error handling
    data->init_ok = 0;
    if (blocksize>WAH_MAX_BLOCKSIZE) return 1;

    // no errors, go on..
    data->blocksize = blocksize;
    data->sampling_rate = sampling_rate;

    data->freq_low = freq_low;
    data->freq_high = freq_high;
    data->freq_delta = freq_delta;
    data->freq_center = data->freq_low;
    data->Q = Q;
 
    wah_reset(data);
    data->init_ok = 1;

    return 0;
}

void wah_reset(t_wah_data *data) {
    arm_fill_f32(0.0f, data->output, data->blocksize);    
    data->yb_old = 0;
    data->yl_old = 0;    
}

void wah_apply(t_wah_data *data, float *input) {    
   
    float F1, yh, yb, yl;

    for(int i = 0; i < data->blocksize; i++)
    {
       
        F1 = 2 * sin((PI*data->freq_center) / data->sampling_rate);

        yh = input[i] - data->yl_old - data->Q*data->yb_old;

        yb = F1*yh + data->yb_old;
        yl = F1*yb + data->yl_old;
        
        data->output[i] = yb;

        data->yb_old = yb;
        data->yl_old = yl;

        data->freq_center = data->freq_center + data->freq_delta;
        if(data->freq_center > data->freq_high) // top reached! count down now!
        {
            data->freq_center = data->freq_high;
            data->freq_delta = data->freq_delta * -1;   
        }

        if (data->freq_center < data->freq_low) // bottom reached! count up now!
        {
            data->freq_center = data->freq_low;
            data->freq_delta = data->freq_delta * -1;
        }    
            
    }

}