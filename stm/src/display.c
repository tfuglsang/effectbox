#include "display.h"
#include "main.h"
#include "codec.h"
#include "audio_process.h"

extern t_audio_process_data audio_process_struct;

void display_init(void)
{
	// Send init values to display
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartKnob, SmartKnob_Volume, audio_process_struct.VOLUME * 100);

	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartKnob, SmartKnob_Flanger_Rate, audio_process_struct.FlangerData.rate * 100);
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartKnob, SmartKnob_Flanger_Delay, audio_process_struct.FlangerData.delay_offset * 15000);
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSwitch, Switch_Flanger, audio_process_struct.FlangerData.enable);

	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSwitch, Switch_Mic_boost, audio_process_struct.CODEC_MIC_BOOST_ENABLE);
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartSlider, Slider_Gain_out, audio_process_struct.CODEC_OUT_GAIN * 7 + 50); // linear relationship between slider value and codec gain can roughly be modelled as x = y * 7 + 50, where x is slider gain and y is codec gain in dB
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartSlider, Slider_Gain_line_in, audio_process_struct.CODEC_LINE_IN_GAIN); // linear relationship between slider value and codec gain can roughly be modelled as x = y * 7 + 10, where x is slider gain and y is codec gain in dB

	display_send_msg_and_wait_for_reply(0x01, DisplayObjectEq, EQ_BASS, audio_process_struct.BiquadData.EQ_BASS_GAIN*5 + 100 );
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectEq, EQ_MID, audio_process_struct.BiquadData.EQ_MID_GAIN*5 + 100 );
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectEq, EQ_TREBLE, audio_process_struct.BiquadData.EQ_TREBLE_GAIN*5 + 100 );

	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartSlider, Slider_Wah_freq_low, audio_process_struct.WahData.freq_low / 20);
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartSlider, Slider_Wah_freq_high, audio_process_struct.WahData.freq_high / 40);
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartSlider, Slider_Wah_q, audio_process_struct.WahData.freq_delta * 1000);
	display_send_msg_and_wait_for_reply(0x01, DisplayObjectSmartKnob, SmartKnob_Wah_rate, audio_process_struct.WahData.Q * 200);
}

static int find_codec_gain_from_slider(uint8_t ObjectValue)
{
	// loop counter, multiplier on gain pr loop
	int g = 0;
	// max value from display is 100, so value between each point on slider must be:
	int dist_between_steps = 100 / GAIN_OUT_NUMBER_OF_STEPS;
	// first interval to look in
	int i = 100 - dist_between_steps;

	// loop to search if value from display slider is within a certain interval, and if so calculate corresponding gain and send value to codec
	while(i >= 0)
	{
		if(ObjectValue >= i) // if value is within interval
		{
			return (GAIN_OUT_MAX_VALUE - GAIN_OUT_DECREMENT_VALUE*g);
			break;
		}
		i = i - 20; // go to next interval
		g++; // increase gain multiplier
	}
	return 0;
}

static int find_codec_line_in_gain_from_slider(uint8_t ObjectValue)
{
	// loop counter, multiplier on gain pr loop
	int g = 0;
	// max value from display is 100, so value between each point on slider must be:
	int dist_between_steps = 100 / GAIN_LINE_IN_NUMBER_OF_STEPS;
	// first interval to look in
	int i = 100 - dist_between_steps;

	// loop to search if value from display slider is within a certain interval, and if so calculate corresponding gain and send value to codec
	while(i >= 0)
	{
		if(ObjectValue >= i) // if value is within interval
		{
			return (GAIN_LINE_IN_MAX_VALUE - GAIN_LINE_IN_DECREMENT_VALUE*g);
			break;
		}
		i = i - 20; // go to next interval
		g++; // increase gain multiplier
	}
	return 0;
}


void display_decode_msg(void)
{
	uint8_t DisplayMsgType = IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 0];

	if (DisplayMsgType == DisplayMsgObject)
	{
		uint8_t DisplayObject = IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 1];
		uint8_t ObjectNumber = IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 2];
		float ObjectValue = (float)IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 4];

		switch(DisplayObject)
		{
			case DisplayObjectSmartKnob:

				if(ObjectNumber == SmartKnob_Volume)
				{
					audio_process_struct.VOLUME = ObjectValue / 100;
				}
				if(ObjectNumber == SmartKnob_Flanger_Rate)
				{
					audio_process_struct.FlangerData.rate = ObjectValue / 100;
					flanger_set_parameters(&audio_process_struct.FlangerData);
				}
				if(ObjectNumber == SmartKnob_Flanger_Delay)
				{
					audio_process_struct.FlangerData.delay_offset = ObjectValue / 15000;
					flanger_set_parameters(&audio_process_struct.FlangerData);
				}
				if(ObjectNumber == SmartKnob_Wah_rate)
				{
					audio_process_struct.WahData.freq_delta = ObjectValue / 1000; // goes from 0.001 to 0.1
				}

				break;

			case DisplayObjectSwitch:

				if(ObjectNumber == Switch_Flanger)
				{
					audio_process_struct.FlangerData.enable = ObjectValue;
				}
				if(ObjectNumber == Switch_Wah)
				{
					audio_process_struct.WahData.enable = ObjectValue;
				}
				if(ObjectNumber == Switch_Overdrive)
				{
					audio_process_struct.OverdriveData.enable = ObjectValue;
				}

				if(ObjectNumber == Switch_Mic_boost)
				{

					if(audio_process_struct.ACTIVE_CODEC_INPUT_INTERFACE == MODE_JACK_IN) // only set mic boost if jack interface is active
					{
						audio_process_struct.CODEC_MIC_BOOST_ENABLE = ObjectValue;
						codec_set_20db_mic_boost(ObjectValue);
					}
				}
				break;

			case DisplayObjectSmartSlider:

				if(ObjectNumber == Slider_Gain_out)
				{
					int gain = find_codec_gain_from_slider(ObjectValue);
					audio_process_struct.CODEC_OUT_GAIN = gain;
					codec_set_out_gain(gain);
				}
				if(ObjectNumber == Slider_Gain_line_in)
				{
					if(audio_process_struct.ACTIVE_CODEC_INPUT_INTERFACE == MODE_LINE_IN)  // only set line in gain if we line interface is active
					{
						int gain = find_codec_line_in_gain_from_slider(ObjectValue);
						audio_process_struct.CODEC_LINE_IN_GAIN = gain;
						codec_set_line_in_gain(gain);
					}
				}
				if(ObjectNumber == Slider_Wah_freq_low)
				{
					audio_process_struct.WahData.freq_low = ObjectValue * 7 + 500; // goes from 500 to 1200
				}
				if(ObjectNumber == Slider_Wah_freq_high)
				{
					audio_process_struct.WahData.freq_high = ObjectValue * 25  + 1500; // goes from 1500 to 4000
				}
				if(ObjectNumber == Slider_Wah_q) // bandwidth
				{
					audio_process_struct.WahData.Q = ObjectValue / 200; // goes from Slider_Wah_q to 0.5
				}

				break;
			case DisplayObjectEq:

				if(ObjectNumber == EQ_BASS)
				{
					int gain = ObjectValue;
					biquad_set_bass_filter(&audio_process_struct.BiquadData, gain);
				}
				if(ObjectNumber == EQ_MID)
				{
					int gain = ObjectValue;
					biquad_set_mid_filter(&audio_process_struct.BiquadData, gain);
				}
				if(ObjectNumber == EQ_TREBLE)
				{
					int gain = ObjectValue;
					biquad_set_treble_filter(&audio_process_struct.BiquadData, gain);
				}


				break;

			case DisplayObjectButton:
			case DisplayObjectForm:

			break;
		}
	}
	IncomingMsgFromDisplay_RdPtr = IncomingMsgFromDisplay_RdPtr + MSG_SIZE;
	if(IncomingMsgFromDisplay_RdPtr >= MSG_FROM_DISPLAY_ARRAY_SIZE)
	{
		IncomingMsgFromDisplay_RdPtr = 0;
	}

}

void display_send_msg(uint8_t MsgType, uint8_t ObjectType, uint8_t ObjectNumber, uint8_t Value)
{
	DisplayTxBuffer[0] = MsgType;
	DisplayTxBuffer[1] = ObjectType;
	DisplayTxBuffer[2] = ObjectNumber;
	DisplayTxBuffer[3] = 0x00;
	DisplayTxBuffer[4] = Value;
	DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

	if (HAL_UART_Transmit_IT(&UartHandle, (uint8_t*) DisplayTxBuffer, MSG_SIZE) != HAL_OK) {
			Error_Handler(HAL_ERROR_UART_TRANSMIT);
		}
}

void display_send_msg_and_wait_for_reply(uint8_t MsgType, uint8_t ObjectType, uint8_t ObjectNumber, uint8_t Value)
{
	DisplayTxBuffer[0] = MsgType;
	DisplayTxBuffer[1] = ObjectType;
	DisplayTxBuffer[2] = ObjectNumber;
	DisplayTxBuffer[3] = 0x00;
	DisplayTxBuffer[4] = Value;
	DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

	if (HAL_UART_Transmit_IT(&UartHandle, (uint8_t*) DisplayTxBuffer, MSG_SIZE) != HAL_OK) {
			Error_Handler(HAL_ERROR_UART_TRANSMIT);
		}
	HAL_UART_Receive(&UartHandle, (uint8_t *) DisplayRxBuffer, 1, 1000);
}

void display_prepare_msg_receive(uint8_t bytes_to_receive) {
	if (UartHandle.RxState != HAL_UART_STATE_BUSY_RX) {
		// Reset transmission flag
		if(UART_DONE == 1)
		{
			UART_DONE = 0;
			//HAL_UART_AbortReceive(&UartHandle);
			if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *) DisplayRxBuffer, bytes_to_receive)
					!= HAL_OK) {
				Error_Handler(HAL_ERROR_UART_RECEIVE);
			}
		}
	}
}


