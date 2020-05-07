#include <arm_math.h>
#include <display.h>
#include <AudioModule.h>

#define BIQUAD_MAX_BLOCKSIZE 128*2
#define NUMBER_OF_BIQUADS 5
#define BIQUAD_N_COEFFS 5
#define BIQUAD_N_DLY 2

#define DEBUG_BIQUAD_ENABLE         1
#define DEBUG_BIQUAD_PASSTHROUGH    0

#ifdef __cplusplus
extern "C" {

class BiquadModule : public AudioModule
{

private:
	float m_MidLowShelfW0;
	float m_MidHighShelfW0;
	float m_BassW0;
	float m_TrebleW0;
	float m_BassGain;
	float m_MidGain;
	float m_TrebleGain;

	float m_Coeffs[5*NUMBER_OF_BIQUADS];
	float* m_BassPtr;
	float* m_MidPtr;
	float* m_TreblePtr;

	float* m_InputPtr;
	float* m_OutputPtr;
	float m_OutputBuffer[BIQUAD_MAX_BLOCKSIZE];

	int m_DlylineLength;
	float m_Dlyline[NUMBER_OF_BIQUADS*BIQUAD_N_DLY];

public:
	BiquadModule() : m_MidLowShelfW0(0),m_MidHighShelfW0(0),m_BassW0(0),m_TrebleW0(0),m_BassGain(0),m_MidGain(0),m_TrebleGain(0),
	m_BassPtr(NULL),m_MidPtr(NULL),m_TreblePtr(NULL),m_InputPtr(NULL),m_OutputPtr(NULL),m_DlylineLength(0)
	{};
	~BiquadModule(){};
	void Apply() override;
	int Init(int blocksize, float* input_ptr) override;
	void Reset() override;
	void SetMemberValue(uint8_t MemberId, uint8_t Value) override;
	int GetMemberValue(uint8_t MemberId) override;

	float* GetOutputPtr()
	{
		return m_OutputPtr;
	}

	int GainToDisplay(int gain) {
		return (100 - (-(gain)  * 5)); // gain goes from 0dB to -20dB
	}

	// Interface for accessing member values
	enum ModifiableMembers
	{
		Bass,
		Mid,
		Treble,
	};

private:
	void SetBassFilter(int value);
	void SetMidFilter(int value);
	void SetTrebleFilter(int value);
	float DoAllBiquads(float input);
};

}
#endif
