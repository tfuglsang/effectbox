#include "stm32h7xx_hal.h"
#include <codec.h>
#include "main.h"

int ConvertDisplayValueToGain(uint8_t DisplayValue, int8_t GainMaxValue, int8_t GainNumberOfSteps, int8_t GainDecrementPrStep)
{
	// loop counter, multiplier on gain pr loop
	int g = 0;
	// max value from display is 100, so value between each point on slider must be:
	int dist_between_steps = 100 / GainNumberOfSteps;
	// first interval to look in
	int i = 100 - dist_between_steps;

	// loop to search if value from display slider is within a certain interval, and if so calculate corresponding gain and send value to codec
	while(i >= 0)
	{
		if(DisplayValue >= i) // if value is within interval
		{
			return (GainMaxValue - GainDecrementPrStep*g);
			break;
		}
		i = i - 20; // go to next interval
		g++; // increase gain multiplier
	}
	return 0;
}

void CodecInit(int mode)
{
	switch(mode)
	{
		case MODE_LINE_IN:
			CodecSendCmd(WM8731_REG_RESET, 0x00);
			CodecSendCmd(0x01, 0x17); // r in mute = 0
			CodecSendCmd(0x04, 0x12); // dac select = 1, mute mic = 1
			CodecSendCmd(0x05, 0x00); // dac mute = 0,  adc hp filter enable
			CodecSendCmd(0x06, 0x02); // microphone powerdown = 1
			//codec_send_cmd(0x07, 0x42); // master mode, 16 bit, i2s format
			CodecSendCmd(0x07, 0x4E); // master mode, 32 bit, i2s format
			CodecSendCmd(0x09, 0x01); // active control = 1
			break;

		case MODE_JACK_IN:
			CodecSendCmd(WM8731_REG_RESET, 0x00);
			//codec_send_cmd(0x02, 0x7f); // gain +6
			//codec_send_cmd(0x03, 0x7f); // gain +6
			//codec_send_cmd(0x04, 0x15); // dac select = 1, mute mic = 0, input to dac = mic, +20dB mic gain
			CodecSendCmd(0x04, 0x14); // dac select = 1, mute mic = 0, input to dac = mic
			CodecSendCmd(0x05, 0x00); // dac mute = 0,  adc hp filter enable
			CodecSendCmd(0x06, 0x01); // line in power down
			//codec_send_cmd(0x07, 0x42); // master mode, 16 bit, i2s format
			CodecSendCmd(0x07, 0x4E); // master mode, 32 bit, i2s format
			CodecSendCmd(0x09, 0x01); // active control = 1
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

void CodecSetOutGain(int8_t gain) // From -6 to 6
{
	int value = 0x79; // equals 0dB
	value += gain; // 1dB pr step
	//codec_send_cmd(0x02, 0x7f);
	CodecSendCmd(0x03, value);
}

void CodecSetLineInGain(int8_t gain)
{
	// Each step is 1.5dB, so we must go 2 steps up to reach 3dB
	if(gain == 0)
	{
		CodecSendCmd(0x00, 0x17);
		CodecSendCmd(0x01, 0x17);
	}
	else
	{
		int steps = (gain / 3) * 2;
		int value = steps;
		CodecSendCmd(0x00, 0x17 + value);
		CodecSendCmd(0x01, 0x17 + value);
	}
}


void CodecSetMicBoost(uint8_t enable)
{
	int value = 0x14;
	value += enable;
	CodecSendCmd(0x04, value);
}

void CodecSendCmd(uint16_t address, uint16_t cmd)
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
