#include "main.h"
#include "wm8731.h"

__IO uint32_t ButtonOnBoardStatus = 0;  /* set to 1 after User Button interrupt  */

#define __ATTR_RAM_D2	__attribute__ ((section(".RAM_D2"))) __attribute__ ((aligned (4)))

/** I2S receive buffers - placed in D2 memory */
static uint8_t g_glueI2sRxBuff[3][1024] __attribute__((section("RAM_D2"))) = {0};

/** I2S transmit buffers - placed in D2 memory */
static uint8_t g_glueI2sTxBuff[3][1024] __attribute__((section("RAM_D2"))) = {0};

uint16_t sineWave[64] __ATTR_RAM_D2;
uint16_t sineWave1[64]= {
        0,2048,0,2447,0,2831,0,3185,0,3495,0,3750,0,3939,0,4056,0,
        4095,0,4056,0,3939,0,3750,0,3495,0,3185,0,2831,0,2447,0,
        2048,0,1648,0,1264,0,910,0,600,0,345,0,156,0,39,0,
        0,0,39,0,156,0,345,0,600,0,910,0,1264,0,1648 } ;

// Message pattern from display, when buttons has been pressed
uint8_t Button_1[] = {0x07,0x21,0x00,0x00,0x00,0x26};
uint8_t Button_2[] = {0x07,0x21,0x01,0x00,0x00,0x27};

enum SelectedGauge {Left = 0, Right = 1};
uint8_t value = 0;
uint8_t selected_gauge = Left;
uint8_t left_gauge_value = 0;
uint8_t right_gauge_value = 0;

#define MSG_FROM_DISPLAY_ARRAY_SIZE 100
uint8_t IncomingMsgFromDisplay[MSG_FROM_DISPLAY_ARRAY_SIZE];
uint8_t IncomingMsgFromDisplay_WrPtr = 0;

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

  InitRotaryEncoder(); // Uses TIM1

  InitTim3(); // Interrupts every 250 ms to avoid spamming UART Rx to display when manipulating rotary encoder

  InitUart();

  InitI2C();

  InitI2S();

  InitDMA();

  InitGPIO();

  /* Configure User push-button in Interrupt mode */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Wait for User push-button press before starting the Communication. */
  while(ButtonOnBoardStatus == 0)
  {
    /* Toggle LED_GREEN*/
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(100);
  }

  // Reset codec
//  uint8_t TxBuffer[2];
//  TxBuffer[0] = 0x0f << 1;
//  TxBuffer[1] = 0x00;
//  do
//  {
//    if(HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)TxBuffer, 2)!= HAL_OK)
//    {
//      /* Error_Handler() function is called when error occurs. */
//      Error_Handler(34);
//    }
//    while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
//    {
//    }
//  }
//  while(HAL_I2C_GetError(&I2cHandle) == HAL_I2C_ERROR_AF);

  // CODEC MASTER
  SendCodecCmd(WM8731_REG_RESET, 0x00);
  SendCodecCmd(0x00, 0x17); // l in mute = 0
  SendCodecCmd(0x01, 0x17); // r in mute = 0
  SendCodecCmd(0x04, 0x12); // dac select = 1, mute mic = 1
  SendCodecCmd(0x05, 0x00); // dac mute = 0,  adc hp filter enable
  SendCodecCmd(0x06, 0x0A); // microphone powerdown = 1
  SendCodecCmd(0x07, 0x4E); // master mode, 16 bit, i2s format
  SendCodecCmd(0x09, 0x01); // active control = 1


  /*
  // Passthrough: line_in -> hp out
  SendCodecCmd(WM8731_REG_RESET, 0x00);
  SendCodecCmd(0x04, 0x0A); // l in mute = 0
  SendCodecCmd(0x06, 0x0E); // r in mute = 0
  SendCodecCmd(0x09, 0x01); // active control = 1
  */

  DisplayTxBuffer[0] = 0x01;
  DisplayTxBuffer[1] = 0x07;
  DisplayTxBuffer[2] = 0x01;
  DisplayTxBuffer[3] = 0x00;
  DisplayTxBuffer[4] = 0x0a;
  DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

  if(HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)DisplayTxBuffer, 6)!= HAL_OK)
  {
	Error_Handler(9);
  }

  if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)DisplayRxBuffer, 1) != HAL_OK)
  {

	 Error_Handler(17);
  }

  BSP_LED_Off(LED_GREEN);
  
//  for(int i = 0; i < 64; i++)
//  {
//	  sineWave[i] = sineWave1[i];
//  }

//  SCB_CleanDCache_by_Addr((uint32_t*)(((uint32_t)sineWave) & ~(uint32_t)0x1F), 128);
//  HAL_I2S_Transmit(&I2sHandle, sineWave, 64,1000);
//  SCB_CleanDCache_by_Addr((uint32_t*)(((uint32_t)sineWave) & ~(uint32_t)0x1F), 128);
//  if(HAL_I2S_Transmit_DMA(&I2sHandle, sineWave, 64) != HAL_OK)
//  {
//   	  Error_Handler(87);
//  }

  HAL_I2SEx_TransmitReceive_DMA(&I2sHandle, (uint16_t*)g_glueI2sTxBuff, (uint16_t*)g_glueI2sRxBuff, 512);

  while (1)
  {
      if(UartHandle.RxState != HAL_UART_STATE_BUSY_RX)
        {
			/* Reset transmission flag */
			HAL_UART_AbortReceive(&UartHandle);
			if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)DisplayRxBuffer, 1) != HAL_OK)
			{
			Error_Handler(20);
			}
        }

      while(0 < IncomingMsgFromDisplay_WrPtr)
      {
    	  if(IncomingMsgFromDisplay[0] == 6) // if the next element is acknowledge, increment read ptr and do nothing
    	  {
    		  IncomingMsgFromDisplay_WrPtr--;
    	  }
    	  else
    	  {
    		  if(IncomingMsgFromDisplay[0] == 7) // cmd button pressed
    		  {
    			  if(IncomingMsgFromDisplay_WrPtr >= 6) // if a full button msg has been received, start decoding
    			  {
    				 // Find out what button has been pressed
					if (Buffercmp(IncomingMsgFromDisplay, Button_1, 6) == 0 )
					{
						selected_gauge = Left;
						TIM1->CNT = left_gauge_value;
						value = left_gauge_value;
						SendValueToGauge(selected_gauge, value);
					}
					else if (Buffercmp(IncomingMsgFromDisplay, Button_2, 6) == 0 )
					{
						selected_gauge = Right;
						TIM1->CNT = right_gauge_value;
						value = right_gauge_value;
						SendValueToGauge(selected_gauge, value);
					}
					IncomingMsgFromDisplay_WrPtr = IncomingMsgFromDisplay_WrPtr - 6;
    			  }
    			  else
    			  {
    				  break;
    			  }

    		  }
    	  }
      }
  }   
 
}
int beenhere = 0;
void CheckRotaryEncoder()
{

 // Update if value changes
	if(value != TIM1->CNT)
	{
		beenhere = 1;

		if(TIM1->CNT > 100)
		{
			TIM1->CNT = 100;
		}
		if(TIM1->CNT <= 1)
		{
			TIM1->CNT = 1;
		}
		value = TIM1->CNT;

		if(selected_gauge == Left)
		{
			left_gauge_value = value;
		}

		if(selected_gauge == Right)
		{
			right_gauge_value = value;
		}
		SendValueToGauge(selected_gauge, value);
		beenhere = 0;
	}
}

void SendValueToGauge(uint8_t gauge_number, uint8_t value)
{
	DisplayTxBuffer[0] = 0x01;
	DisplayTxBuffer[1] = 0x07;
	DisplayTxBuffer[2] = gauge_number;
	DisplayTxBuffer[3] = 0x00;
	DisplayTxBuffer[4] = value;
	DisplayTxBuffer[5] = DisplayTxBuffer[0] ^ DisplayTxBuffer[1] ^ DisplayTxBuffer[2] ^ DisplayTxBuffer[3] ^ DisplayTxBuffer[4];

  if(UartHandle.gState != HAL_UART_STATE_BUSY_TX)
  {
	  HAL_UART_AbortReceive(&UartHandle);
	  Reset_DisplayRxBuffer();

	  if(HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)DisplayTxBuffer, 6)!= HAL_OK)
	  {
		Error_Handler(9);
	  }

      if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)DisplayRxBuffer, 1) != HAL_OK)
      {
      Error_Handler(18);
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
  Error_Handler(11);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  //BSP_LED_Toggle(LED_BLUE);
  if(beenhere != 1)
  {
	  CheckRotaryEncoder();
  }
}

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







