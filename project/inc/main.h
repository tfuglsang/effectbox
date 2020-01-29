/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo_144.h"
#include "HAL_error_numbers.h"
#include "stdbool.h"

#define I2S_FRAME_SIZE 512

#define I2C_ADDRESS        0x34

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

// UART instance for touch display interfacing
UART_HandleTypeDef UartHandle;

void TxFullTransferCplt();
void TxHalfTransferCplt();
void RxFullTransferCplt();
void RxHalfTransferCplt();

#ifdef __cplusplus
extern "C" {
#endif
void Error_Handler(uint8_t error_no);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
