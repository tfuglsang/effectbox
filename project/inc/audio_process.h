#include <arm_math.h>
#include <biquad.h>
#include <flanger.h>
#include <wah.h>
#include <overdrive.h>
#include <volume.h>
#include <revmodel.hpp>

#define AUDIO_BLOCKSIZE 128
#define SAMPLING_RATE 48000

#ifdef __cplusplus
extern "C" {
#endif

void AudioProcessInit(int blocksize, float* input_ptr);
void AudioProcessApply();
float* AudioProcessGetOutputBuffer();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {

class AudioProcess : public AudioModule{
private:

	float* m_InputPtr;
	float m_OutputBuffer[VOLUME_MAX_BLOCKSIZE];
	int NumberOfModules = 0;
public:
	AudioProcess() : m_InputPtr(NULL) {};
	~AudioProcess(){};
	void Apply() override;
	int Init(int blocksize, float* input_ptr) override;
	void Reset() override;
	void SetMemberValue(uint8_t MemberId, uint8_t Value) {};
	int GetMemberValue(uint8_t MemberId) { return 0;};
	float* GetOutputPtr()
	{
		return m_OutputBuffer;
	}

	int AddModule(AudioModule* module);

	// Interface for accessing public members
	enum ModifiableMembers
	{

	};

	AudioModule* modules[5];

	BiquadModule biquad;
	FlangerModule flanger;
	OverdriveModule overdrive;
	WahModule wah;
	VolumeModule volume;
	ReverbModule reverb;

private:
};

}
#endif
