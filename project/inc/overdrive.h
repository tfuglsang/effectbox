#include <AudioModule.h>
#include <display.h>

#define OVERDRIVE_MAX_BLOCKSIZE 256
#define OVERDRIVE_ENABLE         1
#define OVERDRIVE_PASSTHROUGH    0

#define OVERDRIVE_THRESHOLD 0.3 * 2147483648

/* INTERFACE FUNCTIONS */
#ifdef __cplusplus
extern "C" {

class OverdriveModule : public AudioModule{
private:
	float m_Threshold;
	float m_OutputBuffer[OVERDRIVE_MAX_BLOCKSIZE];
	float* m_InputPtr;
public:
	OverdriveModule() : m_InputPtr(NULL){
		m_Threshold = OVERDRIVE_THRESHOLD;
	};
	~OverdriveModule(){};
	void Apply() override;
	void Reset() override;
	void SetMemberValue(uint8_t MemberId, uint8_t Value) override;
	int GetMemberValue(uint8_t MemberId) override;

	int Init(int blocksize, float* input_ptr);
	float* GetOutputPtr()
	{
		return m_OutputBuffer;
	}

	int GetValue(uint8_t MemberId)
	{
		if(MemberId == ModifiableMembers::Enable)
			return m_Enable;
		else
			return 0;
	}

	// Interface for accessing member values
	enum ModifiableMembers
	{
		Enable,
	};

private:
};

}
#endif
