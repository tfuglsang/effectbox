#include <overdrive.h>
#include <arm_math.h>
#include <stdlib.h>

int OverdriveModule :: Init(int blocksize, float* input_ptr) {
    // error handling
    m_Init_ok = 0;
    if (blocksize>OVERDRIVE_MAX_BLOCKSIZE) return 1;

    // no errors, go on..

    m_InputPtr = input_ptr;
    m_Blocksize = blocksize;
    m_Enable = 1;

    Reset();
    m_Init_ok = 1;

    return 0;
}

void OverdriveModule :: Reset() {
    arm_fill_f32(0.0f, m_OutputBuffer, m_Blocksize);
}

void OverdriveModule :: Apply() {
	if(m_Enable == OVERDRIVE_PASSTHROUGH)
	{
		arm_copy_f32(m_InputPtr, m_OutputBuffer, m_Blocksize);
	}
	else if(m_Enable == OVERDRIVE_ENABLE)
	{
		for(int i = 0; i < m_Blocksize; i++)
		{

			if( abs(m_InputPtr[i])< m_Threshold)
			{
				m_OutputBuffer[i]=2*m_InputPtr[i];
			}

			if (abs(m_InputPtr[i])>=m_Threshold)
			{
				if (m_InputPtr[i]> 0)
				{
					m_OutputBuffer[i]= (3 -  pow(2-m_InputPtr[i]*3, 2) ) / 3;
				}

				if (m_InputPtr[i]< 0)
				{
					m_OutputBuffer[i] = - (3 - pow( (2 - abs( m_InputPtr[i]*3 ) ), 2)) / 3;
				}
			}

			if (abs(m_InputPtr[i])>2*m_Threshold)
			{
				if (m_InputPtr[i]> 0)
				{
					m_OutputBuffer[i] = 1;
				}
				if (m_InputPtr[i]< 0)
				{
					m_OutputBuffer[i] =-1;
				}
			}
		}
    }
}

void OverdriveModule :: SetMemberValue(uint8_t MemberId, uint8_t Value){
	switch(MemberId)
	{
	case ModifiableMembers::Enable:
		m_Enable = Value;
		break;
	}
}

int OverdriveModule :: GetMemberValue(uint8_t MemberId){
	if(MemberId == ModifiableMembers::Enable)
		return m_Enable;
	else
		return 0;
}
