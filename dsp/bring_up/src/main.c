#include "main.h"
#include "wm8731.h"
#include "arm_math.h"

__IO uint32_t ButtonOnBoardStatus = 0;  /* set to 1 after User Button interrupt  */

#define __ATTR_RAM_D2 __attribute__ ((section(".RAM_D2"))) __attribute__ ((aligned (4)))

/** I2S receive buffers - placed in D2 memory */
static uint32_t g_glueI2sRxBuff[256] __ATTR_RAM_D2;

/** I2S transmit buffers - placed in D2 memory */
static uint32_t g_glueI2sTxBuff[256] __ATTR_RAM_D2;

static uint16_t I2S_in_buf[256] __ATTR_RAM_D2;
static uint16_t I2S_out_buf[256] __ATTR_RAM_D2;
static float LoopbackBuffer[256] __ATTR_RAM_D2;

bool PROCESS_AUDIO;
float VOLUME = 1;

int main(void)
{
  MPU_Conf();
  CPU_CACHE_Enable();
  HAL_Init();
  /* Configure the system clock to 400 MHz */
  SystemClock_Config();

  /* Configure LED1, LED2 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  InitI2S();

  InitDMA();

  InitRotaryEncoder(); // Uses TIM1

  InitTim3(); // Interrupts every 250 ms to avoid spamming UART Rx to display when manipulating rotary encoder

  InitUart();

  InitGPIO();

  InitI2C();

  InitCodec();

  /*
  // Configure User push-button in Interrupt mode // Wait for User push-button press before starting the Communication.
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);
  while(ButtonOnBoardStatus == 0)
  {
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(100);
  }
  */

  DisplayTxBuffer[0] = 0x01;
  DisplayTxBuffer[1] = 0x07;
  DisplayTxBuffer[2] = 0x01;
  DisplayTxBuffer[3] = 0x00;
  DisplayTxBuffer[4] = 0x0a;
  DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

  if(HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)DisplayTxBuffer, 6)!= HAL_OK)
  {
  Error_Handler(HAL_ERROR_UART_TRANSMIT);
  }

  if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)DisplayRxBuffer, 1) != HAL_OK)
  {

   Error_Handler(HAL_ERROR_UART_RECEIVE);
  }

  BSP_LED_Off(LED_GREEN);
  
  for(int i = 0; i < 256; i++)
  {
    g_glueI2sTxBuff[i] = 0;
    g_glueI2sRxBuff[i] = 0;
    LoopbackBuffer[i] = 0;
  }


  //SCB_CleanDCache_by_Addr((uint32_t*)(((uint32_t)g_glueI2sTxBuff) & ~(uint32_t)0x1F), 1024);
  //SCB_CleanDCache_by_Addr((uint32_t*)&g_glueI2sTxBuff[0], 1024+32);
  //SCB_InvalidateDCache_by_Addr((uint32_t*)(((uint32_t)g_glueI2sRxBuff) & ~(uint32_t)0x1F), 1024);
  //SCB_InvalidateDCache_by_Addr((uint32_t*)&g_glueI2sRxBuff[0], 1024+32);

  HAL_I2SEx_TransmitReceive_DMA(&I2sHandle, (uint16_t*)g_glueI2sTxBuff, (uint16_t*)g_glueI2sRxBuff, 256);



  while (1)
  {
    PrepareDisplayMsgReceive();
    DecodeDisplayMsg();

    if(PROCESS_AUDIO == true)
    {
    	arm_q15_to_float((q15_t*)I2S_in_buf, LoopbackBuffer, 256);
    	for(int i = 0; i < 256; i++)
    	{
    		LoopbackBuffer[i] = LoopbackBuffer[i] * VOLUME;
    	}
    	arm_float_to_q15(LoopbackBuffer, (q15_t*)I2S_out_buf, 256);
    }
  }
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Turn LED_BLUE on: Transfer in transmission process is correct */
  BSP_LED_On(LED_BLUE);   
}

// When receiving byte from display, append it to array
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  IncomingMsgFromDisplay[IncomingMsgFromDisplay_WrPtr++] = DisplayRxBuffer[0];
  if(IncomingMsgFromDisplay_WrPtr==MSG_FROM_DISPLAY_ARRAY_SIZE)
  {
    IncomingMsgFromDisplay_WrPtr=0;
  }

  BSP_LED_Toggle(LED_BLUE);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  Error_Handler(HAL_ERROR_UART_CALLBACK);
}

int8_t RotataryCheckInProgress = 0;
int beenhere = 0;
void checkRotaryEncoder()
{

 // Update if value changes
  if(value != TIM1->CNT)
  {
    beenhere = 1;

    value = TIM1->CNT;

    if(value > 100 && value < 149)
    {
      value = 100;
    }
    if((value > 150) && (value < 200))
    {
      value = 1;
    }
    if(value == 0)
    {
      value = 1;
    }

    VOLUME = (float)value / 100;

    if(selected_gauge == Left)
    {
      left_gauge_value = value;
    }

    if(selected_gauge == Right)
    {
      right_gauge_value = value;
    }
    SendValueToGauge(selected_gauge, value);

    TIM1->CNT = value;

    beenhere = 0;
  }
}

// Periodic callback to check if rotary encoder value has changed
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(RotataryCheckInProgress != 1)
  {
    checkRotaryEncoder();
  }
}

// Callback when user button is pressed
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == USER_BUTTON_PIN)
  {  
    ButtonOnBoardStatus = 1;
  }
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Toggle LED1: Transfer in transmission process is correct */
  BSP_LED_Toggle(LED1);
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Toggle LED1: Transfer in reception process is correct */
  BSP_LED_Toggle(LED1);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  /** Error_Handler() function is called when error occurs.
    * 1- When Slave don't acknowledge it's address, Master restarts communication.
    * 2- When Master don't acknowledge the last data transferred, Slave don't care in this example.
    */
  if (HAL_I2C_GetError(I2cHandle) != HAL_I2C_ERROR_AF)
  {
    /* Turn Off LED1 */
    BSP_LED_Off(LED1);

    /* Turn On LED3 */
    BSP_LED_On(LED3);
  }
}

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	/*
  SCB_InvalidateDCache_by_Addr((uint32_t*)&g_glueI2sRxBuff[0], 1024+32);

  for(int i = 0; i < 256; i++)
  {
	  I2S_in_buf[i]  = g_glueI2sRxBuff[i];
	  g_glueI2sTxBuff[i] = I2S_out_buf[i];
	  //g_glueI2sTxBuff[i] = g_glueI2sRxBuff[i];
  }
  SCB_CleanDCache_by_Addr((uint32_t*)&g_glueI2sTxBuff[0], 1024+32);
  PROCESS_AUDIO = 1;
  */
}


void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	SCB_InvalidateDCache_by_Addr((uint32_t*)&g_glueI2sRxBuff[0], 1024+32);

  for(int i = 0; i < 256; i++)
  {
	  I2S_in_buf[i]  = g_glueI2sRxBuff[i];
	  g_glueI2sTxBuff[i] = I2S_out_buf[i];
	  //g_glueI2sTxBuff[i] = g_glueI2sRxBuff[i];
  }
  SCB_CleanDCache_by_Addr((uint32_t*)&g_glueI2sTxBuff[0], 1024+32);
/*
  arm_q15_to_float((q15_t*)LoopbackBuffer_16, LoopbackBuffer, 128);
  for(int i = 0; i < 128; i++)
  {
    LoopbackBuffer[i] = LoopbackBuffer[i] * VOLUME;
  }
  arm_float_to_q15(LoopbackBuffer, (q15_t*)LoopbackBuffer_16, 128);

  for(int i = 0; i < 128; i++)
  {
    g_glueI2sTxBuff[i+128] = LoopbackBuffer_16[i];
  }
  */
  PROCESS_AUDIO = 1;
}

void HAL_I2S_DMAError(I2S_HandleTypeDef *I2sHandle)
{
  BSP_LED_On(LED_RED);
}

uint8_t ERROR_NO = 0;
void Error_Handler(uint8_t error_no)
{
  ERROR_NO = error_no;
  /* Turn LED_RED on */
  BSP_LED_On(LED_RED);

  while(1)
  {
  }  
}







