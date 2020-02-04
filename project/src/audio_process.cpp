#include <audio_process.h>
#include "codec.h"

/*
DTCM-RAM on TCM interface is mapped at the address 0x2000 0000 and accessible
by Cortex®-M7, and by MDMA through AHBS slave bus of the Cortex®-M7 CPU. The
DTCM-RAM can be used as read-write segment to host critical real-time data (such as
stack and heap) for application running on Cortex®-M7 CPU.
*/
#define __ATTR_RAM_DTCM __attribute__ ((section(".DTCMRAM"))) __attribute__ ((aligned (4)))

AudioProcess audioprocess __ATTR_RAM_DTCM; // Use TCM ram for storing audio modules:

int AudioProcess :: Init(int blocksize, float* input_ptr)
{
	this->m_InputPtr = input_ptr;
	this->m_Blocksize = blocksize;

	biquad.Init(m_Blocksize, this->m_InputPtr);

	flanger.Init(m_Blocksize, biquad.GetOutputPtr());

	overdrive.Init(m_Blocksize, flanger.GetOutputPtr());

	wah.Init(m_Blocksize, overdrive.GetOutputPtr());

	volume.Init(m_Blocksize, wah.GetOutputPtr());

	return 0;
}

void AudioProcess :: Apply()
{
	biquad.Apply();

	flanger.Apply();

	overdrive.Apply();

	wah.Apply();

	volume.Apply();

	float* FinalOutputPtr = volume.GetOutputPtr();

	for(int i = 0; i < m_Blocksize; i++)
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

