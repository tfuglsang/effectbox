#include "main.h"
#include "wm8731.h"

void InitCodec(void)
{
  // CODEC MASTER
  SendCodecCmd(WM8731_REG_RESET, 0x00);
  SendCodecCmd(0x00, 0x17); // l in mute = 0
  SendCodecCmd(0x01, 0x17); // r in mute = 0
  SendCodecCmd(0x04, 0x12); // dac select = 1, mute mic = 1
  SendCodecCmd(0x05, 0x00); // dac mute = 0,  adc hp filter enable
  SendCodecCmd(0x06, 0x02); // microphone powerdown = 1
  SendCodecCmd(0x07, 0x42); // master mode, 16 bit, i2s format
  //SendCodecCmd(0x07, 0x4E); // master mode, 32 bit, i2s format
  SendCodecCmd(0x09, 0x01); // active control = 1

  /*
    // DAC -> headphone
    SendCodecCmd(WM8731_REG_RESET, 0x00);
    SendCodecCmd(0x04, 0x12);
    SendCodecCmd(0x05, 0x00);
    SendCodecCmd(0x06, 0x07);
    SendCodecCmd(0x07, 0x4E); // master mode, 16 bit, i2s format
    SendCodecCmd(0x09, 0x09);
  */
  /*
    // Passthrough: line_in -> hp out
    SendCodecCmd(WM8731_REG_RESET, 0x00);
    SendCodecCmd(0x04, 0x0A); // l in mute = 0
    SendCodecCmd(0x06, 0x0E); // r in mute = 0
    SendCodecCmd(0x09, 0x01); // active control = 1
  */

  /*
    //  line_in -> ADC
    SendCodecCmd(WM8731_REG_RESET, 0x00);
    SendCodecCmd(0x00, 0x17);
    SendCodecCmd(0x01, 0x17);
    SendCodecCmd(0x04, 0x02);
    SendCodecCmd(0x05, 0x09);
    SendCodecCmd(0x07, 0x4E); // master mode, 16 bit, i2s format
    SendCodecCmd(0x06, 0x0A);
    SendCodecCmd(0x09, 0x01);
  */
}

void InitUart(void)
{
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  UartHandle.Instance        = USART6;
  UartHandle.Init.BaudRate   = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
  {
    Error_Handler(HAL_ERROR_UART_INIT);
  }
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    Error_Handler(HAL_ERROR_UART_INIT);
  }
}

void InitRotaryEncoder(void)
{
  timer_1.Instance = TIM1;
  timer_1.Init.Prescaler = 0;
  timer_1.Init.CounterMode = TIM_COUNTERMODE_UP;
  timer_1.Init.Period = 200;
  timer_1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  //timer.Init.RepetitionCounter = 0;
  RotEncoder.EncoderMode = TIM_ENCODERMODE_TI12;
  RotEncoder.IC1Polarity = TIM_INPUTCHANNELPOLARITY_RISING; // TIM_ICPOLARITY_RISING
  RotEncoder.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  RotEncoder.IC1Prescaler = TIM_ICPSC_DIV4; // TIM_ICPSC_DIV1
  RotEncoder.IC1Filter = 0x0F; // 0

  RotEncoder.IC2Polarity = TIM_INPUTCHANNELPOLARITY_FALLING; // TIM_ICPOLARITY_RISING
  RotEncoder.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  RotEncoder.IC2Prescaler = TIM_ICPSC_DIV4; // TIM_ICPSC_DIV1
  RotEncoder.IC2Filter = 0x0F; // 0

  if (HAL_TIM_Encoder_Init(&timer_1, &RotEncoder) != HAL_OK)
  {
    Error_Handler(HAL_ERROR_TIMER_INIT);
  }

  if(HAL_TIM_Encoder_Start_IT(&timer_1,TIM_CHANNEL_1)!=HAL_OK){
    Error_Handler(HAL_ERROR_TIMER_INIT);
 }
}

void InitTim3(void)
{
  __TIM3_CLK_ENABLE();
  timer_3.Instance = TIM3;
  timer_3.Init.Prescaler = 40000;
  timer_3.Init.CounterMode = TIM_COUNTERMODE_UP;
  timer_3.Init.Period = 500;
  timer_3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  timer_3.Init.RepetitionCounter = 0;
  if (HAL_TIM_Base_Init(&timer_3) != HAL_OK)
  {
    Error_Handler(HAL_ERROR_ENCODER_INIT);
  }
  if(HAL_TIM_Base_Start_IT(&timer_3)!=HAL_OK)
  {
    Error_Handler(HAL_ERROR_ENCODER_INIT);
  }

  HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void InitI2S(void)
{
    I2sHandle.Instance = SPI1;
    I2sHandle.Init.Mode = I2S_MODE_SLAVE_FULLDUPLEX;
    I2sHandle.Init.Standard = I2S_STANDARD_PHILIPS;
    I2sHandle.Init.DataFormat = I2S_DATAFORMAT_16B;
    I2sHandle.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
    I2sHandle.Init.AudioFreq = I2S_AUDIOFREQ_48K;
    I2sHandle.Init.CPOL = I2S_CPOL_LOW;
    I2sHandle.Init.FirstBit = I2S_FIRSTBIT_MSB;
    I2sHandle.Init.WSInversion = I2S_WS_INVERSION_ENABLE;
    I2sHandle.Init.Data24BitAlignment = I2S_DATA_24BIT_ALIGNMENT_RIGHT;
    I2sHandle.Init.MasterKeepIOState = I2S_MASTER_KEEP_IO_STATE_DISABLE;

    __HAL_DMA_DISABLE(&DMA_I2s_rx_Handle);
    HAL_Delay(1);
    __HAL_DMA_DISABLE(&DMA_I2s_tx_Handle);

    __HAL_DMA_ENABLE(&DMA_I2s_rx_Handle);
    HAL_Delay(1);
    __HAL_DMA_ENABLE(&DMA_I2s_tx_Handle);

    __HAL_DMA_RESET_HANDLE_STATE(&DMA_I2s_tx_Handle);
    HAL_Delay(1);

    __HAL_I2S_DISABLE(&I2sHandle);
    HAL_Delay(1);
    __HAL_I2S_ENABLE(&I2sHandle);
    __HAL_I2S_RESET_HANDLE_STATE(&I2sHandle);

    RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST; //reset SPI1
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; //reset SPI1

    if (HAL_I2S_DeInit(&I2sHandle) != HAL_OK)
    {
      Error_Handler(HAL_ERROR_I2S_INIT);
    }
    if (HAL_I2S_Init(&I2sHandle) != HAL_OK)
    {
      Error_Handler(HAL_ERROR_I2S_INIT);
    }
}

void InitI2C(void)
{
  /*##-1- Configure the I2C peripheral ######################################*/
  I2cHandle.Instance             = I2C2;
  I2cHandle.Init.Timing          = I2C_TIMING;
  I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0xFF;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

  if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(HAL_ERROR_I2C_INIT);
  }

  /* Enable the Analog I2C Filter */
  HAL_I2CEx_ConfigAnalogFilter(&I2cHandle,I2C_ANALOGFILTER_ENABLE);
}

void InitDMA(void)
{
  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
}

void InitGPIO(void)
{
  // Enable GPIO PC3 to reset display on boot
 __GPIOC_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
  GPIO_InitTypeDef   GPIO_InitStructure;
  GPIO_InitStructure.Pin = GPIO_PIN_3;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

  HAL_Delay(500);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void MPU_Conf()
{
	  MPU_Region_InitTypeDef MPU_InitStruct;

	  HAL_MPU_Disable();
	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;

	  MPU_InitStruct.BaseAddress = 0x30000000;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_4KB;

	  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;

//	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
//	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
//	  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
//	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;

	  MPU_InitStruct.Number = MPU_REGION_NUMBER0;

	  MPU_InitStruct.SubRegionDisable = 0x00;

	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow
  *            System Clock source            = PLL (HSE BYPASS)
  *            SYSCLK(Hz)                     = 400000200 (CPU Clock)
  *            HCLK(Hz)                       = 200000000 (AXI and AHBs Clock)
  *                  = 2
  *            D1 APB3 Prescaler              = 2 (APB3 Clock  100MHz)
  *            D2 APB1 Prescaler              = 2 (APB1 Clock  100MHz)
  *            D2 APB2 Prescaler              = 2 (APB2 Clock  100MHz)
  *            D3 APB4 Prescaler              = 2 (APB4 Clock  100MHz)
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 4
  *            PLL_N                          = 400
  *            PLL_P                          = 2
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  HAL_StatusTypeDef ret = HAL_OK;

  /*!< Supply configuration update enable */
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    Error_Handler(HAL_ERROR_SYSCLOCK_INIT);
  }

/* Select PLL as system clock source and configure  bus clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | \
                                 RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  if(ret != HAL_OK)
  {
    Error_Handler(HAL_ERROR_SYSCLOCK_INIT);
  }
}
