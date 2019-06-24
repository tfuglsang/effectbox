#include "main.h"

void SendCodecCmd(uint16_t address, uint16_t cmd)
{
  uint8_t TxBuffer[2];
  TxBuffer[0] = address << 1;;
  TxBuffer[1] = cmd;
  if(HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)TxBuffer, 2)!= HAL_OK)
  {
    /* Error_Handler() function is called when error occurs. */
    Error_Handler(77);
  }
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
  {
  }
}
