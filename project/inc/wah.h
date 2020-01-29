#include <AudioModule.h>
#include <display.h>

#define WAH_MAX_BLOCKSIZE 256
#define WAH_ENABLE        1
#define WAH_PASSTHROUGH   0
#define WAH_SAMPLINGRATE 48000

#define WAH_FREQ_LOW 1000
#define WAH_FREQ_HIGH 2000
#define WAH_FREQ_DELTA 0.05
#define WAH_Q 0.1

/* INTERFACE FUNCTIONS */
#ifdef __cplusplus
extern "C" {

class WahModule : public AudioModule{
private:
	float* m_InputPtr;
	float m_OutputBuffer[WAH_MAX_BLOCKSIZE];
	float m_YbOld;
	float m_YlOld;
	float m_FreqLow;
	float m_FreqHigh;
	float m_FreqDelta;
	float m_FreqCenter;
	float m_Q;

public:
	WahModule(){
		m_Q = WAH_Q; // pass band width, lower value means smaller band
		m_FreqLow = WAH_FREQ_LOW;
		m_FreqHigh = WAH_FREQ_HIGH;
		m_FreqDelta = WAH_FREQ_DELTA; // wah frequency, how many Hz are cycled through pr sample
		m_FreqCenter = m_FreqLow; // pass band center freq
	};
	~WahModule(){};
	void Apply() override;
	void Reset() override;
	int Init(int blocksize, float* input_ptr);
	void SetMemberValue(uint8_t MemberId, uint8_t Value) override;
	int GetMemberValue(uint8_t MemberId) override;

	float* GetOutputPtr()
	{
		return m_OutputBuffer;
	}

	// Interface for accessing member values
	enum ModifiableMembers
	{
		Enable,
		FreqLow,
		FreqHigh,
		FreqDelta,
		Q
	};

private:
};

}
#endif
