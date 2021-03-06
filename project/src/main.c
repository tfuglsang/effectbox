#include "main.h"
#include "arm_math.h"
#include <arm_const_structs.h>
#include <codec.h>
#include <display.h>
#include <init.h>
#include <audio_process.h>

/*
 AHB SRAM1 is mapped at address 0x3000 0000 and accessible by all system
masters except BDMA through D2 domain AHB matrix. AHB SRAM1 can be used
as DMA buffers to store peripheral input/output data in D2 domain
 */
#define __ATTR_RAM_D2 __attribute__ ((section(".RAM_D2"))) __attribute__ ((aligned (4)))

/** I2S DMA buffers - placed in D2 memory */
volatile uint32_t g_glueI2sRxBuff[I2S_FRAME_SIZE] __ATTR_RAM_D2;
volatile uint32_t g_glueI2sTxBuff[I2S_FRAME_SIZE] __ATTR_RAM_D2;

// Incoming I2S DMA buffers are copied here (in interrupt)
volatile q31_t I2S_InBuf[I2S_FRAME_SIZE / 2] __ATTR_RAM_D2;

// Audio data is copied to here (as mono)
float AudioProcessInBuf[AUDIO_BLOCKSIZE] __ATTR_RAM_D2;

// Indicates if a frame is ready to be processed
volatile bool I2S_FRAME_RECEIVED;

// This is the length of the msg we expect to receive over UART (from display)
int NumberOfUARTWordToReceive = 1;

int main(void) {

	MPU_Conf();
	CPU_CACHE_Enable();
	HAL_Init();
	// Configure the system clock to 400 MHz
	SystemClock_Config();

	// Configure LED1, LED2 and LED3
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	// Flick GPIO pull reset pin on display
	InitGPIO();

	InitI2S();

	// Setup ping-pong DMA
	InitDMA();

	InitUart();

	InitI2C();

	AudioProcessInit(AUDIO_BLOCKSIZE, AudioProcessInBuf);

	CodecInit(MODE_LINE_IN);

	// Wait some time to make sure display has booted
	HAL_Delay(3000);

	// Set init values to display
	DisplayInit();

	// Wait for display to refresh
	HAL_Delay(500);

	// Use TIM1 for rotary encoder
	InitRotaryEncoder();
	// Set encoder value to 100 (default start-up volume)
	TIM1->CNT = 100;

	for (int i = 0; i < I2S_FRAME_SIZE; i++) {
		g_glueI2sTxBuff[i] = 0;
		g_glueI2sRxBuff[i] = 0;
	}

	// Start DMA transmission
	HAL_I2SEx_TransmitReceive_DMA(&I2sHandle, (uint16_t*) g_glueI2sTxBuff, (uint16_t*) g_glueI2sRxBuff, I2S_FRAME_SIZE);

	I2sHandle.hdmarx->XferHalfCpltCallback = RxHalfTransferCplt;
	I2sHandle.hdmarx->XferCpltCallback  = RxFullTransferCplt;

	I2sHandle.hdmatx->XferHalfCpltCallback = TxHalfTransferCplt;
	I2sHandle.hdmatx->XferCpltCallback  = TxFullTransferCplt;

	//SCB_InvalidateDCache_by_Addr((uint32_t*)(((uint32_t)g_glueI2sRxBuff) & ~(uint32_t)0x1F), 1024);
	//SCB_InvalidateDCache_by_Addr((uint32_t*)&g_glueI2sRxBuff[0], 1024+32);

	while (1) {

		if (I2S_FRAME_RECEIVED == true ) {
			I2S_FRAME_RECEIVED = false;

			for(int i = 0; i < AUDIO_BLOCKSIZE ; i++)
			{
				// Cast to float and cap values between -1 to 1
				AudioProcessInBuf[i] = (float)I2S_InBuf[i * 2] / 2147483648;
			}

			AudioProcessApply();
		}
	}
}

/* -------------------------------------
  CALLBACKS
 ------------------------------------- */

void RxHalfTransferCplt()
{
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		I2S_InBuf[i] = (q31_t)g_glueI2sRxBuff[i];
	}
	I2S_FRAME_RECEIVED = 1;
}
void RxFullTransferCplt()
{
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		I2S_InBuf[i] = (q31_t)g_glueI2sRxBuff[i + I2S_FRAME_SIZE/2];
	}
	I2S_FRAME_RECEIVED = 1;
}
void TxHalfTransferCplt()
{
	float* OutputBuf = AudioProcessGetOutputBuffer();
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		g_glueI2sTxBuff[i] = (q31_t)OutputBuf[i];
	}
}
void TxFullTransferCplt()
{
	float* OutputBuf = AudioProcessGetOutputBuffer();
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		g_glueI2sTxBuff[i + I2S_FRAME_SIZE/2] = (q31_t)OutputBuf[i];
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) {
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {

	if(NumberOfUARTWordToReceive == MSG_SIZE)
	{
		for(int i = 0; i < NumberOfUARTWordToReceive; i++)
		{
			IncomingMsgFromDisplay[IncomingMsgFromDisplay_WrPtr++] = DisplayRxBuffer[i];
		}
	}

	// Generate SW interrupt to decode message
	__HAL_GPIO_EXTI_GENERATE_SWIT(GPIO_PIN_15);


	if (IncomingMsgFromDisplay_WrPtr >= MSG_FROM_DISPLAY_ARRAY_SIZE) {
		IncomingMsgFromDisplay_WrPtr=0;
	}
	UartMsgReceived = 1;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
	Error_Handler(HAL_ERROR_UART_CALLBACK);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // SW GPIO interrupt that fires after display msg has been received
  if (GPIO_Pin == GPIO_PIN_15)
  {
	  if(NumberOfUARTWordToReceive == MSG_SIZE)
	  {
		  DisplayDecodeMsg();
	  }
	  NumberOfUARTWordToReceive = 6;
	  DisplayPrepareMsgReceive(NumberOfUARTWordToReceive);
  }
}


int8_t RotataryCheckInProgress = 0;
int RotaryValue = 100;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { // Periodic callback to check if rotary encoder value has changed
	if (RotataryCheckInProgress != 1) {
		RotataryCheckInProgress = 1;
		// Update if value changes
		if (RotaryValue != TIM1->CNT) {

			RotaryValue = TIM1->CNT;

			if (RotaryValue > 100 && RotaryValue < 149) {
				RotaryValue = 100;
			}
			if ((RotaryValue > 150) && (RotaryValue <= 200)) {
				RotaryValue = 1;
			}
			if (RotaryValue == 0) {
				RotaryValue = 1;
			}

			//RotaryValue = (float) RotaryValue / 100;

			DisplaySetVolume(RotaryValue);

			TIM1->CNT = RotaryValue;
		}
		RotataryCheckInProgress = 0;
	}
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2cHandle) {
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2cHandle) {
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle) {
	/** Error_Handler() function is called when error occurs.
	 * 1- When Slave don't acknowledge it's address, Master restarts communication.
	 * 2- When Master don't acknowledge the last data transferred, Slave don't care in this example.
	 */
	if (HAL_I2C_GetError(I2cHandle) != HAL_I2C_ERROR_AF) {
		/* Turn Off LED1 */
		BSP_LED_Off(LED1);

		/* Turn On LED3 */
		BSP_LED_On(LED3);
	}
}

void HAL_I2S_DMAError(I2S_HandleTypeDef *I2sHandle) {
	BSP_LED_On(LED_RED);
}

uint8_t ERROR_NO = 0;
void Error_Handler(uint8_t error_no) {
	ERROR_NO = error_no;
	/* Turn LED_RED on */
	BSP_LED_On(LED_RED);

	while (1) {
	}
}


