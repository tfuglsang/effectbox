/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo_144.h"
#include "HAL_error_numbers.h"
#include "stdbool.h"

#define I2C_ADDRESS        0x34

/* I2C TIMING Register define when I2C clock source is APB1 (SYSCLK/4) */
/* I2C TIMING is calculated in case of the I2C Clock source is the APB1CLK = 100 MHz */
/* This example use TIMING to 0x00901954 to reach 400 kHz speed (Rise time = 100 ns, Fall time = 10 ns) */
#define I2C_TIMING      0x00901954

// UART instance for touch display interfacing
UART_HandleTypeDef UartHandle;

// I2C instance for codec communication
I2C_HandleTypeDef I2cHandle;

// I2S for codec audio
I2S_HandleTypeDef I2sHandle;

// DMA for codec audio
DMA_HandleTypeDef DMA_I2s_tx_Handle;
DMA_HandleTypeDef DMA_I2s_rx_Handle;

// Timer 1 used for rotary encoding counting
TIM_Encoder_InitTypeDef RotEncoder;
TIM_HandleTypeDef timer_1;

// Timer 3 used to check state of rotary, and if state has changed, then update display
TIM_HandleTypeDef timer_3;
  
/* Buffer used for display transmission */
uint8_t DisplayTxBuffer[6];

/* Buffer used for display reception */
uint8_t DisplayRxBuffer[6];

#define MSG_FROM_DISPLAY_ARRAY_SIZE 100
static uint8_t IncomingMsgFromDisplay[MSG_FROM_DISPLAY_ARRAY_SIZE];
static uint8_t IncomingMsgFromDisplay_WrPtr = 0;
static enum SelectedGauge {Left = 0, Right = 1};
static uint8_t value = 0;
static uint8_t selected_gauge = Left;
static uint8_t left_gauge_value = 0;
static uint8_t right_gauge_value = 0;

void DecodeDisplayMsg(void);
void PrepareDisplayMsgReceive(void);
void SendValueToGauge(uint8_t gauge_number, uint8_t value);

void InitCodec(void);
void InitRotaryEncoder(void);
void InitTim3(void);
void InitUart(void);
void InitGPIO(void);
void InitI2C(void);
void InitI2S(void);
void InitDMA(void);
void MPU_Conf(void);

void Reset_DisplayRxBuffer(void);

void SystemClock_Config(void);
void Error_Handler(uint8_t error_no);
uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void CPU_CACHE_Enable(void);


#endif /* __MAIN_H */
