#include <biquad.h>
#include <flanger.h>
#include <wah.h>
#include <overdrive.h>
#include <arm_math.h>

#define AUDIO_BLOCKSIZE 128*2
#define SAMPLING_RATE 48000

typedef struct {

	float VOLUME;

	int ACTIVE_CODEC_INPUT_INTERFACE;

	int CODEC_OUT_GAIN;
	int CODEC_LINE_IN_GAIN;
	int CODEC_MIC_BOOST_ENABLE;

	t_biquad_data BiquadData;
	t_flanger_data FlangerData;
	t_wah_data WahData;
	t_overdrive_data OverdriveData;

	float input[AUDIO_BLOCKSIZE];
    float output[AUDIO_BLOCKSIZE];
} t_audio_process_data;

void audio_process_apply(t_audio_process_data *data, float *input);
void audio_process_init(t_audio_process_data *data);
