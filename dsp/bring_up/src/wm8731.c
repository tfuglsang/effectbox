#include "main.h"
#include "wm8731.h"

void InitWM8731(void)
{
 // CODEC MASTER
  SendCodecCmd(WM8731_REG_RESET, 0x00);
  SendCodecCmd(0x00, 0x17); // l in mute = 0
  SendCodecCmd(0x01, 0x17); // r in mute = 0
  SendCodecCmd(0x04, 0x12); // dac select = 1, mute mic = 1
  SendCodecCmd(0x05, 0x00); // dac mute = 0,  adc hp filter enable
  SendCodecCmd(0x06, 0x02); // microphone powerdown = 1
  //SendCodecCmd(0x07, 0x42); // master mode, 16 bit, i2s format
  SendCodecCmd(0x07, 0x4E); // master mode, 32 bit, i2s format
  SendCodecCmd(0x09, 0x01); // active control = 1

  /*
    // DAC -> headphone
    SendCodecCmd(WM8731_REG_RESET, 0x00);
    SendCodecCmd(0x04, 0x12);
    SendCodecCmd(0x05, 0x00);
    SendCodecCmd(0x06, 0x07);
    SendCodecCmd(0x07, 0x4E); // master mode, 16 bit, i2s format
    SendCodecCmd(0x09, 0x09);
  */
  /*
    // Passthrough: line_in -> hp out
    SendCodecCmd(WM8731_REG_RESET, 0x00);
    SendCodecCmd(0x04, 0x0A); // l in mute = 0
    SendCodecCmd(0x06, 0x0E); // r in mute = 0
    SendCodecCmd(0x09, 0x01); // active control = 1
  */

  /*
    //  line_in -> ADC
    SendCodecCmd(WM8731_REG_RESET, 0x00);
    SendCodecCmd(0x00, 0x17);
    SendCodecCmd(0x01, 0x17);
    SendCodecCmd(0x04, 0x02);
    SendCodecCmd(0x05, 0x09);
    SendCodecCmd(0x07, 0x4E); // master mode, 16 bit, i2s format
    SendCodecCmd(0x06, 0x0A);
    SendCodecCmd(0x09, 0x01);
  */
}

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
