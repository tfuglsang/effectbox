#include "main.h"
#include "arm_math.h"
#include <arm_const_structs.h>
#include <codec.h>
#include <display.h>
#include <init.h>
#include <audio_process.h>

bool I2S_FRAME_RECEIVED;

#define __ATTR_RAM_D2 __attribute__ ((section(".RAM_D2"))) __attribute__ ((aligned (4)))

/** I2S buffers - placed in D2 memory */
static uint32_t g_glueI2sRxBuff[I2S_FRAME_SIZE] __ATTR_RAM_D2;
static uint32_t g_glueI2sTxBuff[I2S_FRAME_SIZE] __ATTR_RAM_D2;

int NumberOfUARTWordToReceive = 1;

static q31_t I2S_in_buf[AUDIO_BLOCKSIZE] __ATTR_RAM_D2;

t_audio_process_data audio_process_struct;

q31_t tmp[I2S_FRAME_SIZE/2];
float tmp_f[I2S_FRAME_SIZE/2];

int main(void) {

	MPU_Conf();
	CPU_CACHE_Enable();
	HAL_Init();
	/* Configure the system clock to 400 MHz */
	SystemClock_Config();

	/* Configure LED1, LED2 and LED3 */
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	InitGPIO(); // flick GPIO to reset display

	InitI2S();

	InitDMA();

	InitRotaryEncoder(); // Uses TIM1

	InitTim3(); // Interrupts every 250 ms to avoid spamming UART Rx to display when manipulating rotary encoder

	InitUart();

	InitI2C();

	audio_process_init(&audio_process_struct);

	codec_init(audio_process_struct.ACTIVE_CODEC_INPUT_INTERFACE);

	// Wait some time to make sure display has booted
	HAL_Delay(3000);
	// Set init values to display
	display_init();
	HAL_Delay(500);
	// Prepare to receive messages from display
	NumberOfUARTWordToReceive = 6;
	UART_DONE = 1;
	display_prepare_msg_receive(NumberOfUARTWordToReceive);

	for (int i = 0; i < I2S_FRAME_SIZE; i++) {
		g_glueI2sTxBuff[i] = 0;
		g_glueI2sRxBuff[i] = 0;
	}

	HAL_I2SEx_TransmitReceive_DMA(&I2sHandle, (uint16_t*) g_glueI2sTxBuff, (uint16_t*) g_glueI2sRxBuff, I2S_FRAME_SIZE);

	I2sHandle.hdmarx->XferHalfCpltCallback = RxHalfTransferCplt;
	I2sHandle.hdmarx->XferCpltCallback  = RxFullTransferCplt;

	I2sHandle.hdmatx->XferHalfCpltCallback = TxHalfTransferCplt;
	I2sHandle.hdmatx->XferCpltCallback  = TxFullTransferCplt;

	//SCB_InvalidateDCache_by_Addr((uint32_t*)(((uint32_t)g_glueI2sRxBuff) & ~(uint32_t)0x1F), 1024);
	//SCB_InvalidateDCache_by_Addr((uint32_t*)&g_glueI2sRxBuff[0], 1024+32);

	while (1) {
		//display_prepare_msg_receive(NumberOfWordToReceive);

		if (I2S_FRAME_RECEIVED == true ) {
			audio_process_apply(&audio_process_struct, audio_process_struct.input);
			I2S_FRAME_RECEIVED = false;
		}
	}
}

int8_t RotataryCheckInProgress = 0;
int beenhere = 0;
void checkRotaryEncoder() {
/*
	// Update if value changes
	if (KnobVolumeValue != TIM1->CNT) {
		beenhere = 1;

		KnobVolumeValue = TIM1->CNT;

		if (KnobVolumeValue > 100 && KnobVolumeValue < 149) {
			KnobVolumeValue = 100;
		}
		if ((KnobVolumeValue > 150) && (KnobVolumeValue <= 200)) {
			KnobVolumeValue = 1;
		}
		if (KnobVolumeValue == 0) {
			KnobVolumeValue = 1;
		}

		KnobVolumeValue = (float) KnobVolumeValue / 100;

		//SendValueToGauge(selected_gauge, value);

		TIM1->CNT = KnobVolumeValue;

		beenhere = 0;
	}
	*/
}


/* -------------------------------------
  CALLBACKS
 ------------------------------------- */

void RxHalfTransferCplt()
{
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		I2S_in_buf[i] = (q31_t)g_glueI2sRxBuff[i];
		audio_process_struct.input[i] = (float)I2S_in_buf[i];
	}
	I2S_FRAME_RECEIVED = 1;
}
void RxFullTransferCplt()
{
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		I2S_in_buf[i] = (q31_t)g_glueI2sRxBuff[i + I2S_FRAME_SIZE/2];
		audio_process_struct.input[i] = (float)I2S_in_buf[i];
	}
	I2S_FRAME_RECEIVED = 1;
}
void TxHalfTransferCplt()
{
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		g_glueI2sTxBuff[i] = (q31_t)audio_process_struct.output[i];
	}
}
void TxFullTransferCplt()
{
	for (int i = 0; i < I2S_FRAME_SIZE/2; i++) {
		g_glueI2sTxBuff[i + I2S_FRAME_SIZE/2] = (q31_t)audio_process_struct.output[i];
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

		// Generate SW interrupt to decode message
		__HAL_GPIO_EXTI_GENERATE_SWIT(GPIO_PIN_15);
	}

	if (IncomingMsgFromDisplay_WrPtr >= MSG_FROM_DISPLAY_ARRAY_SIZE) {
		IncomingMsgFromDisplay_WrPtr=0;
	}
	UART_DONE = 1;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
	Error_Handler(HAL_ERROR_UART_CALLBACK);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_15)
  {
	  display_decode_msg();
	  display_prepare_msg_receive(NumberOfUARTWordToReceive);
  }
}

// Periodic callback to check if rotary encoder value has changed
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (RotataryCheckInProgress != 1) {
		checkRotaryEncoder();
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


