#include <codec.h>
#include "main.h"

void codec_init(int mode)
{
	switch(mode)
	{
		case MODE_LINE_IN:
			codec_send_cmd(WM8731_REG_RESET, 0x00);
			codec_send_cmd(0x01, 0x17); // r in mute = 0
			codec_send_cmd(0x04, 0x12); // dac select = 1, mute mic = 1
			codec_send_cmd(0x05, 0x01); // dac mute = 0,  adc hp filter enable
			codec_send_cmd(0x06, 0x02); // microphone powerdown = 1
			//codec_send_cmd(0x07, 0x42); // master mode, 16 bit, i2s format
			codec_send_cmd(0x07, 0x4E); // master mode, 32 bit, i2s format
			codec_send_cmd(0x09, 0x01); // active control = 1
			break;

		case MODE_JACK_IN:
			codec_send_cmd(WM8731_REG_RESET, 0x00);
			//codec_send_cmd(0x02, 0x7f); // gain +6
			//codec_send_cmd(0x03, 0x7f); // gain +6
			//codec_send_cmd(0x04, 0x15); // dac select = 1, mute mic = 0, input to dac = mic, +20dB mic gain
			codec_send_cmd(0x04, 0x14); // dac select = 1, mute mic = 0, input to dac = mic
			codec_send_cmd(0x05, 0x00); // dac mute = 0,  adc hp filter enable
			codec_send_cmd(0x06, 0x01); // line in power down
			//codec_send_cmd(0x07, 0x42); // master mode, 16 bit, i2s format
			codec_send_cmd(0x07, 0x4E); // master mode, 32 bit, i2s format
			codec_send_cmd(0x09, 0x01); // active control = 1
			break;

		default:
			break;
	}

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

void codec_set_line_in_gain(int8_t gain)
{
	if(gain == 12)
	{
		codec_send_cmd(0x00, 0x1f);
		codec_send_cmd(0x01, 0x1f);
	}
	if(gain == 9)
	{
		codec_send_cmd(0x00, 0x1d);
		codec_send_cmd(0x01, 0x1d);
	}
	if(gain == 6)
	{
		codec_send_cmd(0x00, 0x1b);
		codec_send_cmd(0x01, 0x1b);
	}
	if(gain == 3)
	{
		codec_send_cmd(0x00, 0x19);
		codec_send_cmd(0x01, 0x19);
	}
	if(gain == 0)
	{
		codec_send_cmd(0x00, 0x17);
		codec_send_cmd(0x01, 0x17);
	}
}


void codec_set_out_gain(int8_t gain)
{
	if(gain == 6)
	{
		codec_send_cmd(0x02, 0x7f);
		codec_send_cmd(0x03, 0x7f);
	}
	if(gain == 3)
	{
		codec_send_cmd(0x02, 0x7c);
		codec_send_cmd(0x03, 0x7c);
	}
	if(gain == 0)
	{
		codec_send_cmd(0x02, 0x79);
		codec_send_cmd(0x03, 0x79);
	}
	if(gain == -3)
	{
		codec_send_cmd(0x02, 0x76);
		codec_send_cmd(0x03, 0x76);
	}
	if(gain == -6)
	{
		codec_send_cmd(0x02, 0x73);
		codec_send_cmd(0x03, 0x73);
	}


}

void codec_set_20db_mic_boost(uint8_t enable)
{
	if(enable == 1)
	{
		codec_send_cmd(0x04, 0x15);
	}
	else
	{
		codec_send_cmd(0x04, 0x14);
	}
}

void codec_send_cmd(uint16_t address, uint16_t cmd)
{
  uint8_t TxBuffer[2];
  TxBuffer[0] = address << 1;;
  TxBuffer[1] = cmd;
  if(HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)TxBuffer, 2)!= HAL_OK)
  {
    /* Error_Handler() function is called when error occurs. */
    Error_Handler(HAL_ERROR_I2C_ERROR);
  }
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
  {
  }
}
