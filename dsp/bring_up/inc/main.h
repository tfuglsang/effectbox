/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo_144.h"
#include "HAL_error_numbers.h"
#include "stdbool.h"

/* Definition for USARTx clock resources */
#define USARTx                           USART6
#define USARTx_FORCE_RESET()             __HAL_RCC_USART6_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART6_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_6
#define USARTx_TX_GPIO_PORT              GPIOC
#define USARTx_TX_AF                     GPIO_AF7_USART6
#define USARTx_RX_PIN                    GPIO_PIN_7
#define USARTx_RX_GPIO_PORT              GPIOC
#define USARTx_RX_AF                     GPIO_AF7_USART6

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART6_IRQn
#define USARTx_IRQHandler                USART6_IRQHandler

/* Definition for I2Cx clock resources */
#define I2Cx                            I2C2
#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C2_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()

#define I2Cx_FORCE_RESET()              __HAL_RCC_I2C2_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __HAL_RCC_I2C2_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_1
#define I2Cx_SCL_GPIO_PORT              GPIOF
#define I2Cx_SDA_PIN                    GPIO_PIN_0
#define I2Cx_SDA_GPIO_PORT              GPIOF
#define I2Cx_SCL_SDA_AF                 GPIO_AF4_I2C2

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C2_EV_IRQn
#define I2Cx_ER_IRQn                    I2C2_ER_IRQn
#define I2Cx_EV_IRQHandler              I2C2_EV_IRQHandler
#define I2Cx_ER_IRQHandler              I2C2_ER_IRQHandler

#define I2C_ADDRESS        0x34

/* I2C TIMING Register define when I2C clock source is APB1 (SYSCLK/4) */
/* I2C TIMING is calculated in case of the I2C Clock source is the APB1CLK = 100 MHz */
/* This example use TIMING to 0x00901954 to reach 400 kHz speed (Rise time = 100 ns, Fall time = 10 ns) */
#define I2C_TIMING      0x00901954

// UART for touch display interfacing
UART_HandleTypeDef UartHandle;

I2C_HandleTypeDef I2cHandle;

I2S_HandleTypeDef I2sHandle;

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

void decodeDisplayMsg(void);
void prepareDisplayMsgReceive(void);
void sendValueDisplayGauge(uint8_t gauge_number, uint8_t value);
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
