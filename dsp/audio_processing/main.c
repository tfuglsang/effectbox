#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_led.h"
#include "ezdsp5535_lcd.h"
#include "ezdsp5535_sar.h"
#include "csl_pll.h"

void systemInit(void);

#define SYS_ICR        *(volatile ioport Uint16*)(0x0001)


void main( void )
{
    /* Initialize board */
    systemInit();
    EZDSP5535_init( );
    EZDSP5535_LED_init( );
    EZDSP5535_SAR_init();

    /* Codec Loopback */
    oled_test(2);
    audio_processing();

}

void systemInit(void)
{
    Uint16 i;
    PLL_Obj pllObj;
    CSL_Status status;
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
    status = PLL_init(&pllObj, CSL_PLL_INST_0);
    hPll = (PLL_Handle)(&pllObj);
    PLL_reset(hPll);
    pConfigInfo = &pllCfg_v2_100MHz;

    status = PLL_config (hPll, pConfigInfo);
}
