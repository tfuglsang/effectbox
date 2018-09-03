

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_led.h"
#include "ezdsp5535_sar.h"

extern Int16 oled_test( );

int  TestFail    = (int)-1;   

Uint8  sw1State  = 0;       // SW1 state
Uint8  sw2State  = 0;       // SW2 state

void StopTest()
{
    //SW_BREAKPOINT;
    return;
}

/*
 *
 *  main( )
 *
 */
void main( void )
{
    /* Initialize BSL */
    EZDSP5535_init( );

    /* Display test ID */
    printf( "\nTesting OLED...\n");

    /* Initialize LEDs */
        EZDSP5535_LED_init( );
        EZDSP5535_LED_toggle( 1 );  // Toggle DS3 (RED LED)
        EZDSP5535_LED_toggle( 2 );  // Toggle DS4 (YELLOW LED)

    /* Call test function */
    TestFail = oled_test( );

    while(1)
    {
        if(EZDSP5535_SAR_getKey( ) == SW1) // Is SW1 pressed?
        {
            if(sw1State)              // Was previous state not pressed?
            {
                EZDSP5535_LED_toggle( 0 );  // Toggle DS2 (GREEN LED)
                sw1State = 0;     // Set state to 0 to allow only single press
            }
        }
        else                      // SW1 not pressed
            sw1State = 1;         // Set state to 1 to allow timer change

        /* Check SW2 */
        if(EZDSP5535_SAR_getKey( ) == SW2) // Is SW2 pressed?
        {
            if(sw2State)          // Was previous state not pressed?
            {
                EZDSP5535_LED_toggle( 3 );  // Toggle DS5 (BLUE LED)
                sw2State = 0;     // Set state to 0 to allow only single press
            }
        }
        else                      // SW2 not pressed
            sw2State = 1;         // Set state to 1 to allow tone change

            if((EZDSP5535_SAR_getKey( ) == SW12))   // If SW1 and SW2 pressed
            {
                EZDSP5535_LED_toggle( 1 );  // Toggle DS3 (RED LED)
                EZDSP5535_LED_toggle( 2 );  // Toggle DS4 (YELLOW LED)
                break;
            }
    }



    /* Check for test fail */
    if ( TestFail != 0 )
    {
        /* Print error message */
        printf( "     FAIL... error code %d... quitting\n", TestFail );
    }
    else
    {
        /* Print pass message */
        printf( "    PASS\n" );
        printf( "\n***ALL Tests Passed***\n" );
    }
    
    EZDSP5535_LED_toggle( 1 );  // Toggle DS3 (RED LED)
    EZDSP5535_LED_toggle( 2 );  // Toggle DS4 (YELLOW LED)
    EZDSP5535_LED_toggle( 1 );  // Toggle DS3 (RED LED)
    EZDSP5535_LED_toggle( 2 );  // Toggle DS4 (YELLOW LED)
    EZDSP5535_LED_toggle( 1 );  // Toggle DS3 (RED LED)
    EZDSP5535_LED_toggle( 2 );  // Toggle DS4 (YELLOW LED)
    StopTest();
}

