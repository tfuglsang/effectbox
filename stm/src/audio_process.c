#include "audio_process.h"
#include "codec.h"

float WAH_FREQ_LOW = 1000;
float WAH_FREQ_HIGH = 2000;
float WAH_FREQ_DELTA = 0.05;
float WAH_Q = 0.1;

float OVERDRIVE_THRESHOLD = 0.3 * pow(31,2);

float input_mono[AUDIO_BLOCKSIZE / 2];
void audio_process_apply(t_audio_process_data *data, float *input)
{
/*
	for(int i = 0; i < AUDIO_BLOCKSIZE; i++)
	{
		input[i] = input[i] / 2147483648;
	}
	*/
	for(int i = 0; i < AUDIO_BLOCKSIZE / 2 ; i++)
	{
		input_mono[i] = input[i * 2] / 2147483648;
	}

	flanger_apply(&data->FlangerData, input_mono);

	wah_apply(&data->WahData, data->FlangerData.output);

	overdrive_apply(&data->OverdriveData, data->WahData.output);

	biquad_apply(&data->BiquadData, data->OverdriveData.output);
	//biquad_apply(&data->BiquadData, data->WahData.output);

	arm_scale_f32(data->BiquadData.output, 2147483648, data->BiquadData.output, AUDIO_BLOCKSIZE/2);

	for(int i = 0; i < AUDIO_BLOCKSIZE/2; i++)
	{
		input[i*2] = data->BiquadData.output[i];
		input[i*2+1] = data->BiquadData.output[i];
	}

	arm_scale_f32(input, data->VOLUME, data->output, AUDIO_BLOCKSIZE);
}

void audio_process_init(t_audio_process_data *data)
{
	data->VOLUME = 0.5;
	data->CODEC_MIC_BOOST_ENABLE = 0;
	data->CODEC_OUT_GAIN = 0;
	data->CODEC_LINE_IN_GAIN = 0;
	data->ACTIVE_CODEC_INPUT_INTERFACE = MODE_LINE_IN; //MODE_JACK_IN; MODE_LINE_IN

	flanger_init(&data->FlangerData, AUDIO_BLOCKSIZE/2, SAMPLING_RATE);
	biquad_init(&data->BiquadData, AUDIO_BLOCKSIZE/2);
	wah_init(&data->WahData, AUDIO_BLOCKSIZE/2, SAMPLING_RATE, WAH_FREQ_LOW, WAH_FREQ_HIGH, WAH_FREQ_DELTA, WAH_Q);
	overdrive_init(&data->OverdriveData, AUDIO_BLOCKSIZE/2, OVERDRIVE_THRESHOLD);

}

