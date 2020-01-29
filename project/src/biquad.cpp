#include "biquad.h"
#include "math.h"

float BIQUAD_SAMPLING_RATE = 48000;
float BIQUAD_MAX_ATTENUATION = -20;
float BIQUAD_Q = 1.0;

float BIQUAD_BASS_FREQ = 200.0;
float BIQUAD_TREBLE_FREQ = 2500.0;
float BIQUAD_MID_LS_FREQ = 2500.0;
float BIQUAD_MID_HS_FREQ = 200.0;

float BassW0Initial = 2 * PI * BIQUAD_BASS_FREQ  / BIQUAD_SAMPLING_RATE;
float TrebleW0Initial = 2 * PI * BIQUAD_TREBLE_FREQ  / BIQUAD_SAMPLING_RATE;
float MidLowShelfW0Initial = 2 * PI * BIQUAD_MID_LS_FREQ  / BIQUAD_SAMPLING_RATE;
float MidHighShelfW0Initial = 2 * PI * BIQUAD_MID_HS_FREQ  / BIQUAD_SAMPLING_RATE;

#ifdef __cplusplus
extern "C" {

// member function defined outside class definition
void BiquadModule :: Apply()
{
	float *inPtr 		= m_InputPtr;
	float *outPtr 		= m_OutputPtr;
	float *dlylinePtr 	= m_Dlyline;

	// If we're in passthrough pipe input to output
	if(m_Enable == DEBUG_BIQUAD_PASSTHROUGH) {
		arm_copy_f32(m_InputPtr, m_OutputBuffer, m_Blocksize);
	}
	else if (m_Enable == DEBUG_BIQUAD_ENABLE)
	{
	 for(int i=0; i<m_Blocksize; i++) {
			dlylinePtr = m_Dlyline;
			*outPtr++ = DoAllBiquads(*inPtr++);
			dlylinePtr += NUMBER_OF_BIQUADS * BIQUAD_N_DLY;
		}
	}
}

float BiquadModule :: DoAllBiquads(float input)
{
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
	float *dlyline_ptr = m_Dlyline;

	float output;

    for(int j=0;j<NUMBER_OF_BIQUADS;j++) {
    	output = m_Coeffs[j*BIQUAD_N_COEFFS + 2]*input + dlyline_ptr[0];
    	dlyline_ptr[0] = dlyline_ptr[1] + m_Coeffs[j*BIQUAD_N_COEFFS + 1]*input - m_Coeffs[j*BIQUAD_N_COEFFS + 4]*output;
    	dlyline_ptr[1] = m_Coeffs[j*BIQUAD_N_COEFFS + 0]*input - m_Coeffs[j*BIQUAD_N_COEFFS + 3]*output;
    	dlyline_ptr += BIQUAD_N_DLY;
    	input = output;
    }
    return output;
}

void BiquadModule :: Init(int blocksize, float* input_ptr)
{
	m_InputPtr = input_ptr;
	m_OutputPtr = m_OutputBuffer;

	m_BassW0 = BassW0Initial;
	m_TrebleW0 = TrebleW0Initial;
	m_MidLowShelfW0 = MidLowShelfW0Initial;
	m_MidHighShelfW0 = MidHighShelfW0Initial;

	m_BassPtr 	= &m_Coeffs[0];
	m_TreblePtr	= &m_Coeffs[5];
	m_MidPtr 	= &m_Coeffs[10];

    m_DlylineLength = NUMBER_OF_BIQUADS*BIQUAD_N_DLY;
    m_Blocksize = blocksize;
    m_Enable = 1;

    SetBassFilter(100);
    SetMidFilter(100);
    SetTrebleFilter(100);

    Reset();
}

void BiquadModule :: Reset()
{
    arm_fill_f32(0.0f, m_Dlyline, m_DlylineLength);
    arm_fill_f32(0.0f, m_OutputPtr, m_Blocksize);
}

int BiquadModule :: GetMemberValue(uint8_t MemberId){
	if(MemberId == ModifiableMembers::Bass)
		return GainToDisplay(m_BassGain);
	else if(MemberId == ModifiableMembers::Mid)
		return GainToDisplay(m_MidGain);
	else if(MemberId == ModifiableMembers::Treble)
		return GainToDisplay(m_TrebleGain);
	else
		return 0;
}

void BiquadModule :: SetMemberValue(uint8_t MemberId, uint8_t Value){

	switch(MemberId)
	{
	case ModifiableMembers::Bass:
		SetBassFilter(Value);
		break;

	case ModifiableMembers::Mid:
		SetMidFilter(Value);
		break;

	case ModifiableMembers::Treble:
		SetTrebleFilter(Value);
		break;
	}
}

void BiquadModule :: SetBassFilter(int display_value)
{
	float B0, B1, B2, A0, A1, A2, a, alpha, biquad_gain;

    // gain goes from 0dB to -20dB
    biquad_gain = BIQUAD_MAX_ATTENUATION - (display_value / (100/BIQUAD_MAX_ATTENUATION) );
    m_BassGain = biquad_gain;

    a = powf(10, biquad_gain / 40);
    alpha = sin(m_BassW0) / 2 * sqrtf((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    float cos_tmp = cos(m_BassW0);
    float sqrt_tmp = sqrtf(a);
    B0 = a * ((a + 1) - (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha);
    B1 = 2 * a * ((a - 1) - (a + 1) * cos_tmp);
    B2 = a * ((a + 1) - (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha);
    A0 = (a + 1) + (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha;
    A1 = -2 * ((a - 1) + (a + 1) * cos_tmp);
    A2 = (a + 1) + (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha;

    m_BassPtr[0] = B2 / A0;
    m_BassPtr[1] = B1 / A0;
    m_BassPtr[2] = B0 / A0;
    m_BassPtr[3] = A2 / A0;
    m_BassPtr[4] = A1 / A0;
}

void BiquadModule :: SetTrebleFilter(int display_value)
{
	float m_TrebleW0 = 2 * PI * BIQUAD_TREBLE_FREQ / BIQUAD_SAMPLING_RATE;
	float B0, B1, B2, A0, A1, A2, a, alpha, biquad_gain;

	// gain goes from 0dB to -20dB
	biquad_gain = BIQUAD_MAX_ATTENUATION - (display_value / (100/BIQUAD_MAX_ATTENUATION) );
	m_TrebleGain = biquad_gain;

	a = pow(10, biquad_gain / 40);
	alpha = sin(m_TrebleW0) / 2 *sqrt((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    float cos_tmp = cos(m_TrebleW0);
    float sqrt_tmp = sqrtf(a);
	B0 = a * ((a + 1) + (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha);
	B1 = -2 * a * ((a - 1) + (a + 1) * cos_tmp);
	B2 = a * ((a + 1) + (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha);
	A0 = (a + 1) - (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha;
	A1 = 2 * ((a - 1) - (a + 1) * cos_tmp);
	A2 = (a + 1) - (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha;

	m_TreblePtr[0] = B2 / A0;
	m_TreblePtr[1] = B1 / A0;
	m_TreblePtr[2] = B0 / A0;
	m_TreblePtr[3] = A2 / A0;
	m_TreblePtr[4] = A1 / A0;

}

void BiquadModule :: SetMidFilter(int display_value)
{
    float B0, B1, B2, A0, A1, A2, a, alpha, biquad_gain;

    // gain goes from 0dB to -20dB
    biquad_gain = BIQUAD_MAX_ATTENUATION - (display_value / (100/BIQUAD_MAX_ATTENUATION) );
    m_MidGain = biquad_gain;

    a = pow(10, biquad_gain / 40);

    // First calculate low shelf filter:

    alpha = sin(m_MidLowShelfW0) / 2 * sqrt((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    float cos_tmp = cos(m_MidLowShelfW0);
    float sqrt_tmp = sqrtf(a);
    B0 = a * ((a + 1) - (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha);
    B1 = 2 * a * ((a - 1) - (a + 1) * cos_tmp);
    B2 = a * ((a + 1) - (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha);
    A0 = (a + 1) + (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha;
    A1 = -2 * ((a - 1) + (a + 1) * cos_tmp);
    A2 = (a + 1) + (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha;

    m_MidPtr[0] = B2 / A0;
    m_MidPtr[1] = B1 / A0;
    m_MidPtr[2] = B0 / A0;
    m_MidPtr[3] = A2 / A0;
    m_MidPtr[4] = A1 / A0;

    // Then high shelf

    alpha = sin(m_MidHighShelfW0) / 2 * sqrt((a + 1 / a) * (1 / BIQUAD_Q - 1) + 2);

    cos_tmp = cos(m_MidHighShelfW0);
    sqrt_tmp = sqrtf(a);
    B0 = a * ((a + 1) + (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha);
    B1 = -2 * a * ((a - 1) + (a + 1) * cos_tmp);
    B2 = a * ((a + 1) + (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha);
    A0 = (a + 1) - (a - 1) * cos_tmp + 2 * sqrt_tmp * alpha;
    A1 = 2 * ((a - 1) - (a + 1) * cos_tmp);
    A2 = (a + 1) - (a - 1) * cos_tmp - 2 * sqrt_tmp * alpha;

    B0 = B0 / A0;
    B1 = B1 / A0;
    B2 = B2 / A0;
    A1 = A1 / A0;
    A2 = A2 / A0;
    A0 = 1;

    m_MidPtr[5] = B2 / A0;
    m_MidPtr[6] = B1 / A0;
    m_MidPtr[7] = B0 / A0;
    m_MidPtr[8] = A2 / A0;
    m_MidPtr[9] = A1 / A0;

    // Last the passthrough filter
    B0 = (pow(10, (-biquad_gain / 20)));
    B1 = 0;
    B2 = 0;
    A1 = 0;
    A2 = 0;
    A0 = 1.0;

    m_MidPtr[10] = B2 / A0;
    m_MidPtr[11] = B1 / A0;
    m_MidPtr[12] = B0 / A0;
    m_MidPtr[13] = A2 / A0;
    m_MidPtr[14] = A1 / A0;
}

}
#endif
