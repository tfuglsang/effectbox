#define WAH_MAX_BLOCKSIZE 256

typedef struct {    
	int enable;
	int init_ok;
    int blocksize;   
    int sampling_rate;   
    float output[WAH_MAX_BLOCKSIZE];
    float yb_old;
    float yl_old;
    float freq_low;
    float freq_high;
    float freq_delta;
    float freq_center;
    float Q;
} t_wah_data;

/* INTERFACE FUNCTIONS */
int wah_init(t_wah_data *data, int blocksize, int sampling_rate, float freq_low, float freq_high, float freq_delta, float Q);
void wah_reset(t_wah_data *data);
void wah_apply(t_wah_data *data, float *input);
