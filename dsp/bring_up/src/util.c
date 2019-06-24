#include "main.h"

uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if ((*pBuffer1) != *pBuffer2)
    {
      return BufferLength;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

void Reset_DisplayRxBuffer()
{
  DisplayRxBuffer[0] = 0;
  DisplayRxBuffer[1] = 0;
  DisplayRxBuffer[2] = 0;
  DisplayRxBuffer[3] = 0;
  DisplayRxBuffer[4] = 0;
  DisplayRxBuffer[5] = 0;
}
