#include <modules.h>
#include <arm_math.h>
#include <stdlib.h>

int overdrive_init(t_overdrive_data *data, int blocksize, int sampling_rate, float threshold) {
    // error handling
    data->init_ok = 0;
    if (blocksize>OVERDRIVE_MAX_BLOCKSIZE) return 1;

    // no errors, go on..
    data->blocksize = blocksize;
    data->sampling_rate = sampling_rate;
    data->threshold = threshold;
 
    overdrive_reset(data);
    data->init_ok = 1;

    return 0;
}

void overdrive_reset(t_overdrive_data *data) {
    arm_fill_f32(0.0f, data->output, data->blocksize);        
}

void overdrive_apply(t_overdrive_data *data, float *input) {   
    for(int i = 0; i < data->blocksize; i++)
    {
       
        if( abs(input[i])< data->threshold)
        {
            data->output[i]=2*input[i];
        }

        if (abs(input[i])>=data->threshold)
        {
            if (input[i]> 0)
            {
                data->output[i]= (3 -  pow(2-input[i]*3, 2) ) / 3;
            }
            
            if (input[i]< 0)
            {
                data->output[i] = - (3 - pow( (2 - abs( input[i]*3 ) ), 2)) / 3;
            }                   
        }            
             
        if (abs(input[i])>2*data->threshold)
        {
            if (input[i]> 0)
            {
                data->output[i] =1;
            }                    
            if (input[i]< 0)
            {
                data->output[i] =-1;
            }            
        }   
    }
}