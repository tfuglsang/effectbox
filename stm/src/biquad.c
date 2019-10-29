#include "biquad.h"
#include "math.h"

#define DEBUG_BIQUAD_ENABLE         1
#define DEBUG_BIQUAD_PASSTHROUGH    0

float BIQUAD_SAMPLING_RATE = 48000;
float BIQUAD_MAX_ATTENUATION = -20;
float BIQUAD_Q = 1.0;

float BIQUAD_BASS_FREQ = 200.0;
float BIQUAD_TREBLE_FREQ = 2500.0;
float BIQUAD_MID_LS_FREQ = 2500.0;
float BIQUAD_MID_HS_FREQ = 200.0;

float biquad_mid_ls_w0;
float biquad_mid_hs_w0;
float biquad_bass_w0;
float biquad_treble_w0;

void biquad_init(t_biquad_data *data, int blocksize)
{
	biquad_bass_w0 = 2 * PI * BIQUAD_BASS_FREQ  / BIQUAD_SAMPLING_RATE;
	biquad_treble_w0 = 2 * PI * BIQUAD_TREBLE_FREQ / BIQUAD_SAMPLING_RATE;
	biquad_mid_ls_w0 = 2 * PI * BIQUAD_MID_LS_FREQ / BIQUAD_SAMPLING_RATE;
    biquad_mid_hs_w0 = 2 * PI * BIQUAD_MID_HS_FREQ / BIQUAD_SAMPLING_RATE;

    biquad_set_bass_filter(data, 100);
    biquad_set_mid_filter(data, 100);
    biquad_set_treble_filter(data, 100);

    data->dlyline_length = NUMBER_OF_BIQUADS*BIQUAD_N_DLY;
	data->blocksize = blocksize;
	data->enable = 1;

    biquad_reset(data);
}


void biquad_reset(t_biquad_data *data) {
    arm_fill_f32(0.0f, data->dlyline, data->dlyline_length);
    arm_fill_f32(0.0f, data->output, data->blocksize);
}

void biquad_apply(t_biquad_data *data, float *input) {
    float *inPtr=input;
    float *outPtr=data->output;
    float *dlylinePtr=data->dlyline;

    // If we're in passthrough pipe input to output
    if(data->enable == DEBUG_BIQUAD_PASSTHROUGH) {
    	arm_copy_f32(input, data->output, data->blocksize);
    }
    else if (data->enable == DEBUG_BIQUAD_ENABLE)
    {
	 for(int i=0; i<data->blocksize; i++) {
			dlylinePtr=data->dlyline;
			*outPtr++ = do_all_biquad(data, *inPtr++);
			dlylinePtr += NUMBER_OF_BIQUADS * BIQUAD_N_DLY;
		}
    }
}

void biquad_set_bass_filter(t_biquad_data *data, int display_value) // low shelf filter @ 200Hz, Q=1
 {
	float B0, B1, B2, A0, A1, A2, a, alpha, biquad_gain;

    // gain goes from 0dB to -20dB
    biquad_gain = BIQUAD_MAX_ATTENUATION - (display_value / (100/BIQUAD_MAX_ATTENUATION) );
    data->EQ_BASS_GAIN = biquad_gain;

    a = powf(10, biquad_gain / 40);
    alpha = sin(biquad_bass_w0) / 2 * sqrtf((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    B0 = a * ((a + 1) - (a - 1) * cos(biquad_bass_w0) + 2 * sqrtf(a) * alpha);
    B1 = 2 * a * ((a - 1) - (a + 1) * cos(biquad_bass_w0));
    B2 = a * ((a + 1) - (a - 1) * cos(biquad_bass_w0) - 2 * sqrtf(a) * alpha);
    A0 = (a + 1) + (a - 1) * cos(biquad_bass_w0) + 2 * sqrtf(a) * alpha;
    A1 = -2 * ((a - 1) + (a + 1) * cos(biquad_bass_w0));
    A2 = (a + 1) + (a - 1) * cos(biquad_bass_w0) - 2 * sqrtf(a) * alpha;

    data->biquad_coeffs[0] = B2 / A0;
    data->biquad_coeffs[1] = B1 / A0;
    data->biquad_coeffs[2] = B0 / A0;
    data->biquad_coeffs[3] = A2 / A0;
    data->biquad_coeffs[4] = A1 / A0;
 }

 void biquad_set_treble_filter(t_biquad_data *data, int display_value) // high shelf filter @ 2500Hz, Q=1
 {
	float biquad_treble_w0 = 2 * PI * BIQUAD_TREBLE_FREQ / BIQUAD_SAMPLING_RATE;
    float B0, B1, B2, A0, A1, A2, a, alpha, biquad_gain;

    // gain goes from 0dB to -20dB
    biquad_gain = BIQUAD_MAX_ATTENUATION - (display_value / (100/BIQUAD_MAX_ATTENUATION) );
    data->EQ_MID_GAIN = biquad_gain;

    a = pow(10, biquad_gain / 40);
    alpha = sin(biquad_treble_w0) / 2 *sqrt((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    B0 = a * ((a + 1) + (a - 1) * cos(biquad_treble_w0) + 2 * sqrt(a) * alpha);
    B1 = -2 * a * ((a - 1) + (a + 1) * cos(biquad_treble_w0));
    B2 = a * ((a + 1) + (a - 1) * cos(biquad_treble_w0) - 2 * sqrt(a) * alpha);
    A0 = (a + 1) - (a - 1) * cos(biquad_treble_w0) + 2 * sqrt(a) * alpha;
    A1 = 2 * ((a - 1) - (a + 1) * cos(biquad_treble_w0));
    A2 = (a + 1) - (a - 1) * cos(biquad_treble_w0) - 2 * sqrt(a) * alpha;

    data->biquad_coeffs[5] = B2 / A0;
    data->biquad_coeffs[6] = B1 / A0;
    data->biquad_coeffs[7] = B0 / A0;
    data->biquad_coeffs[8] = A2 / A0;
    data->biquad_coeffs[9] = A1 / A0;

 }

 void biquad_set_mid_filter(t_biquad_data *data, int display_value) // low shelf filter @ 2500Hz, Q=1, high shelf filter @ 200Hz, Q=1, passthrough filter with gain equal to shelf filter attenuation
 {

    float B0, B1, B2, A0, A1, A2, a, alpha, biquad_gain;

    // gain goes from 0dB to -20dB
    biquad_gain = BIQUAD_MAX_ATTENUATION - (display_value / (100/BIQUAD_MAX_ATTENUATION) );
    data->EQ_TREBLE_GAIN = biquad_gain;
    a = pow(10, biquad_gain / 40);

    // First calculate low shelf filter:

    alpha = sin(biquad_mid_ls_w0) / 2 * sqrt((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    B0 = a * ((a + 1) - (a - 1) * cos(biquad_mid_ls_w0) + 2 * sqrt(a) * alpha);
    B1 = 2 * a * ((a - 1) - (a + 1) * cos(biquad_mid_ls_w0));
    B2 = a * ((a + 1) - (a - 1) * cos(biquad_mid_ls_w0) - 2 * sqrt(a) * alpha);
    A0 = (a + 1) + (a - 1) * cos(biquad_mid_ls_w0) + 2 * sqrt(a) * alpha;
    A1 = -2 * ((a - 1) + (a + 1) * cos(biquad_mid_ls_w0));
    A2 = (a + 1) + (a - 1) * cos(biquad_mid_ls_w0) - 2 * sqrt(a) * alpha;

    data->biquad_coeffs[10] = B2 / A0;
    data->biquad_coeffs[11] = B1 / A0;
    data->biquad_coeffs[12] = B0 / A0;
    data->biquad_coeffs[13] = A2 / A0;
    data->biquad_coeffs[14] = A1 / A0;

    // Then high shelf

    alpha = sin(biquad_mid_hs_w0) / 2 * sqrt((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    B0 = a * ((a + 1) + (a - 1) * cos(biquad_mid_hs_w0) + 2 * sqrt(a) * alpha);
    B1 = -2 * a * ((a - 1) + (a + 1) * cos(biquad_mid_hs_w0));
    B2 = a * ((a + 1) + (a - 1) * cos(biquad_mid_hs_w0) - 2 * sqrt(a) * alpha);
    A0 = (a + 1) - (a - 1) * cos(biquad_mid_hs_w0) + 2 * sqrt(a) * alpha;
    A1 = 2 * ((a - 1) - (a + 1) * cos(biquad_mid_hs_w0));
    A2 = (a + 1) - (a - 1) * cos(biquad_mid_hs_w0) - 2 * sqrt(a) * alpha;

    B0 = B0 / A0;
    B1 = B1 / A0;
    B2 = B2 / A0;
    A1 = A1 / A0;
    A2 = A2 / A0;
    A0 = 1;

    data->biquad_coeffs[15] = B2 / A0;
    data->biquad_coeffs[16] = B1 / A0;
    data->biquad_coeffs[17] = B0 / A0;
    data->biquad_coeffs[18] = A2 / A0;
    data->biquad_coeffs[19] = A1 / A0;

    // Last the passthrough filter
    B0 = (pow(10, (-biquad_gain / 20)));
    B1 = 0;
    B2 = 0;
    A1 = 0;
    A2 = 0;
    A0 = 1.0;

    data->biquad_coeffs[20] = B2 / A0;
    data->biquad_coeffs[21] = B1 / A0;
    data->biquad_coeffs[22] = B0 / A0;
    data->biquad_coeffs[23] = A2 / A0;
    data->biquad_coeffs[24] = A1 / A0;

 }

float do_all_biquad(t_biquad_data *data, float in){
    /*
    / b0 = coeffs[2]
    / b1 = coeffs[1]
    / b2 = coeffs[0]
    / a1 = coeffs[4]
    / a2 = coeffs[3]
    / Filter implementation is transposed direct form II
    / y(n) = b0*x(n) + s1(n-1)
    / s1(n) = s2(n-1) + b1*x(n) - a1*y(n)
    / s2(n) = b2*x(n) - a2*y(n)
    */
	float *dlyline_ptr = data->dlyline;

	float y, x;
	x = in;
    for(int j=0;j<NUMBER_OF_BIQUADS;j++) {
    	y = data->biquad_coeffs[j*BIQUAD_N_COEFFS + 2]*x + dlyline_ptr[0];
    	dlyline_ptr[0] = dlyline_ptr[1] + data->biquad_coeffs[j*BIQUAD_N_COEFFS + 1]*x - data->biquad_coeffs[j*BIQUAD_N_COEFFS + 4]*y;
    	dlyline_ptr[1] = data->biquad_coeffs[j*BIQUAD_N_COEFFS + 0]*x - data->biquad_coeffs[j*BIQUAD_N_COEFFS + 3]*y;
    	dlyline_ptr += BIQUAD_N_DLY;
    	x = y;
    }
    return y;
}
