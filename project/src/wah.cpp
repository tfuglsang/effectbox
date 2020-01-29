#include <wah.h>
#include <arm_math.h>

int WahModule :: Init(int blocksize, float* input_ptr) {
    // error handling
    m_Init_ok = 0;
    if (blocksize>WAH_MAX_BLOCKSIZE) return 1;

    // no errors, go on..
    m_InputPtr = input_ptr;
    m_Enable = 1;
    m_Blocksize = blocksize;
    m_SamplingRate = WAH_SAMPLINGRATE;

    Reset();
    m_Init_ok = 1;

    return 0;
}

int WahModule :: GetMemberValue(uint8_t MemberId){
	if(MemberId == ModifiableMembers::Enable)
		return m_Enable;
	else if(MemberId == ModifiableMembers::FreqLow)
		return ((int)(m_FreqLow / 20));
	else if(MemberId == ModifiableMembers::FreqHigh)
		return ((int)(m_FreqHigh / 40));
	else if(MemberId == ModifiableMembers::FreqDelta)
		return ((int)(m_FreqDelta * 1000));
	else if(MemberId == ModifiableMembers::Q)
		return ((int)(m_Q * 200));
	else
		return 0;
}

void WahModule :: SetMemberValue(uint8_t MemberId, uint8_t Value){

	switch(MemberId)
	{
	case ModifiableMembers::FreqDelta:
		m_FreqCenter = Value / 1000; // goes from 0.001 to 0.1
		break;
	case ModifiableMembers::Enable:
		m_Enable = Value;
		break;
	case ModifiableMembers::FreqLow:
		m_FreqLow = Value * 7 + 500;
		break;
	case ModifiableMembers::FreqHigh:
		m_FreqHigh = Value * 25  + 1500;
		break;
	case ModifiableMembers::Q:
		m_Q = Value / 200;
		break;
	}
}


void WahModule :: Reset() {
    arm_fill_f32(0.0f, m_OutputBuffer, m_Blocksize);
    m_YbOld = 0;
    m_YlOld = 0;
}

void WahModule :: Apply() {

	if(m_Enable == WAH_PASSTHROUGH)
	{
		arm_copy_f32(m_InputPtr, m_OutputBuffer, m_Blocksize);
	}
	else if(m_Enable == WAH_ENABLE)
	{
		float F1, yh, yb, yl;

		for(int i = 0; i < m_Blocksize; i++)
		{

			F1 = 2 * sin((PI*m_FreqCenter) / m_SamplingRate);

			yh = m_InputPtr[i] - m_YlOld - m_Q*m_YbOld;

			yb = F1*yh + m_YbOld;
			yl = F1*yb + m_YlOld;

			m_OutputBuffer[i] = yb;

			m_YbOld = yb;
			m_YlOld = yl;

			m_FreqCenter = m_FreqCenter + m_FreqDelta;
			if(m_FreqCenter > m_FreqHigh) // top reached! count down now!
			{
				m_FreqCenter = m_FreqHigh;
				m_FreqDelta = m_FreqDelta * -1;
			}

			if (m_FreqCenter < m_FreqLow) // bottom reached! count up now!
			{
				m_FreqCenter = m_FreqLow;
				m_FreqDelta = m_FreqDelta * -1;
			}

		}
	}

}
