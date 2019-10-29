#define FLANGER_MAX_BLOCKSIZE 128*2
#define FLANGER_DELAYLINE_SIZE 4000

#define FLANGER_ENABLE         1
#define FLANGER_PASSTHROUGH    0

typedef struct {    
	int enable;
	int init_ok;
    int blocksize;
    float delay_offset;
    int max_delayunits;
    int sampling_rate;
    int pi_cnt;
    int pi_reset;
    float sin_term;
    float sin_inc;    
    float rate;
    float output[FLANGER_MAX_BLOCKSIZE];
    float delay_buffer[FLANGER_DELAYLINE_SIZE];
    int wr_ptr;
    int time_shift_idx;
    int n;
} t_flanger_data;

/* INTERFACE FUNCTIONS */
int flanger_init(t_flanger_data *data, int blocksize, int sampling_rate);
int flanger_set_parameters(t_flanger_data *data);
void flanger_reset(t_flanger_data *data);
void flanger_apply(t_flanger_data *data, float *input);
