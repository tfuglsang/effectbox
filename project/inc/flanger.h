#include <arm_math.h>
#include <display.h>
#include <AudioModule.h>

#define FLANGER_SAMPLING_RATE 48000
#define FLANGER_MAX_BLOCKSIZE 128*2
#define FLANGER_DELAYLINE_SIZE 4000

/* INTERFACE FUNCTIONS */
#ifdef __cplusplus
extern "C" {

class FlangerModule : public AudioModule{
private:
	int m_MaxDelayunits;
	int m_SamplingRate;
	int m_PiCnt;
	int m_PiReset;
	float m_SinTerm;
	float m_SinInc;

	float* m_InputPtr;
	float m_OutputBuffer[FLANGER_MAX_BLOCKSIZE];
	float m_DelayBuffer[FLANGER_DELAYLINE_SIZE];
	int m_WrPtr;
	int m_TimeShiftIdx;
	int m_N;
public:
	float m_Rate;
	float m_DelayOffset;

public:
	FlangerModule() : m_MaxDelayunits(0),m_SamplingRate(0),m_PiCnt(0),m_PiReset(0),m_SinTerm(0),m_SinInc(0),m_InputPtr(NULL),m_WrPtr(0),m_TimeShiftIdx(0),m_N(0),m_Rate(0),m_DelayOffset(0){};
	~FlangerModule(){};
	void Apply() override;
	void SetMemberValue(uint8_t MemberId, uint8_t Value) override;
	int GetMemberValue(uint8_t MemberId) override;
	int Init(int blocksize, float* input_ptr);
	void Reset() override;
	float* GetOutputPtr()
	{
		return m_OutputBuffer;
	}
	// Interface for accessing member values
	enum ModifiableMembers
	{
		Enable,
		Rate,
		DelayOffset,
	};

private:
};

}
#endif
