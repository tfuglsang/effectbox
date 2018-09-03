#include "stdio.h"
#include "ezdsp5535.h"

extern Int16 aic3204_test( );

int  TestFail    = (int)-1;   

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
    printf( "\n656\n");


    /* Display test ID */
    printf( "\nTesting AIC3204...\n");

    /* Call test function */
    TestFail = aic3204_test( );

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
    
    StopTest();
}

