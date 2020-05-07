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

int AudioProcess :: AddModule(AudioModule* module)
{
	this->modules[this->NumberOfModules++] = module;
	return 1;
}

int AudioProcess :: Init(int blocksize, float* input_ptr)
{
	this->m_InputPtr = input_ptr;
	this->m_Blocksize = blocksize;

	AddModule(&biquad);
	AddModule(&flanger);
	AddModule(&overdrive);
	AddModule(&wah);
	AddModule(&volume);
	AddModule(&reverb);

	this->modules[0]->Init(m_Blocksize, this->m_InputPtr);
	for(int i = 1; i<NumberOfModules; i++)
	{
		this->modules[i]->Init(m_Blocksize, modules[i-1]->GetOutputPtr());
	}

	return 1;
}
float OutputBuffer[256];
void AudioProcess :: Apply()
{
	int i = 0;
	for(i = 0; i<NumberOfModules; i++)
	{
		this->modules[i]->Apply();
	}

	float* FinalOutputPtr = this->modules[NumberOfModules-1]->GetOutputPtr();
		for(int i = 0; i < m_Blocksize; i++)
	{
		this->m_OutputBuffer[i*2] = FinalOutputPtr[i] * 2147483648;
		this->m_OutputBuffer[i*2+1] = FinalOutputPtr[i] * 2147483648;
	}
}

void AudioProcess :: Reset()
{
	for(int i = 0; i<NumberOfModules; i++)
	{
		this->modules[i]->Reset();
	}
}


// Wrapper functions for C++
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

