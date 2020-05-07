#include "revmodel.hpp"

void ReverbModule::Reset()
{
	for (int i=0;i<numcombs;i++)
	{
		combL[i].Reset();
		combR[i].Reset();
	}
	for (int i=0;i<numallpasses;i++)
	{
		allpassL[i].Reset();
		allpassR[i].Reset();
	}
}

int ReverbModule :: Init(int blocksize, float* input_ptr) {
    // error handling
    m_Init_ok = 0;
    if (blocksize>REVERB_MAX_BLOCKSIZE) return 1;

    // no errors, go on..
    m_Enable = 1;
    m_InputPtr = input_ptr;
    m_Blocksize = blocksize;
	// Tie the components to their buffers
	combL[0].setbuffer(bufcombL1,combtuningL1);
	combL[1].setbuffer(bufcombL2,combtuningL2);
	combL[2].setbuffer(bufcombL3,combtuningL3);
	combL[3].setbuffer(bufcombL4,combtuningL4);
	combL[4].setbuffer(bufcombL5,combtuningL5);
	combL[5].setbuffer(bufcombL6,combtuningL6);
	combL[6].setbuffer(bufcombL7,combtuningL7);
	combL[7].setbuffer(bufcombL8,combtuningL8);
	allpassL[0].setbuffer(bufallpassL1,allpasstuningL1);
	allpassL[1].setbuffer(bufallpassL2,allpasstuningL2);
	allpassL[2].setbuffer(bufallpassL3,allpasstuningL3);
	allpassL[3].setbuffer(bufallpassL4,allpasstuningL4);

	// Set default values
	allpassL[0].setfeedback(0.5f);
	allpassL[1].setfeedback(0.5f);
	allpassL[2].setfeedback(0.5f);
	allpassL[3].setfeedback(0.5f);
	m_wet = initialwet;
	m_roomsize = initialroom;
	m_dry = initialdry;
	m_damp = initialdamp;
	m_width = initialwidth;

	Reset();

    return m_Init_ok;
}

int  ReverbModule :: GetMemberValue(uint8_t MemberId)
{
	if(MemberId == ModifiableMembers::Enable)
	{
		return m_Enable;
	}
	if(MemberId == ModifiableMembers::Roomsize)
		return (int)((m_roomsize-offsetroom)/scaleroom);
	if(MemberId == ModifiableMembers::Damp)
	{
		return (int)(m_damp/scaledamp);
	}
	if(MemberId == ModifiableMembers::Wet)
	{
		return (int)(m_wet/scalewet);
	}
	if(MemberId == ModifiableMembers::Dry)
	{
		return ((int)(m_dry/scaledry));
	}
	if(MemberId == ModifiableMembers::Width)
	{
		return ((int)(m_width));
	}

	else
		return 0;
}

void ReverbModule :: SetMemberValue(uint8_t MemberId, uint8_t Value){

	if(MemberId == ModifiableMembers::Enable)
	{
		m_Enable = Value;
	}
	if(MemberId == ModifiableMembers::Roomsize)
	{
		m_roomsize = ((float)Value*scaleroom) + offsetroom;
	}
	else if(MemberId == ModifiableMembers::Damp)
	{
		m_damp = Value*scaledamp;
	}
	else if(MemberId == ModifiableMembers::Wet)
	{
		m_wet = Value*scalewet;
	}
	else if(MemberId == ModifiableMembers::Dry)
	{
		m_dry = Value*scaledry;
	}
	else if(MemberId == ModifiableMembers::Width)
	{
		m_width = Value;
	}
	UpdateValues();
}

void ReverbModule::Apply()
{
	float *outPtr 		= m_OutputBuffer;
	float *inPtr 		= m_InputPtr;
	if(m_Enable)
	{
		float out,input;

		while(m_Blocksize-- > 0)
		{
			out = 0;
			input = (*inPtr) * m_gain;

			// Accumulate comb filters in parallel
			for(int i=0; i<numcombs; i++)
			{
				out += combL[i].process(input);
			}

			// Feed through allpasses in series
			for(int i=0; i<numallpasses; i++)
			{
				out = allpassL[i].process(out);
			}

			// Calculate output REPLACING anything already there
			*outPtr = out*m_wet1 + input*m_dry;

			// Increment sample pointers, allowing for interleave (if any)
			inPtr ++;
			outPtr ++;
		}
	}
}

void ReverbModule::UpdateValues()
{
// Recalculate internal values after parameter change
	int i;

	m_wet1 = m_wet*(m_width/2 + 0.5f);
	m_wet2 = m_wet*((1-m_width)/2);

	m_roomsize1 = m_roomsize;
	m_damp1 = m_damp;
	m_gain = fixedgain;

	for(i=0; i<numcombs; i++)
	{
		combL[i].setfeedback(m_roomsize1);
		combR[i].setfeedback(m_roomsize1);
	}

	for(i=0; i<numcombs; i++)
	{
		combL[i].setdamp(m_damp1);
		combR[i].setdamp(m_damp1);
	}
}
