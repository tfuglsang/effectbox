#include "stm32h7xx_hal.h"

// Message types
#define DisplayMsgAck	    		0x06
#define DisplayMsgObject    		0x07

// Display object types
#define DisplayObjectButton 		0x21
#define DisplayObjectForm 			0x0A
#define DisplayObjectSwitch			0x1E
#define DisplayObjectEq 			0x04
#define DisplayObjectSmartSlider	0x24
#define DisplayObjectSmartKnob 		0x25

// Smart knobs
#define SmartKnob_Volume 			1
#define SmartKnob_Flanger_Delay 	0
#define SmartKnob_Flanger_Rate 		2
#define SmartKnob_Wah_rate	 		4

// Switches
#define Switch_Wah		 			0
#define Switch_Flanger		 		1
#define Switch_Mic_boost	 		2
#define Switch_Overdrive	 		3

// Sliders
#define Slider_Gain_out				0
#define Slider_Gain_line_in			1
#define Slider_Wah_freq_low			2
#define Slider_Wah_freq_high		3
#define Slider_Wah_q				4

// Equalizer
#define EQ_BASS						0
#define EQ_MID						1
#define EQ_TREBLE					2

#define MSG_FROM_DISPLAY_ARRAY_SIZE 60
#define MSG_SIZE 6
uint8_t UART_DONE;
uint8_t DisplayTxBuffer[MSG_SIZE]; 									// Buffer used for display transmission
uint8_t DisplayRxBuffer[MSG_SIZE];										// Buffer used for display reception
uint8_t IncomingMsgFromDisplay[MSG_FROM_DISPLAY_ARRAY_SIZE];	// Queue for incoming display messages
uint8_t IncomingMsgFromDisplay_WrPtr;							// Keeps track of the next byte to write in the message queue
uint8_t IncomingMsgFromDisplay_RdPtr;							// Keeps track of the next byte to decode in the message queue


void display_init(void);
void display_decode_msg(void);
void display_send_msg(uint8_t MsgType, uint8_t ObjectType, uint8_t ObjectNumber, uint8_t Value);
void display_send_msg_and_wait_for_reply(uint8_t MsgType, uint8_t ObjectType, uint8_t ObjectNumber, uint8_t Value);
void display_prepare_msg_receive(uint8_t bytes_to_receive);

