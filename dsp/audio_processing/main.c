#include "csl_spi.h"
#include "csl_general.h"
#include <stdio.h>
#include "csl_sysctrl.h"
#include "csl_pll.h"
#include "ezdsp5535_sar.h"
#include "ezdsp5535_led.h"

#define CSL_SPI_BUF_LEN         (64)
#define SPI_CLK_DIV             (100) // = 1Mhz    // 120 = 833khz.  Clock must run at 100MHz.
#define SPI_FRAME_LENGTH        (1)

#define SYS_ICR        *(volatile ioport Uint16*)(0x0001)

// Local variables
Uint16 spiWriteBuff[CSL_SPI_BUF_LEN];
Uint16 spiReadBuff[CSL_SPI_BUF_LEN];

// Local function prototypes
CSL_SpiHandle spi_init();
void spi_read(CSL_SpiHandle handleid);
void spi_write(CSL_SpiHandle handle);
void systemInit(void);


void main(void)
{
    /* Initialize board */
     systemInit();
     EZDSP5535_init( );
     EZDSP5535_LED_init( );
     EZDSP5535_SAR_init();

     CSL_SpiHandle spi_handle;
     spi_handle = spi_init();

     printf("CSL SPI Internal Loopback Test\n\n");
     while(EZDSP5535_SAR_getKey() != SW1);
     while(1)
     {

         //audio_processing();


        printf("Writing to SPI\n\n");
        spi_write(spi_handle);
        //spi_read(spi_handle);
        printf("Please press SW2\n\n");
        while(EZDSP5535_SAR_getKey() != SW2);
    }
}

CSL_SpiHandle spi_init(void)
{
    CSL_SpiHandle   hSpi;
    SPI_Config      hwConfig;
    Int16           result;

    result = SPI_init();

    if(CSL_SOK != result)
    {
        printf ("SPI Instance Initialize failed\n");
        return;
    }
    else
    {
        printf ("SPI Instance Initialize successfully\n");
    }

    result = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);

    if (CSL_SOK != result)
    {
        printf("SYS_setEBSR failed\n");
        return;
    }

    hSpi = SPI_open(SPI_CS_NUM_0, SPI_POLLING_MODE);

    if(NULL == hSpi)
    {
        printf ("SPI Instance Opened failed\n");
        return;
    }
    else
    {
        printf ("SPI Instance Opened successfully\n");
    }

    /** Set the hardware configuration                          */
    hwConfig.spiClkDiv  = SPI_CLK_DIV;
    hwConfig.wLen       = SPI_WORD_LENGTH_8;
    hwConfig.frLen      = SPI_FRAME_LENGTH;
    hwConfig.wcEnable   = SPI_WORD_IRQ_DISABLE;
    hwConfig.fcEnable   = SPI_FRAME_IRQ_DISABLE;
    hwConfig.csNum      = SPI_CS_NUM_0;
    hwConfig.dataDelay  = SPI_DATA_DLY_0;
    hwConfig.csPol      = SPI_CSP_ACTIVE_LOW;
    hwConfig.clkPol     = SPI_CLKP_LOW_AT_IDLE;
    hwConfig.clkPh      = SPI_CLK_PH_FALL_EDGE;

    result = SPI_config(hSpi, &hwConfig);

    if(CSL_SOK != result)
    {
        printf ("SPI Instance Config failed\n");
        return;
    }
    else
    {
        printf ("SPI Instance Configured successfully\n");
    }

    /*Enable the Internal Loopback mode*/
    #if (defined(CHIP_C5505_C5515) || defined(CHIP_C5504_C5514) || defined(CHIP_C5535) || defined(CHIP_C5545))
    //  CSL_FINST(CSL_SPI_REGS->SPIDCR2,SPI_SPIDCR2_LPBK,ENABLE);
    #endif

    return hSpi;
}

void spi_write(CSL_SpiHandle hSpi)
{
    Int16 result;
    Int16 looper;

    for(looper = 0; looper < 64; )
    {
        spiWriteBuff[looper] = 0;
        spiWriteBuff[(looper + 1)] = 0;
        spiReadBuff[looper] = 0;
        spiReadBuff[(looper + 1)] = 0;
        looper += 2;
    }
    for(looper = 0; looper < 64; )
    {
        spiWriteBuff[looper] = 0x0011;
        spiWriteBuff[(looper + 1)] = 0x00AB;
        spiReadBuff[looper] = 0x0000;
        spiReadBuff[(looper + 1)] = 0x00CD;
        looper += 2;
    }

    /* Write the Data to the SPI*/
    result = SPI_dataTransaction(hSpi ,spiWriteBuff, CSL_SPI_BUF_LEN, SPI_WRITE);
    if(CSL_SOK != result)
    {
        printf ("SPI Write failed\n");
        return;
    }
    else
    {
        printf ("SPI Instance Write successfully\n");
    }

}

void spi_read(CSL_SpiHandle hSpi)
{
  Int16 result;
  /* Read the Data to the SPI*/
  result = SPI_dataTransaction(hSpi ,spiReadBuff, CSL_SPI_BUF_LEN, SPI_READ);
  if(CSL_SOK != result)
  {
      printf ("SPI Instance Read failed\n");
      return;
  }
  else
  {
      printf ("SPI Instance Read successfully\n");
  }

  result = SPI_close(hSpi);

  if(CSL_SOK != result)
  {
      printf ("SPI Instance Close failed\n");
      return;
  }
  else
  {
      printf ("SPI Instance Close successfully\n");
  }
}

void systemInit(void)
{
    Uint16 i;
    PLL_Obj pllObj;
    //CSL_Status status;
    PLL_Handle hPll;
    PLL_Config *pConfigInfo;
    PLL_Config pllCfg_v2_100MHz    = {0x8BE8, 0x8000, 0x0806, 0x0000};

    /* Config Idle control */
    SYS_ICR = 0xFF2E;
    asm(" IDLE");

    /* Reset peripherals */
    CSL_FINS(CSL_SYSCTRL_REGS->PSRCR, SYS_PSRCR_COUNT, 0x02);
    CSL_SYSCTRL_REGS->PRCR = 0xfb;

    /* Delay for devices to reset */
    for (i=0; i< 200; i++);

    /* Setup PLL */
     PLL_init(&pllObj, CSL_PLL_INST_0);
    hPll = (PLL_Handle)(&pllObj);
    PLL_reset(hPll);
    pConfigInfo = &pllCfg_v2_100MHz;

    PLL_config (hPll, pConfigInfo);
}
