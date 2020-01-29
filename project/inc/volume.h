#include <arm_math.h>
#include <AudioModule.h>

#define VOLUME_MAX_BLOCKSIZE 128*2

#ifdef __cplusplus
extern "C" {

class VolumeModule : public AudioModule{
private:

	float* m_InputPtr;
	float m_OutputBuffer[VOLUME_MAX_BLOCKSIZE];
	float m_Volume;
	int m_MicBoost;
	int m_GainLineIn;
	int m_GainOut;
	int m_ActiveCodecInputInterface;

public:
	VolumeModule(){};
	~VolumeModule(){};
	void Apply() override;
	int Init(int blocksize, float* input_ptr);
	void Reset() override;
	void SetMemberValue(uint8_t MemberId, uint8_t Value) override;
	int GetMemberValue(uint8_t MemberId) override;
	float* GetOutputPtr()
	{
		return m_OutputBuffer;
	}

	// Interface for accessing public members
	enum ModifiableMembers
	{
		Volume,
		MicBoost,
		GainLineIn,
		GainOut,
		ActiveCodecInputInterface
	};

private:
};

}
#endif
