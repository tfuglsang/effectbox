#include "main.h"

/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  __HAL_RCC_USART6_CLK_ENABLE();

  __HAL_RCC_GPIOG_CLK_ENABLE();
  /**USART6 GPIO Configuration
  PG9     ------> USART6_RX
  PG14     ------> USART6_TX
  */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART6;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*##-3- Configure the NVIC for UART ########################################*/
  /* NVIC for USART */
  HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USARTx_IRQn);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    __HAL_RCC_USART6_CLK_DISABLE();
  
    /**USART6 GPIO Configuration    
    PG9     ------> USART6_RX
    PG14     ------> USART6_TX 
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_9|GPIO_PIN_14);
  
  /*##-3- Disable the NVIC for UART ##########################################*/
  HAL_NVIC_DisableIRQ(USARTx_IRQn);
}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_encoder)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim_encoder->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
  
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**TIM1 GPIO Configuration    
    PE9     ------> TIM1_CH1
    PE11     ------> TIM1_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }

}
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* htim_encoder)
{
  if(htim_encoder->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();
  
    /**TIM1 GPIO Configuration    
    PE9     ------> TIM1_CH1
    PE11     ------> TIM1_CH2 
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_9|GPIO_PIN_11);

  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }

}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  I2Cx_SCL_GPIO_CLK_ENABLE();
  I2Cx_SDA_GPIO_CLK_ENABLE();
  /* Enable I2Cx clock */
  I2Cx_CLK_ENABLE(); 

  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* I2C TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = I2Cx_SCL_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);
    
  /* I2C RX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = I2Cx_SDA_PIN;
  GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
    
  /*##-3- Configure the NVIC for I2C ########################################*/   
  /* NVIC for I2Cx */
  HAL_NVIC_SetPriority(I2Cx_ER_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(I2Cx_ER_IRQn);
  HAL_NVIC_SetPriority(I2Cx_EV_IRQn, 0, 2);
  HAL_NVIC_EnableIRQ(I2Cx_EV_IRQn);
}

/**
  * @brief I2C MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO, DMA and NVIC configuration to their default state
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
  
  /*##-1- Reset peripherals ##################################################*/
  I2Cx_FORCE_RESET();
  I2Cx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure I2C Tx as alternate function  */
  HAL_GPIO_DeInit(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN);
  /* Configure I2C Rx as alternate function  */
  HAL_GPIO_DeInit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN);
  
  /*##-3- Disable the NVIC for I2C ##########################################*/
  HAL_NVIC_DisableIRQ(I2Cx_ER_IRQn);
  HAL_NVIC_DisableIRQ(I2Cx_EV_IRQn);
}

void HAL_I2S_MspInit(I2S_HandleTypeDef* hi2s)
{
  if(hi2s->Instance==SPI2)
  {
	  GPIO_InitTypeDef  GPIO_InitStruct;

	__HAL_RCC_SPI2_CLK_ENABLE();

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();


	/**I2S2 GPIO Configuration
	PC2_C     ------> I2S2_SDI
	PC3_C     ------> I2S2_SDO
	PB10     ------> I2S2_CK
	PB12     ------> I2S2_WS
	PC6     ------> I2S2_MCK
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  // I2S1 GPIO Configuration
  PA4     ------> I2S1_WS
  PA5     ------> I2S1_CK
  PA6     ------> I2S1_SDI
  PD7     ------> I2S1_SDO


  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  */

    DMA_I2s_tx_Handle.Instance = DMA1_Stream0;
    DMA_I2s_tx_Handle.Init.Request = DMA_REQUEST_SPI2_TX;
    DMA_I2s_rx_Handle.Instance = DMA1_Stream1;
    DMA_I2s_rx_Handle.Init.Request = DMA_REQUEST_SPI2_RX;
    //__HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

    DMA_I2s_tx_Handle.Init.Direction = DMA_MEMORY_TO_PERIPH;
    DMA_I2s_tx_Handle.Init.MemInc = DMA_MINC_ENABLE;
    DMA_I2s_tx_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
    DMA_I2s_tx_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    DMA_I2s_tx_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    DMA_I2s_tx_Handle.Init.Mode = DMA_CIRCULAR;
    DMA_I2s_tx_Handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    DMA_I2s_tx_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    DMA_I2s_tx_Handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    DMA_I2s_tx_Handle.Init.MemBurst = DMA_MBURST_SINGLE;
    DMA_I2s_tx_Handle.Init.PeriphBurst = DMA_PBURST_SINGLE;

    HAL_DMA_Init(&DMA_I2s_tx_Handle);
    __HAL_LINKDMA(hi2s,hdmatx,DMA_I2s_tx_Handle);

    DMA_I2s_rx_Handle.Init.Direction = DMA_MEMORY_TO_PERIPH;
    DMA_I2s_rx_Handle.Init.MemInc = DMA_MINC_ENABLE;
    DMA_I2s_rx_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
    DMA_I2s_rx_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    DMA_I2s_rx_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    DMA_I2s_rx_Handle.Init.Mode = DMA_CIRCULAR;
    DMA_I2s_rx_Handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    DMA_I2s_rx_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    DMA_I2s_rx_Handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    DMA_I2s_rx_Handle.Init.MemBurst = DMA_MBURST_SINGLE;
    DMA_I2s_rx_Handle.Init.PeriphBurst = DMA_PBURST_SINGLE;

    HAL_DMA_Init(&DMA_I2s_rx_Handle);
    __HAL_LINKDMA(hi2s,hdmatx,DMA_I2s_rx_Handle);


	HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

	HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

    //HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(SPI1_IRQn);

  }

}

/**
* @brief I2S MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2s: I2S handle pointer
* @retval None
*/
void HAL_I2S_MspDeInit(I2S_HandleTypeDef* hi2s)
{
  if(hi2s->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();

    /**I2S2 GPIO Configuration
    PB12     ------> I2S2_WS
    PB13     ------> I2S2_CK
    PB15     ------> I2S2_SDO
    PC6     ------> I2S2_MCK
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6);

    /* I2S2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(SPI2_IRQn);
  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }

}

