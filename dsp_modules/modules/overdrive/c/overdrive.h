#define OVERDRIVE_MAX_BLOCKSIZE 256

typedef struct {    
	int enable;
	int init_ok;
    int blocksize;   
    int sampling_rate;   
    float output[WAH_MAX_BLOCKSIZE];
    float threshold;
} t_overdrive_data;

/* INTERFACE FUNCTIONS */
int overdrive_init(t_overdrive_data *data, int blocksize, int sampling_rate, float threshold);
void overdrive_reset(t_overdrive_data *data);
void overdrive_apply(t_overdrive_data *data, float *input);
