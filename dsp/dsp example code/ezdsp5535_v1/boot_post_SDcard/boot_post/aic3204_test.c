#define AIC3204_I2C_ADDR 0x18
#include "ezdsp5535.h"
#include "ezdsp5535_gpio.h"
#include "ezdsp5535_i2c.h"
#include "stdio.h"

extern Int16 aic3204_loop_linein( );

/*
 *
 *  AIC3204_rGet( regnum, *regval )
 *
 *      Return value of codec register regnum
 *
 */
Int16 AIC3204_rget(  Uint16 regnum, Uint16* regval )
{
    Int16  retcode = 0;
    Uint16 cmd[2];

    cmd[0] = regnum & 0x007F;       // 7-bit Device Register
    cmd[1] = 0;

    retcode |= EZDSP5535_I2C_write( AIC3204_I2C_ADDR, cmd, 1 );
    retcode |= EZDSP5535_I2C_read( AIC3204_I2C_ADDR, cmd, 1 );

    *regval = cmd[0];
    EZDSP5535_wait( 10 );
    return retcode;
}

/*
 *
 *  AIC3204_rSet( regnum, regval )
 *
 *      Set codec register regnum to value regval
 *
 */
Int16 AIC3204_rset( Uint16 regnum, Uint16 regval )
{
    Uint16 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Device Register
    cmd[1] = regval;                // 8-bit Register Data

    EZDSP5535_waitusec( 300 );

    return EZDSP5535_I2C_write( AIC3204_I2C_ADDR, cmd, 2 );
}

/*
 * 
 *  aic3204_test( )
 *
 *      Test different configurations of the AIC3204
 */
Int16 aic3204_test( )
{
    /* Initialize I2C */
    EZDSP5535_I2C_init( );
    
    /* Codec tests */
      printf( " -> 1 KHz Tone on Headphone.\n" );
      if ( aic3204_tone_headphone( ) )           // Output test
          return 1;

      
    EZDSP5535_wait( 100 );  // Wait    
    printf( "<-> Audio Loopback from Stereo IN --> to HP OUT\n" );
    if ( aic3204_loop_linein( ) )              // Loop test
        return 3;
        
    return 0;
}
