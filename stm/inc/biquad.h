#include <arm_math.h>

#define BIQUAD_MAX_BLOCKSIZE 128*2
#define NUMBER_OF_BIQUADS 5
#define BIQUAD_N_COEFFS 5
#define BIQUAD_N_DLY 2

typedef struct {
	int enable;
	int init_ok;
    int blocksize;

    float EQ_BASS_GAIN;
    float EQ_MID_GAIN;
    float EQ_TREBLE_GAIN;

	float biquad_coeffs[5*NUMBER_OF_BIQUADS];
    float output[BIQUAD_MAX_BLOCKSIZE];

    int dlyline_length;
    float dlyline[NUMBER_OF_BIQUADS*BIQUAD_N_DLY];
} t_biquad_data;

/* INTERFACE FUNCTIONS */
void biquad_init(t_biquad_data *data, int blocksize);
void biquad_reset(t_biquad_data *data);
void biquad_apply(t_biquad_data *data, float *input);
float do_all_biquad(t_biquad_data *data, float x);

void biquad_set_bass_filter(t_biquad_data *data, int display_value);
void biquad_set_treble_filter(t_biquad_data *data, int display_value);
void biquad_set_mid_filter(t_biquad_data *data, int display_value);

