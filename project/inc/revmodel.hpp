// Reverb model declaration
//
// Written by Jezar at Dreampoint, June 2000
// http://www.dreampoint.co.uk
// This code is public domain

#ifndef _revmodel_
#define _revmodel_

#include <arm_math.h>
#include <AudioModule.h>
#include "comb.hpp"
#include "allpass.hpp"

#define REVERB_MAX_BLOCKSIZE 128*2

#ifdef __cplusplus
extern "C" {

const int	numcombs		= 8;
const int	numallpasses	= 4;
const float	fixedgain		= 0.015f;
const float scalewet		= 3;
const float scaledry		= 2;
const float scaledamp		= 0.4f;
const float scaleroom		= 0.28f;
const float offsetroom		= 0.7f;
const float initialroom		= 0.5f;
const float initialdamp		= 0.5f;
const float initialwet		= 1/scalewet;
const float initialdry		= 0;
const float initialwidth	= 1;

// These values assume 44.1KHz sample rate
// they will probably be OK for 48KHz sample rate
// but would need scaling for 96KHz (or other) sample rates.
// The values were obtained by listening tests.
const int combtuningL1		= 1116;
const int combtuningL2		= 1188;
const int combtuningL3		= 1277;
const int combtuningL4		= 1356;
const int combtuningL5		= 1422;
const int combtuningL6		= 1491;
const int combtuningL7		= 1557;
const int combtuningL8		= 1617;
const int allpasstuningL1	= 556;
const int allpasstuningL2	= 441;
const int allpasstuningL3	= 341;
const int allpasstuningL4	= 225;

class ReverbModule : public AudioModule{
public:

			ReverbModule() {};
			~ReverbModule(){};
			void Apply();
			int Init(int blocksize, float* input_ptr);
			void Reset();
			void SetMemberValue(uint8_t MemberId, uint8_t Value);
			int GetMemberValue(uint8_t MemberId);

			float* GetOutputPtr()
			{
				return m_OutputBuffer;
			}

			int m_Init_ok;
			int m_Enable;
			int m_Blocksize;
			float* m_InputPtr;
			float m_OutputBuffer[REVERB_MAX_BLOCKSIZE];

			// Interface for accessing member values
			enum ModifiableMembers
			{
				Enable,
				Roomsize,
				Damp,
				Wet,
				Dry,
				Width
			};

private:
			void UpdateValues();
private:
	float	m_gain;
	float	m_roomsize,m_roomsize1;
	float	m_damp,m_damp1;
	float	m_wet,m_wet1,m_wet2;
	float	m_dry;
	float	m_width;

	// The following are all declared inline 
	// to remove the need for dynamic allocation
	// with its subsequent error-checking messiness

	// Comb filters
	comb	combL[numcombs];
	comb	combR[numcombs];

	// Allpass filters
	allpass	allpassL[numallpasses];
	allpass	allpassR[numallpasses];

	// Buffers for the combs
	float	bufcombL1[combtuningL1];
	float	bufcombL2[combtuningL2];
	float	bufcombL3[combtuningL3];
	float	bufcombL4[combtuningL4];
	float	bufcombL5[combtuningL5];
	float	bufcombL6[combtuningL6];
	float	bufcombL7[combtuningL7];
	float	bufcombL8[combtuningL8];

	// Buffers for the allpasses
	float	bufallpassL1[allpasstuningL1];
	float	bufallpassL2[allpasstuningL2];
	float	bufallpassL3[allpasstuningL3];
	float	bufallpassL4[allpasstuningL4];
};

}
#endif // __cplusplus

#endif//_revmodel_

//ends
