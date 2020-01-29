#include <flanger.h>
#include <arm_math.h>

float FLANGER_RATE_INIT = 0.9;
float FLANGER_DELAY_INIT = 0.01;

#define FLANGER_ENABLE         1
#define FLANGER_PASSTHROUGH    0

int FlangerModule :: Init(int blocksize, float* input_ptr) {
    // error handling
    m_Init_ok = 0;
    if (blocksize>FLANGER_MAX_BLOCKSIZE) return 1;

    // no errors, go on..
    m_Enable = 1;
    m_InputPtr = input_ptr;
    m_Blocksize = blocksize;
    m_SamplingRate = FLANGER_SAMPLING_RATE;
    m_DelayOffset = FLANGER_DELAY_INIT / 2;
    m_MaxDelayunits = ceil(0.015*m_SamplingRate);
    m_Rate= FLANGER_RATE_INIT;
    m_SinInc = (m_Rate/m_SamplingRate)*2*PI;
    float tmp = floor( 1 / (m_Rate / m_SamplingRate));
    m_PiReset = (int)tmp; // (2*PI)/m_SinInc;

    Reset();
    m_Init_ok = 1;

    return 0;
}

void FlangerModule :: SetMemberValue(uint8_t MemberId, uint8_t Value){
	float tmp;
	switch(MemberId)
	{
	case ModifiableMembers::Rate:
		m_Rate = Value / 100;
		m_SinInc = (m_Rate/m_SamplingRate)*2*PI;
		tmp = floor( 1 / (m_Rate / m_SamplingRate));
		m_PiReset = (int)tmp; // (2*PI)/m_SinInc;
		break;

	case ModifiableMembers::DelayOffset:
		m_DelayOffset = Value / 15000;
		break;

	case ModifiableMembers::Enable:
		m_Enable = Value;
		break;
	}
}

int FlangerModule :: GetMemberValue(uint8_t MemberId){
	switch(MemberId)
	{
	case ModifiableMembers::Rate:
		return ((int)(m_Rate*100));
		break;
	case ModifiableMembers::DelayOffset:
		return ((int)(m_DelayOffset * 15000));
		break;
	case ModifiableMembers::Enable:
		return m_Enable;
		break;
	default:
		return 0;
	}
}

void FlangerModule :: Reset(){
    arm_fill_f32(0.0f, m_OutputBuffer, m_Blocksize);
    arm_fill_f32(0.0f, m_DelayBuffer, FLANGER_DELAYLINE_SIZE);

    m_SinTerm = 0;
    m_PiCnt = 0;
    m_WrPtr = 0;
}

static int flanger_time_shift;
void FlangerModule :: Apply()
{
	if(m_Enable == FLANGER_PASSTHROUGH)
		{
			arm_copy_f32(m_InputPtr, m_OutputBuffer, m_Blocksize);
		}
		else if(m_Enable == FLANGER_ENABLE)
		{
			// check if new input block fits in delay_buffer
			int space_in_buffer = FLANGER_DELAYLINE_SIZE - (m_WrPtr + m_Blocksize);

			if(space_in_buffer < 0){ // data doesnt fit
				// first write the amount that fits
				int amount_to_copy = m_Blocksize + space_in_buffer;
				arm_copy_f32(m_InputPtr, &m_DelayBuffer[m_WrPtr], amount_to_copy); //m_DelayBuffer(m_WrPtr:obj.wr_ptr+obj.input_blocksize+space - 1) = input_block(1:obj.input_blocksize+space);

				// then rewind wr pointer and write the rest of the block
				m_WrPtr = 0;
				arm_copy_f32(m_InputPtr + amount_to_copy, &m_DelayBuffer[m_WrPtr], m_Blocksize - amount_to_copy);
				// obj.delay_buffer(obj.wr_ptr:obj.wr_ptr - space -1) = input_block(obj.input_blocksize+space + 1:obj.input_blocksize);
				m_WrPtr = m_WrPtr - space_in_buffer;
			}
			else
			{
				// if it fits, append it
				arm_copy_f32(m_InputPtr, &m_DelayBuffer[m_WrPtr], m_Blocksize);
				m_WrPtr = m_WrPtr + m_Blocksize;

				if(m_WrPtr == FLANGER_DELAYLINE_SIZE)
				{
					m_WrPtr = 0;
				}
			}


			for(int i = 0; i < m_Blocksize; i++)
			{
				m_SinTerm = m_SinTerm + m_SinInc;
				m_PiCnt++;
				if(m_PiCnt >= m_PiReset)
				{
					m_PiCnt = 0;
					m_SinTerm = 0;
				}

				float time_delay = m_DelayOffset * sin(m_SinTerm)+m_DelayOffset;

				m_N = (int)ceil(m_SamplingRate*time_delay);
				flanger_time_shift = m_WrPtr - m_N + i - m_Blocksize; // idx of delayed sample with reference to current write pointer

				if (flanger_time_shift < 0) // if idx is under lower limit, wrap backwards to end of buffer
				{
					flanger_time_shift = FLANGER_DELAYLINE_SIZE + flanger_time_shift;
				}
				if(flanger_time_shift >= FLANGER_DELAYLINE_SIZE) // if idx is larger than length of delaybuffer, start fresh from beginning of buffer
				{
					flanger_time_shift = flanger_time_shift - FLANGER_DELAYLINE_SIZE;
				}

				m_TimeShiftIdx = flanger_time_shift;
				m_OutputBuffer[i] = m_InputPtr[i] +  m_DelayBuffer[flanger_time_shift];
			}
	    }
}

