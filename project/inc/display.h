#include <stm32h7xx_hal.h>
#include <AudioModule.h>

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

///////////////////////////////////
// Define all display objects types and object numbers here.
// Display objects must be linked to a AudioModule member (done in display.cpp)
///////////////////////////////////

// Message types
#define DisplayMsgSet	    		0x01
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
#define Switch_Reverb		 		4

// Sliders
#define Slider_Gain_out				0
#define Slider_Gain_line_in			1
#define Slider_Wah_freq_low			2
#define Slider_Wah_freq_high		3
#define Slider_Wah_q				4

// Equalizer
#define Eq_Bass						0
#define Eq_Mid						1
#define Eq_Treble					2

#define MSG_FROM_DISPLAY_ARRAY_SIZE 60
#define MSG_SIZE 6

extern uint8_t UartMsgReceived;
extern uint8_t DisplayTxBuffer[MSG_SIZE]; 									// Buffer used for display transmission
extern uint8_t DisplayRxBuffer[MSG_SIZE];										// Buffer used for display reception
extern uint8_t IncomingMsgFromDisplay[MSG_FROM_DISPLAY_ARRAY_SIZE];	// Queue for incoming display messages
extern uint8_t IncomingMsgFromDisplay_WrPtr;							// Keeps track of the next byte to write in the message queue
extern uint8_t IncomingMsgFromDisplay_RdPtr;							// Keeps track of the next byte to decode in the message queue

#ifdef __cplusplus
extern "C" {
#endif

void DisplayInit(void);
void DisplayDecodeMsg(void);
void DisplaySendMsg(uint8_t ObjectType, uint8_t ObjectNumber, uint8_t Value);
void DisplaySetVolume(uint8_t Value);
void DisplaySendMsgAndWaitForResponse(uint8_t moduleObject, uint8_t moduleNumber, uint8_t Value);
void DisplayPrepareMsgReceive(uint8_t bytes_to_receive);
#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */
