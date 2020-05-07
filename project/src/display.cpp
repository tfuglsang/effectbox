#include <arm_math.h>
#include "main.h"
#include "codec.h"
#include "display.h"
#include "audio_process.h"
#include <vector>

// Struct for storing display module type (eg. Button) and the object number (eg. 5)
struct DisplayModuleID
{
	uint8_t Object; // Display object type
	uint8_t Number; // Display object number
};

// Struct for storing DisplayModuleID and its associated AudioModule and AudioModule member ID
struct DisplayToModuleInterface{
	DisplayModuleID Id;
	AudioModule* AudioModulePtr; // Pointer to audio module
	uint8_t ModuleMemberId; // ID of the associated audio module member
};

// All display modules and their associated AudioModules are stored here
std::vector<DisplayToModuleInterface> DisplayModules;

// Overload operator to check if DisplayModuleID object and DisplayModuleInterface object are registered to the same module
bool operator==(const DisplayModuleID& displayModule, const DisplayToModuleInterface& displayInterface)
{
	   return displayModule.Number == displayInterface.Id.Number &&
			  displayModule.Object == displayInterface.Id.Object;
}

//////////////////////////////
//	Display Objects ID
//////////////////////////////

DisplayModuleID DisplayVolumeID			= {DisplayObjectSmartKnob, SmartKnob_Volume};
DisplayModuleID DisplayMicBoostID		= {DisplayObjectSwitch, Switch_Mic_boost};
DisplayModuleID DisplayGainOutID		= {DisplayObjectSmartSlider, Slider_Gain_out};
DisplayModuleID DisplayGainLineInID		= {DisplayObjectSmartSlider, Slider_Gain_line_in};

DisplayModuleID DisplayEqBassID 		= {DisplayObjectEq, Eq_Bass};
DisplayModuleID DisplayEqMidID 			= {DisplayObjectEq, Eq_Mid};
DisplayModuleID DisplayEqTrebleID 		= {DisplayObjectEq, Eq_Treble};

DisplayModuleID DisplayFlangerRateID 	= {DisplayObjectSmartKnob, SmartKnob_Flanger_Rate};
DisplayModuleID DisplayFlangerDelayID 	= {DisplayObjectSmartKnob, SmartKnob_Flanger_Delay};
DisplayModuleID DisplayFlangerSwitchID 	= {DisplayObjectSwitch, Switch_Flanger};

DisplayModuleID DisplayWahFreqLowID 	= {DisplayObjectSmartSlider, Slider_Wah_freq_low};
DisplayModuleID DisplayWahFreqHighID 	= {DisplayObjectSmartSlider, Slider_Wah_freq_high};
DisplayModuleID DisplayWahFreqDeltaID 	= {DisplayObjectSmartKnob, SmartKnob_Wah_rate};
DisplayModuleID DisplayWahQID 			= {DisplayObjectSmartSlider, Slider_Wah_q};
DisplayModuleID DisplayWahSwitchID		= {DisplayObjectSwitch, Switch_Wah};

DisplayModuleID DisplayOverdriveSwitchID	= {DisplayObjectSwitch, Switch_Overdrive};

DisplayModuleID DisplayReverbSwitchID	= {DisplayObjectSwitch, Switch_Reverb};

//////////////////////////////
//	Display buffer and buffer pointers
//////////////////////////////
uint8_t UartMsgReceived;
uint8_t DisplayTxBuffer[MSG_SIZE]; 								// Buffer used for display transmission
uint8_t DisplayRxBuffer[MSG_SIZE];								// Buffer used for display reception
uint8_t IncomingMsgFromDisplay[MSG_FROM_DISPLAY_ARRAY_SIZE];	// Queue for incoming display messages
uint8_t IncomingMsgFromDisplay_WrPtr;							// Keeps track of the next byte to write in the message queue
uint8_t IncomingMsgFromDisplay_RdPtr;							// Keeps track of the next byte to decode in the message queue

extern AudioProcess audioprocess;

void RegisterAudioModule(DisplayModuleID dmId, AudioModule* audioModule, uint8_t moduleMemberId)
{
	DisplayToModuleInterface d = {dmId, audioModule, moduleMemberId};
	DisplayModules.push_back(d);
}

void DecodeMsg(DisplayModuleID IncomingDisplayModule, uint8_t ObjectValue)
{
	for(DisplayToModuleInterface aModule : DisplayModules)
	{
		if(IncomingDisplayModule == aModule)
		{
			(*aModule.AudioModulePtr).SetMemberValue(aModule.ModuleMemberId, ObjectValue);
		}
	}
}

void RegisterModules()
{
	// Register volume module
	RegisterAudioModule(DisplayVolumeID, 		&audioprocess.volume, audioprocess.volume.ModifiableMembers::Volume);
	RegisterAudioModule(DisplayMicBoostID, 		&audioprocess.volume, audioprocess.volume.ModifiableMembers::MicBoost);
	RegisterAudioModule(DisplayGainOutID, 		&audioprocess.volume, audioprocess.volume.ModifiableMembers::GainOut);
	RegisterAudioModule(DisplayGainLineInID, 	&audioprocess.volume, audioprocess.volume.ModifiableMembers::GainLineIn);

	// Register flanger module
	RegisterAudioModule(DisplayFlangerRateID, 	&audioprocess.flanger, audioprocess.flanger.ModifiableMembers::Rate);
	RegisterAudioModule(DisplayFlangerDelayID, 	&audioprocess.flanger, audioprocess.flanger.ModifiableMembers::DelayOffset);
	RegisterAudioModule(DisplayFlangerSwitchID, &audioprocess.flanger, audioprocess.flanger.ModifiableMembers::Enable);

	// Register biquad module
	RegisterAudioModule(DisplayEqBassID, 		&audioprocess.biquad, audioprocess.biquad.ModifiableMembers::Bass);
	RegisterAudioModule(DisplayEqMidID, 		&audioprocess.biquad, audioprocess.biquad.ModifiableMembers::Mid);
	RegisterAudioModule(DisplayEqTrebleID, 		&audioprocess.biquad, audioprocess.biquad.ModifiableMembers::Treble);

	// Register wah module
	RegisterAudioModule(DisplayWahFreqLowID, 	&audioprocess.wah, audioprocess.wah.ModifiableMembers::FreqLow);
	RegisterAudioModule(DisplayWahFreqHighID, 	&audioprocess.wah, audioprocess.wah.ModifiableMembers::FreqHigh);
	RegisterAudioModule(DisplayWahQID, 			&audioprocess.wah, audioprocess.wah.ModifiableMembers::Q);
	RegisterAudioModule(DisplayWahFreqDeltaID, 	&audioprocess.wah, audioprocess.wah.ModifiableMembers::FreqDelta);
	RegisterAudioModule(DisplayWahSwitchID, 	&audioprocess.wah, audioprocess.wah.ModifiableMembers::Enable);

	// Register overdrive module
	RegisterAudioModule(DisplayOverdriveSwitchID, &audioprocess.overdrive, audioprocess.overdrive.ModifiableMembers::Enable);

	// Register reverb module
	RegisterAudioModule(DisplayReverbSwitchID, &audioprocess.reverb, audioprocess.reverb.ModifiableMembers::Enable);
}

void InitDisplayModules(){
	// Send all register AudioModule member values to display
	for(DisplayToModuleInterface aModule : DisplayModules)
	{
		int moduleNumber = aModule.Id.Number;
		int moduleObject = aModule.Id.Object;
		int value = (*aModule.AudioModulePtr).GetMemberValue(aModule.ModuleMemberId);
		DisplaySendMsg(moduleObject, moduleNumber, value);
		HAL_UART_Receive(&UartHandle, (uint8_t *) DisplayRxBuffer, 1, 1000);
	}
}

void DisplayInit(void)
{
	RegisterModules();

	InitDisplayModules();
}

void DisplayDecodeMsg(void)
{
	uint8_t DisplayMsgType = IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 0];

	if (DisplayMsgType == DisplayMsgObject)
	{
		uint8_t DisplayObject = IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 1];
		uint8_t ObjectNumber = IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 2];
		DisplayModuleID dm = {DisplayObject, ObjectNumber};
		float ObjectValue = (float)IncomingMsgFromDisplay[IncomingMsgFromDisplay_RdPtr + 4];

		DecodeMsg(dm, ObjectValue);

	}
	IncomingMsgFromDisplay_RdPtr = IncomingMsgFromDisplay_RdPtr + MSG_SIZE;
	if(IncomingMsgFromDisplay_RdPtr >= MSG_FROM_DISPLAY_ARRAY_SIZE)
	{
		IncomingMsgFromDisplay_RdPtr = 0;
	}

}

void DisplaySendMsg(uint8_t ObjectType, uint8_t ObjectNumber, uint8_t Value)
{
	DisplayTxBuffer[0] = 0x01;
	DisplayTxBuffer[1] = ObjectType;
	DisplayTxBuffer[2] = ObjectNumber;
	DisplayTxBuffer[3] = 0x00;
	DisplayTxBuffer[4] = Value;
	DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

	if (HAL_UART_Transmit_IT(&UartHandle, (uint8_t*) DisplayTxBuffer, MSG_SIZE) != HAL_OK) {
			Error_Handler(HAL_ERROR_UART_TRANSMIT);
		}
}

extern int NumberOfUARTWordToReceive;
void DisplaySetVolume(uint8_t Value)
{
	NumberOfUARTWordToReceive = 1;
	DisplayPrepareMsgReceive(NumberOfUARTWordToReceive);

	DisplayTxBuffer[0] = 0x01;
	DisplayTxBuffer[1] = DisplayVolumeID.Object;
	DisplayTxBuffer[2] = DisplayVolumeID.Number;
	DisplayTxBuffer[3] = 0x00;
	DisplayTxBuffer[4] = Value;
	DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

	audioprocess.volume.SetMemberValue(audioprocess.volume.ModifiableMembers::Volume, Value);

	if (HAL_UART_Transmit_IT(&UartHandle, (uint8_t*) DisplayTxBuffer, MSG_SIZE) != HAL_OK) {
			Error_Handler(HAL_ERROR_UART_TRANSMIT);
		}
}

void DisplayPrepareMsgReceive(uint8_t bytes_to_receive) {
	if (UartHandle.RxState != HAL_UART_STATE_BUSY_RX) {
		// Reset transmission flag
//		if(UartMsgReceived == 1)
//		{
//			UartMsgReceived = 0;
			//HAL_UART_AbortReceive(&UartHandle);
			if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *) DisplayRxBuffer, bytes_to_receive)
					!= HAL_OK) {
				Error_Handler(HAL_ERROR_UART_RECEIVE);
			}
//		}
	}
	else if (UartHandle.RxState == HAL_UART_STATE_BUSY_RX) {
		HAL_UART_AbortReceive(&UartHandle);
		if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *) DisplayRxBuffer, bytes_to_receive)
				!= HAL_OK) {
			Error_Handler(HAL_ERROR_UART_RECEIVE);
		}
	}
}




