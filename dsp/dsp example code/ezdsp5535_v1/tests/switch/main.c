#include "stdio.h"
#include "ezdsp5535.h"

extern Int16 switch_test( );

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

    /* Display test ID */
    printf( "\nTesting Switches...\n");

    /* Call test function */
    TestFail = switch_test( );

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
