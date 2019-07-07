#include "main.h"

// Message pattern from display, when buttons has been pressed
uint8_t Button_1[] = {0x07,0x21,0x00,0x00,0x00,0x26};
uint8_t Button_2[] = {0x07,0x21,0x01,0x00,0x00,0x27};

void DecodeDisplayMsg(void)
{
    while(0 < IncomingMsgFromDisplay_WrPtr)
    {
      if(IncomingMsgFromDisplay[0] == 6) // if the next element is acknowledge, increment read ptr and do nothing
      {
        IncomingMsgFromDisplay_WrPtr--;
      }
      else
      {
        if(IncomingMsgFromDisplay[0] == 7) // cmd button pressed
        {
          if(IncomingMsgFromDisplay_WrPtr >= 6) // if a full button msg has been received, start decoding
          {
           // Find out what button has been pressed
          if (Buffercmp(IncomingMsgFromDisplay, Button_1, 6) == 0 )
          {
            selected_gauge = Left;
            TIM1->CNT = left_gauge_value;
            value = left_gauge_value;
            SendValueToGauge(selected_gauge, value);
          }
          else if (Buffercmp(IncomingMsgFromDisplay, Button_2, 6) == 0 )
          {
            selected_gauge = Right;
            TIM1->CNT = right_gauge_value;
            value = right_gauge_value;
            SendValueToGauge(selected_gauge, value);
          }
          IncomingMsgFromDisplay_WrPtr = IncomingMsgFromDisplay_WrPtr - 6;
          }
          else
          {
            break;
          }

        }
      }
    }
}

void PrepareDisplayMsgReceive(void)
{
  if(UartHandle.RxState != HAL_UART_STATE_BUSY_RX)
  {
    /* Reset transmission flag */
    HAL_UART_AbortReceive(&UartHandle);
    if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)DisplayRxBuffer, 1) != HAL_OK)
    {
      Error_Handler(HAL_ERROR_UART_RECEIVE);
    }
  }
}

void SendValueToGauge(uint8_t gauge_number, uint8_t value)
{
  DisplayTxBuffer[0] = 0x01;
  DisplayTxBuffer[1] = 0x07;
  DisplayTxBuffer[2] = gauge_number;
  DisplayTxBuffer[3] = 0x00;
  DisplayTxBuffer[4] = value;
  DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

  if(UartHandle.gState != HAL_UART_STATE_BUSY_TX)
  {
    HAL_UART_AbortReceive(&UartHandle);
    Reset_DisplayRxBuffer();

    if(HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)DisplayTxBuffer, 6)!= HAL_OK)
    {
    Error_Handler(HAL_ERROR_UART_TRANSMIT);
    }

      if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)DisplayRxBuffer, 1) != HAL_OK)
      {
      Error_Handler(HAL_ERROR_UART_RECEIVE);
      }
  }
}

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
