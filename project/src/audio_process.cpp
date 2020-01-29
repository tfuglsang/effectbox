#include <audio_process.h>
#include "codec.h"

float InputMono[AUDIO_BLOCKSIZE / 2];

AudioProcess audioprocess;

int AudioProcess :: Init(int blocksize, float* input_ptr)
{
	this->m_InputPtr = input_ptr;
	this->m_Blocksize = blocksize;

	biquad.Init(m_Blocksize/2, InputMono);

	flanger.Init(m_Blocksize/2, biquad.GetOutputPtr());

	overdrive.Init(m_Blocksize/2, flanger.GetOutputPtr());

	wah.Init(m_Blocksize/2, overdrive.GetOutputPtr());

	volume.Init(m_Blocksize/2, wah.GetOutputPtr());

	return 0;
}

void AudioProcess :: Apply()
{
	for(int i = 0; i < m_Blocksize / 2 ; i++)
	{
		InputMono[i] = m_InputPtr[i * 2] / 2147483648;
	}

	biquad.Apply();

	flanger.Apply();

	overdrive.Apply();

	wah.Apply();

	volume.Apply();

	float* FinalOutputPtr = volume.GetOutputPtr();

	for(int i = 0; i < m_Blocksize/2; i++)
	{
		this->m_OutputBuffer[i*2] = FinalOutputPtr[i] * 2147483648;
		this->m_OutputBuffer[i*2+1] = FinalOutputPtr[i] * 2147483648;
	}

}

void AudioProcess :: Reset()
{
	biquad.Reset();

	flanger.Reset();

	overdrive.Reset();

	wah.Reset();

	volume.Reset();
}

void AudioProcessApply()
{
	audioprocess.Apply();
}
void AudioProcessInit(int blocksize, float* input_ptr)
{
	audioprocess.Init(blocksize, input_ptr);
}
float* AudioProcessGetOutputBuffer()
{
	return audioprocess.GetOutputPtr();
}
/*
void audio_process_apply(t_audio_process_data *data)
{
	for(int i = 0; i < AUDIO_BLOCKSIZE / 2 ; i++)
	{
		input_mono[i] = data->input[i * 2] / 2147483648;
	}



	float* output_ptr = volume.GetOutputPtr();
	for(int i = 0; i < AUDIO_BLOCKSIZE/2; i++)
	{
		data->output[i*2] = output_ptr[i] * 2147483648;
		data->output[i*2+1] = output_ptr[i] * 2147483648;
	}
}
*/
