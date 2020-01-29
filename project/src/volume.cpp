#include <arm_math.h>
#include <volume.h>
#include "codec.h"

int VolumeModule :: Init(int blocksize, float* input_ptr) {
    // error handling
    m_Init_ok = 0;
    if (blocksize>VOLUME_MAX_BLOCKSIZE) return 1;

    // no errors, go on..
    m_Enable = 1;
    m_InputPtr = input_ptr;
    m_Blocksize = blocksize;
    m_Volume = 1.0;

    m_ActiveCodecInputInterface = MODE_JACK_IN;

    m_GainOut = 0;
    CodecSetOutGain(m_GainOut);
    m_GainLineIn = 0;
    CodecSetLineInGain(m_GainLineIn);

    m_Init_ok = 1;

    return 0;
}


int  VolumeModule :: GetMemberValue(uint8_t MemberId)
{
	if(MemberId == ModifiableMembers::Volume)
		return ((int)(m_Volume*100));
	if(MemberId == ModifiableMembers::MicBoost)
	{
		return ((int)(m_MicBoost));
	}
	if(MemberId == ModifiableMembers::GainOut)
	{
		return ((int)(m_GainOut * 7 + 50)); // linear relationship between slider value and codec gain can roughly be modelled as x = y * 7 + 50, where x is slider gain and y is codec gain in dB
	}
	if(MemberId == ModifiableMembers::GainLineIn)
	{
		return ((int)(m_GainLineIn * 7 + 50)); // linear relationship between slider value and codec gain can roughly be modelled as x = y * 7 + 50, where x is slider gain and y is codec gain in dB
	}

	else
		return 0;
}

void VolumeModule :: SetMemberValue(uint8_t MemberId, uint8_t Value){
	if(MemberId == ModifiableMembers::Volume)
	{
		m_Volume = (float)Value;
		m_Volume /= 100;
	}
	else if(MemberId == ModifiableMembers::MicBoost)
		m_MicBoost = Value;

	else if(MemberId == ModifiableMembers::GainLineIn)
	{
		// Convert from a display value (0 to 100) to a gain value (0 to 12)
		m_GainLineIn = ConvertDisplayValueToGain(Value,GAIN_LINE_IN_MAX_VALUE, GAIN_LINE_IN_NUMBER_OF_STEPS, GAIN_LINE_IN_DECREMENT_VALUE);
		// Send value to codec
		CodecSetLineInGain(m_GainLineIn);
	}
	else if(MemberId == ModifiableMembers::GainOut)
	{
		// Convert from a display value (0 to 100) to a gain value (0 to 12)
		m_GainOut = ConvertDisplayValueToGain(Value,GAIN_OUT_MAX_VALUE, GAIN_OUT_NUMBER_OF_STEPS, GAIN_OUT_DECREMENT_VALUE);
		// Send value to codec
		CodecSetOutGain(m_GainOut);
	}
}


void VolumeModule :: Reset(){
    arm_fill_f32(0.0f, m_OutputBuffer, m_Blocksize);
}

void VolumeModule :: Apply()
{
	if(m_Enable)
	{
		arm_scale_f32(m_InputPtr, m_Volume, m_OutputBuffer, m_Blocksize);
	}
}

