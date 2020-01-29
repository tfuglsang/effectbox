/* I2C TIMING Register define when I2C clock source is APB1 (SYSCLK/4) */
/* I2C TIMING is calculated in case of the I2C Clock source is the APB1CLK = 100 MHz */
/* This example use TIMING to 0x00901954 to reach 400 kHz speed (Rise time = 100 ns, Fall time = 10 ns) */
#define I2C_TIMING      0x00901954

// Initialization functions
void InitRotaryEncoder(void);
void InitTim3(void);
void InitUart(void);
void InitGPIO(void);
void InitI2C(void);
void InitI2S(void);
void InitDMA(void);
void MPU_Conf(void);
void SystemClock_Config(void);
void CPU_CACHE_Enable(void);
