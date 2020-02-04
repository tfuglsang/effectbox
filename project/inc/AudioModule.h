#include <arm_math.h>

#ifndef AUDIO_MODULE_WRAPPER_H
#define AUDIO_MODULE_WRAPPER_H

#ifdef __cplusplus
extern "C" {

	class AudioModule{

	public:
		int m_Enable;
		int m_Init_ok;
		int m_Blocksize;
		int m_SamplingRate;

		/* abstract class (pure virtual)
		virtual AudioModule()
		{
		}
		*/
		virtual ~AudioModule()
		{

		}

		virtual void Apply(){};
		virtual void Reset(){};
		virtual void SetMemberValue(uint8_t MemberId, uint8_t Value) = 0;
		virtual int GetMemberValue(uint8_t MemberId) = 0;
	};
}

#endif

#endif // !AUDIO_MODULE_WRAPPER_H
