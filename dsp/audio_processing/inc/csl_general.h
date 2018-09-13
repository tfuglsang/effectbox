
#ifndef _CSL_GENERAL_H_
#define _CSL_GENERAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 ******************************************************
 * CAUTION: DEFINE EITHER THE MACROS IN PART1 OR PART2.
 * DO NOT DEFINE MACROS IN BOTH PARTS.
 ******************************************************
 */

/** ***************************************************************************
 * --------------------------------------------------
 * PART1: CHIP VERSION MACRO DEFINITION FOR PG2.1 CSL
 * --------------------------------------------------
 *
 * Below macros are used to enable the source code specific to chip version
 * TMS320C5517.
 *
 * 'CHIP_C5517' indicates TMS320C5517 DSP.
 *
 * Defining the macro below will enable the code for the DSP TMS320C5517.
 */

/* TMS320C5517 */
//#define CHIP_C5517


/******************************* END OF PART1 *******************************/


/** ***************************************************************************
 * --------------------------------------------------
 * PART2: CHIP VERSION MACRO DEFINITION FOR PG2.0 CSL
 * --------------------------------------------------
 *
 * Below macros are used to enable the source code specific to chip versions
 * TMS320C5505, TMS320C5515, TMS320C5504, and TMS320C5514.
 * Design revision(DesignRev) of the DIE ID regsiter(0x1C43 & 0x1C44) will have
 * the value '5' for this chip set.
 *
 * 'CHIP_C5505_C5515' indicates TMS320C5505 and TMS320C5515.
 * 'CHIP_C5504_C5514' indicates TMS320C5504 and TMS320C5514.
 *
 * DSPs TMS320C5505 and TMS320C5515 are similar but certain LDOs not bonded out
 * for TMS320C5505 DSP.
 * DSPs TMS320C5504 and TMS320C5514 are similar but certain LDOs not bonded out
 * for TMS320C5504 DSP.
 *
 * DSPs TMS320C55x5 and TMS320C55x4 are having the same peripherals but
 * they differ in the internal memory available. 'x' stands for 0 or 1.
 *
 * Defining any of the below macros will enable the code for all the DSPs
 * TMS320C5504, TMS320C5505, TMS320C5514 and TMS320C5515.
 * Current CSL software does not have the code that is specific to TMS320C5504
 * and TMS320C5514 DSPs.
 */

#ifndef CHIP_C5517

/* TMS320C5505 and TMS320C5515 */
//#define CHIP_C5505_C5515

/** TMS320C5504 and TMS320C5514 */
//#define CHIP_C5504_C5514

#if ((!defined(CHIP_C5505_C5515))&&(!defined(CHIP_C5504_C5514)))

/* TMS320C5535 or TMS320C5545 */
#define CHIP_C5535

#if (!defined(CHIP_C5535))
#define CHIP_C5545
#endif
#endif

#endif

/******************************* END OF PART2 *******************************/


/** ***************************************************************************
 * -----------------------------------------------------------
 * PART3: EVM VERSION MACRO DEFINITION FOR PG2.0 and PG2.1 CSL
 * -----------------------------------------------------------
 *
 * Below macros are used to enable the source code specific to EVM versions
 */

#if (defined(CHIP_C5517))
/** Macro to define platform as C5517 */
//#define C5517_EVM

#else // (!defined(CHIP_C5517))
#if (defined(CHIP_C5505_C5515)||defined(CHIP_C5504_C5514))
/** Macro to define platform as C5515 */
//#define C5515_EVM

#if (!(defined(C5515_EVM)))
/** Macro to define platform as C5515 eZdsp */
//#define C5515_EZDSP

#endif // !(defined(C5515_EVM))
#else // (!(defined(CHIP_C5517)||defined(CHIP_C5505_C5515)||(defined(CHIP_C5504_C5514))

#if (defined(CHIP_C5535))
/** Macro to define platform as C5535 eZdsp */
#define C5535_EZDSP
#endif

#if (!defined(C5535_EZDSP))
/** Macro to define platform as C5545 BoosterPack */
#define C5545_BSTPCK
#endif // !(defined(C5535_EZDSP))
#endif // ((defined(CHIP_C5505_C5515))||(defined(CHIP_C5504_C5514)))

#endif // (defined(CHIP_C5517))
/******************************* END OF PART3 *******************************/

#ifdef __cplusplus
}
#endif

#endif    // _CSL_GENERAL_H_

