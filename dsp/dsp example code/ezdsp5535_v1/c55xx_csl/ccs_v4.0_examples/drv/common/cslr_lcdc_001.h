#ifndef _CSLR_LCDC_1_H_
#define _CSLR_LCDC_1_H_
/*********************************************************************
 * Copyright (C) 2003-2004 Texas Instruments Incorporated. 
 * All Rights Reserved 
 *********************************************************************/
 /** \file cslr_lcdc_1.h
 * 
 * \brief This file contains the Register Desciptions for LCDC
 * 
 *********************************************************************/
#include <cslr.h>

/* Minimum unit = 2 bytes */

//#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint16 LCDRRL;
    volatile Uint16 LCDRRM;
    volatile Uint16 RSVD0[2];
    volatile Uint16 LCDCRL;
    volatile Uint16 LCDCRM;
    volatile Uint16 RSVD1[2];
    volatile Uint16 LCDSRL;
    volatile Uint16 LCDSRM;
    volatile Uint16 RSVD2[2];
    volatile Uint16 LCDLIDDCRL;
    volatile Uint16 LCDLIDDCRM;
    volatile Uint16 RSVD3[2];
    volatile Uint16 LCDLIDDCS0CONFIGL;
    volatile Uint16 LCDLIDDCS0CONFIGM;
    volatile Uint16 RSVD4[2];
    volatile Uint16 LCDLIDDCS0ADDRL;
    volatile Uint16 LCDLIDDCS0ADDRM;
    volatile Uint16 RSVD5[2];
    volatile Uint16 LCDLIDDCS0DATAL;
    volatile Uint16 LCDLIDDCS0DATAM;
    volatile Uint16 RSVD6[2];
    volatile Uint16 LCDLIDDCS1CONFIGL;
    volatile Uint16 LCDLIDDCS1CONFIGM;
    volatile Uint16 RSVD7[2];
    volatile Uint16 LCDLIDDCS1ADDRL;
    volatile Uint16 LCDLIDDCS1ADDRM;
    volatile Uint16 RSVD8[2];
    volatile Uint16 LCDLIDDCS1DATAL;
    volatile Uint16 LCDLIDDCS1DATAM;
    volatile Uint16 RSVD9[2];
    volatile Uint16 LCDRASTCRL;
    volatile Uint16 LCDRASTCRM;
    volatile Uint16 RSVD10[2];
    volatile Uint16 LCDRASTT0RL;
    volatile Uint16 LCDRASTT0RM;
    volatile Uint16 RSVD11[2];
    volatile Uint16 LCDRASTT1RL;
    volatile Uint16 LCDRASTT1RM;
    volatile Uint16 RSVD12[2];
    volatile Uint16 LCDRASTT2RL;
    volatile Uint16 LCDRASTT2RM;
    volatile Uint16 RSVD13[2];
    volatile Uint16 LCDRASTSUBPANDISPL;
    volatile Uint16 LCDRASTSUBPANDISPM;
    volatile Uint16 RSVD14[6];
    volatile Uint16 LCDDMACRL;
    volatile Uint16 LCDDMACRM;
    volatile Uint16 RSVD15[2];
    volatile Uint16 LCDDMAFB0BARL;
    volatile Uint16 LCDDMAFB0BARM;
    volatile Uint16 RSVD16[2];
    volatile Uint16 LCDDMAFB0CARL;
    volatile Uint16 LCDDMAFB0CARM;
    volatile Uint16 RSVD17[2];
    volatile Uint16 LCDDMAFB1BARL;
    volatile Uint16 LCDDMAFB1BARM;
    volatile Uint16 RSVD18[2];
    volatile Uint16 LCDDMAFB1CARL;
    volatile Uint16 LCDDMAFB1CARM;
} CSL_LcdcRegs;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* LCDRRL */

#define CSL_LCDC_LCDRRL_REVMIN_MASK (0xFFFFu)
#define CSL_LCDC_LCDRRL_REVMIN_SHIFT (0x0000u)
#define CSL_LCDC_LCDRRL_REVMIN_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRRL_RESETVAL (0x0000u)

/* LCDRRM */

#define CSL_LCDC_LCDRRM_REVMAJ_MASK (0xFFFFu)
#define CSL_LCDC_LCDRRM_REVMAJ_SHIFT (0x0000u)
#define CSL_LCDC_LCDRRM_REVMAJ_RESETVAL (0x0001u)

#define CSL_LCDC_LCDRRM_RESETVAL (0x0001u)

/* LCDCRL */

#define CSL_LCDC_LCDCRL_CLKDIV_MASK (0xFF00u)
#define CSL_LCDC_LCDCRL_CLKDIV_SHIFT (0x0008u)
#define CSL_LCDC_LCDCRL_CLKDIV_RESETVAL (0x0000u)


#define CSL_LCDC_LCDCRL_MODESEL_MASK (0x0001u)
#define CSL_LCDC_LCDCRL_MODESEL_SHIFT (0x0000u)
#define CSL_LCDC_LCDCRL_MODESEL_RESETVAL (0x0000u)
/*----MODESEL Tokens----*/
#define CSL_LCDC_LCDCRL_MODESEL_LIDD (0x0000u)

#define CSL_LCDC_LCDCRL_RESETVAL (0x0000u)

/* LCDCRM */


#define CSL_LCDC_LCDCRM_RESETVAL (0x0000u)

/* LCDSRL */


#define CSL_LCDC_LCDSRL_EOF1_MASK (0x0200u)
#define CSL_LCDC_LCDSRL_EOF1_SHIFT (0x0009u)
#define CSL_LCDC_LCDSRL_EOF1_RESETVAL (0x0000u)

#define CSL_LCDC_LCDSRL_EOF0_MASK (0x0100u)
#define CSL_LCDC_LCDSRL_EOF0_SHIFT (0x0008u)
#define CSL_LCDC_LCDSRL_EOF0_RESETVAL (0x0000u)


#define CSL_LCDC_LCDSRL_PL_MASK (0x0040u)
#define CSL_LCDC_LCDSRL_PL_SHIFT (0x0006u)
#define CSL_LCDC_LCDSRL_PL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDSRL_FUF_MASK (0x0020u)
#define CSL_LCDC_LCDSRL_FUF_SHIFT (0x0005u)
#define CSL_LCDC_LCDSRL_FUF_RESETVAL (0x0000u)


#define CSL_LCDC_LCDSRL_ABC_MASK (0x0008u)
#define CSL_LCDC_LCDSRL_ABC_SHIFT (0x0003u)
#define CSL_LCDC_LCDSRL_ABC_RESETVAL (0x0000u)

#define CSL_LCDC_LCDSRL_SYNC_MASK (0x0004u)
#define CSL_LCDC_LCDSRL_SYNC_SHIFT (0x0002u)
#define CSL_LCDC_LCDSRL_SYNC_RESETVAL (0x0000u)


#define CSL_LCDC_LCDSRL_DONE_MASK (0x0001u)
#define CSL_LCDC_LCDSRL_DONE_SHIFT (0x0000u)
#define CSL_LCDC_LCDSRL_DONE_RESETVAL (0x0000u)

#define CSL_LCDC_LCDSRL_RESETVAL (0x0000u)

/* LCDSRM */


#define CSL_LCDC_LCDSRM_RESETVAL (0x0000u)

/* LCDLIDDCRL */


#define CSL_LCDC_LCDLIDDCRL_DONE_INT_EN_MASK (0x0400u)
#define CSL_LCDC_LCDLIDDCRL_DONE_INT_EN_SHIFT (0x000Au)
#define CSL_LCDC_LCDLIDDCRL_DONE_INT_EN_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_DMA_CS0_CS1_MASK (0x0200u)
#define CSL_LCDC_LCDLIDDCRL_DMA_CS0_CS1_SHIFT (0x0009u)
#define CSL_LCDC_LCDLIDDCRL_DMA_CS0_CS1_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_LIDD_DMA_EN_MASK (0x0100u)
#define CSL_LCDC_LCDLIDDCRL_LIDD_DMA_EN_SHIFT (0x0008u)
#define CSL_LCDC_LCDLIDDCRL_LIDD_DMA_EN_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_CS1_E1_POL_MASK (0x0080u)
#define CSL_LCDC_LCDLIDDCRL_CS1_E1_POL_SHIFT (0x0007u)
#define CSL_LCDC_LCDLIDDCRL_CS1_E1_POL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_CS0_E0_POL_MASK (0x0040u)
#define CSL_LCDC_LCDLIDDCRL_CS0_E0_POL_SHIFT (0x0006u)
#define CSL_LCDC_LCDLIDDCRL_CS0_E0_POL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_WS_DIR_POL_MASK (0x0020u)
#define CSL_LCDC_LCDLIDDCRL_WS_DIR_POL_SHIFT (0x0005u)
#define CSL_LCDC_LCDLIDDCRL_WS_DIR_POL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_RS_EN_POL_MASK (0x0010u)
#define CSL_LCDC_LCDLIDDCRL_RS_EN_POL_SHIFT (0x0004u)
#define CSL_LCDC_LCDLIDDCRL_RS_EN_POL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_ALEPOL_MASK (0x0008u)
#define CSL_LCDC_LCDLIDDCRL_ALEPOL_SHIFT (0x0003u)
#define CSL_LCDC_LCDLIDDCRL_ALEPOL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCRL_LIDD_MODE_SEL_MASK (0x0007u)
#define CSL_LCDC_LCDLIDDCRL_LIDD_MODE_SEL_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCRL_LIDD_MODE_SEL_RESETVAL (0x0000u)
/*----LIDD_MODE_SEL Tokens----*/
#define CSL_LCDC_LCDLIDDCRL_LIDD_MODE_SEL_SYNC_MPU68 (0x0000u)
#define CSL_LCDC_LCDLIDDCRL_LIDD_MODE_SEL_HITACHI (0x0004u)

#define CSL_LCDC_LCDLIDDCRL_RESETVAL (0x0000u)

/* LCDLIDDCRM */


#define CSL_LCDC_LCDLIDDCRM_RESETVAL (0x0000u)

/* LCDLIDDCS0CONFIGL */

#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_SU_MASK (0xF000u)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_SU_SHIFT (0x000Cu)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_SU_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_STROBE_MASK (0x0FC0u)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_STROBE_SHIFT (0x0006u)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_STROBE_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_HOLD_MASK (0x003Cu)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_HOLD_SHIFT (0x0002u)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_R_HOLD_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS0CONFIGL_TA_MASK (0x0003u)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_TA_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS0CONFIGL_TA_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS0CONFIGL_RESETVAL (0x0044u)

/* LCDLIDDCS0CONFIGM */

#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_SU_MASK (0xF800u)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_SU_SHIFT (0x000Bu)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_SU_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_STROBE_MASK (0x07E0u)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_STROBE_SHIFT (0x0005u)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_STROBE_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_HOLD_MASK (0x001Eu)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_HOLD_SHIFT (0x0001u)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_W_HOLD_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS0CONFIGM_R_SU_MASK (0x0001u)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_R_SU_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS0CONFIGM_R_SU_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS0CONFIGM_RESETVAL (0x0022u)

/* LCDLIDDCS0ADDRL */

#define CSL_LCDC_LCDLIDDCS0ADDRL_ADR_INDX_MASK (0xFFFFu)
#define CSL_LCDC_LCDLIDDCS0ADDRL_ADR_INDX_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS0ADDRL_ADR_INDX_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS0ADDRL_RESETVAL (0x0000u)

/* LCDLIDDCS0ADDRM */


#define CSL_LCDC_LCDLIDDCS0ADDRM_RESETVAL (0x0000u)

/* LCDLIDDCS0DATAL */

#define CSL_LCDC_LCDLIDDCS0DATAL_DATA_MASK (0xFFFFu)
#define CSL_LCDC_LCDLIDDCS0DATAL_DATA_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS0DATAL_DATA_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS0DATAL_RESETVAL (0x0000u)

/* LCDLIDDCS0DATAM */


#define CSL_LCDC_LCDLIDDCS0DATAM_RESETVAL (0x0000u)

/* LCDLIDDCS1CONFIGL */

#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_SU_MASK (0xF000u)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_SU_SHIFT (0x000Cu)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_SU_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_STROBE_MASK (0x0FC0u)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_STROBE_SHIFT (0x0006u)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_STROBE_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_HOLD_MASK (0x003Cu)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_HOLD_SHIFT (0x0002u)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_R_HOLD_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS1CONFIGL_TA_MASK (0x0003u)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_TA_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS1CONFIGL_TA_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS1CONFIGL_RESETVAL (0x0044u)

/* LCDLIDDCS1CONFIGM */

#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_SU_MASK (0xF800u)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_SU_SHIFT (0x000Bu)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_SU_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_STROBE_MASK (0x07E0u)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_STROBE_SHIFT (0x0005u)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_STROBE_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_HOLD_MASK (0x001Eu)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_HOLD_SHIFT (0x0001u)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_W_HOLD_RESETVAL (0x0001u)

#define CSL_LCDC_LCDLIDDCS1CONFIGM_R_SU_MASK (0x0001u)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_R_SU_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS1CONFIGM_R_SU_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS1CONFIGM_RESETVAL (0x0022u)

/* LCDLIDDCS1ADDRL */

#define CSL_LCDC_LCDLIDDCS1ADDRL_ADR_INDX_MASK (0xFFFFu)
#define CSL_LCDC_LCDLIDDCS1ADDRL_ADR_INDX_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS1ADDRL_ADR_INDX_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS1ADDRL_RESETVAL (0x0000u)

/* LCDLIDDCS1ADDRM */


#define CSL_LCDC_LCDLIDDCS1ADDRM_RESETVAL (0x0000u)

/* LCDLIDDCS1DATAL */

#define CSL_LCDC_LCDLIDDCS1DATAL_DATA_MASK (0xFFFFu)
#define CSL_LCDC_LCDLIDDCS1DATAL_DATA_SHIFT (0x0000u)
#define CSL_LCDC_LCDLIDDCS1DATAL_DATA_RESETVAL (0x0000u)

#define CSL_LCDC_LCDLIDDCS1DATAL_RESETVAL (0x0000u)

/* LCDLIDDCS1DATAM */


#define CSL_LCDC_LCDLIDDCS1DATAM_RESETVAL (0x0000u)

/* LCDRASTCRL */

#define CSL_LCDC_LCDRASTCRL_REQDLY_MASK (0xF000u)
#define CSL_LCDC_LCDRASTCRL_REQDLY_SHIFT (0x000Cu)
#define CSL_LCDC_LCDRASTCRL_REQDLY_RESETVAL (0x0000u)


#define CSL_LCDC_LCDRASTCRL_MONO8B_MASK (0x0200u)
#define CSL_LCDC_LCDRASTCRL_MONO8B_SHIFT (0x0009u)
#define CSL_LCDC_LCDRASTCRL_MONO8B_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRL_RDORDER_MASK (0x0100u)
#define CSL_LCDC_LCDRASTCRL_RDORDER_SHIFT (0x0008u)
#define CSL_LCDC_LCDRASTCRL_RDORDER_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRL_LCDTFT_MASK (0x0080u)
#define CSL_LCDC_LCDRASTCRL_LCDTFT_SHIFT (0x0007u)
#define CSL_LCDC_LCDRASTCRL_LCDTFT_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRL_FUFEN_MASK (0x0040u)
#define CSL_LCDC_LCDRASTCRL_FUFEN_SHIFT (0x0006u)
#define CSL_LCDC_LCDRASTCRL_FUFEN_RESETVAL (0x0000u)
/*----FUFEN Tokens----*/
#define CSL_LCDC_LCDRASTCRL_FUFEN_DISABLE (0x0000u)
#define CSL_LCDC_LCDRASTCRL_FUFEN_ENABLE (0x0001u)

#define CSL_LCDC_LCDRASTCRL_SYNCEN_MASK (0x0020u)
#define CSL_LCDC_LCDRASTCRL_SYNCEN_SHIFT (0x0005u)
#define CSL_LCDC_LCDRASTCRL_SYNCEN_RESETVAL (0x0000u)
/*----SYNCEN Tokens----*/
#define CSL_LCDC_LCDRASTCRL_SYNCEN_DISABLE (0x0000u)
#define CSL_LCDC_LCDRASTCRL_SYNCEN_ENABLE (0x0001u)

#define CSL_LCDC_LCDRASTCRL_LOADEN_MASK (0x0010u)
#define CSL_LCDC_LCDRASTCRL_LOADEN_SHIFT (0x0004u)
#define CSL_LCDC_LCDRASTCRL_LOADEN_RESETVAL (0x0000u)
/*----LOADEN Tokens----*/
#define CSL_LCDC_LCDRASTCRL_LOADEN_DISABLE (0x0000u)
#define CSL_LCDC_LCDRASTCRL_LOADEN_ENABLE (0x0001u)

#define CSL_LCDC_LCDRASTCRL_DONEEN_MASK (0x0008u)
#define CSL_LCDC_LCDRASTCRL_DONEEN_SHIFT (0x0003u)
#define CSL_LCDC_LCDRASTCRL_DONEEN_RESETVAL (0x0000u)
/*----DONEEN Tokens----*/
#define CSL_LCDC_LCDRASTCRL_DONEEN_DISABLE (0x0000u)
#define CSL_LCDC_LCDRASTCRL_DONEEN_ENABLE (0x0001u)

#define CSL_LCDC_LCDRASTCRL_ABCEN_MASK (0x0004u)
#define CSL_LCDC_LCDRASTCRL_ABCEN_SHIFT (0x0002u)
#define CSL_LCDC_LCDRASTCRL_ABCEN_RESETVAL (0x0000u)
/*----ABCEN Tokens----*/
#define CSL_LCDC_LCDRASTCRL_ABCEN_DISABLE (0x0000u)
#define CSL_LCDC_LCDRASTCRL_ABCEN_ENABLE (0x0001u)

#define CSL_LCDC_LCDRASTCRL_LCDBW_MASK (0x0002u)
#define CSL_LCDC_LCDRASTCRL_LCDBW_SHIFT (0x0001u)
#define CSL_LCDC_LCDRASTCRL_LCDBW_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRL_LCDEN_MASK (0x0001u)
#define CSL_LCDC_LCDRASTCRL_LCDEN_SHIFT (0x0000u)
#define CSL_LCDC_LCDRASTCRL_LCDEN_RESETVAL (0x0000u)
/*----LCDEN Tokens----*/
#define CSL_LCDC_LCDRASTCRL_LCDEN_DISABLE (0x0000u)
#define CSL_LCDC_LCDRASTCRL_LCDEN_ENABLE (0x0001u)

#define CSL_LCDC_LCDRASTCRL_RESETVAL (0x0000u)

/* LCDRASTCRM */


#define CSL_LCDC_LCDRASTCRM_STN565_MASK (0x0100u)
#define CSL_LCDC_LCDRASTCRM_STN565_SHIFT (0x0008u)
#define CSL_LCDC_LCDRASTCRM_STN565_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRM_TFTMAP_MASK (0x0080u)
#define CSL_LCDC_LCDRASTCRM_TFTMAP_SHIFT (0x0007u)
#define CSL_LCDC_LCDRASTCRM_TFTMAP_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRM_NIBMODE_MASK (0x0040u)
#define CSL_LCDC_LCDRASTCRM_NIBMODE_SHIFT (0x0006u)
#define CSL_LCDC_LCDRASTCRM_NIBMODE_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRM_PALMODE_MASK (0x0030u)
#define CSL_LCDC_LCDRASTCRM_PALMODE_SHIFT (0x0004u)
#define CSL_LCDC_LCDRASTCRM_PALMODE_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRM_REQDLY_MASK (0x000Fu)
#define CSL_LCDC_LCDRASTCRM_REQDLY_SHIFT (0x0000u)
#define CSL_LCDC_LCDRASTCRM_REQDLY_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTCRM_RESETVAL (0x0000u)

/* LCDRASTT0RL */

#define CSL_LCDC_LCDRASTT0RL_HSW_MASK (0xFC00u)
#define CSL_LCDC_LCDRASTT0RL_HSW_SHIFT (0x000Au)
#define CSL_LCDC_LCDRASTT0RL_HSW_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT0RL_PPL_MASK (0x03F0u)
#define CSL_LCDC_LCDRASTT0RL_PPL_SHIFT (0x0004u)
#define CSL_LCDC_LCDRASTT0RL_PPL_RESETVAL (0x0000u)


#define CSL_LCDC_LCDRASTT0RL_RESETVAL (0x0000u)

/* LCDRASTT0RM */

#define CSL_LCDC_LCDRASTT0RM_HBP_MASK (0xFF00u)
#define CSL_LCDC_LCDRASTT0RM_HBP_SHIFT (0x0008u)
#define CSL_LCDC_LCDRASTT0RM_HBP_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT0RM_HFP_MASK (0x00FFu)
#define CSL_LCDC_LCDRASTT0RM_HFP_SHIFT (0x0000u)
#define CSL_LCDC_LCDRASTT0RM_HFP_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT0RM_RESETVAL (0x0000u)

/* LCDRASTT1RL */

#define CSL_LCDC_LCDRASTT1RL_VSW_MASK (0xFC00u)
#define CSL_LCDC_LCDRASTT1RL_VSW_SHIFT (0x000Au)
#define CSL_LCDC_LCDRASTT1RL_VSW_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT1RL_LPP_MASK (0x03FFu)
#define CSL_LCDC_LCDRASTT1RL_LPP_SHIFT (0x0000u)
#define CSL_LCDC_LCDRASTT1RL_LPP_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT1RL_RESETVAL (0x0000u)

/* LCDRASTT1RM */

#define CSL_LCDC_LCDRASTT1RM_VBP_MASK (0xFF00u)
#define CSL_LCDC_LCDRASTT1RM_VBP_SHIFT (0x0008u)
#define CSL_LCDC_LCDRASTT1RM_VBP_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT1RM_VFP_MASK (0x00FFu)
#define CSL_LCDC_LCDRASTT1RM_VFP_SHIFT (0x0000u)
#define CSL_LCDC_LCDRASTT1RM_VFP_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT1RM_RESETVAL (0x0000u)

/* LCDRASTT2RL */

#define CSL_LCDC_LCDRASTT2RL_ACB_MASK (0xFF00u)
#define CSL_LCDC_LCDRASTT2RL_ACB_SHIFT (0x0008u)
#define CSL_LCDC_LCDRASTT2RL_ACB_RESETVAL (0x0000u)


#define CSL_LCDC_LCDRASTT2RL_RESETVAL (0x0000u)

/* LCDRASTT2RM */


#define CSL_LCDC_LCDRASTT2RM_PHSVS_ON_OFF_MASK (0x0200u)
#define CSL_LCDC_LCDRASTT2RM_PHSVS_ON_OFF_SHIFT (0x0009u)
#define CSL_LCDC_LCDRASTT2RM_PHSVS_ON_OFF_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT2RM_PHSVS_RF_MASK (0x0100u)
#define CSL_LCDC_LCDRASTT2RM_PHSVS_RF_SHIFT (0x0008u)
#define CSL_LCDC_LCDRASTT2RM_PHSVS_RF_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT2RM_IEO_MASK (0x0080u)
#define CSL_LCDC_LCDRASTT2RM_IEO_SHIFT (0x0007u)
#define CSL_LCDC_LCDRASTT2RM_IEO_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT2RM_IPC_MASK (0x0040u)
#define CSL_LCDC_LCDRASTT2RM_IPC_SHIFT (0x0006u)
#define CSL_LCDC_LCDRASTT2RM_IPC_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT2RM_IHS_MASK (0x0020u)
#define CSL_LCDC_LCDRASTT2RM_IHS_SHIFT (0x0005u)
#define CSL_LCDC_LCDRASTT2RM_IHS_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT2RM_IVS_MASK (0x0010u)
#define CSL_LCDC_LCDRASTT2RM_IVS_SHIFT (0x0004u)
#define CSL_LCDC_LCDRASTT2RM_IVS_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT2RM_ACBI_MASK (0x000Fu)
#define CSL_LCDC_LCDRASTT2RM_ACBI_SHIFT (0x0000u)
#define CSL_LCDC_LCDRASTT2RM_ACBI_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTT2RM_RESETVAL (0x0000u)

/* LCDRASTSUBPANDISPL */

#define CSL_LCDC_LCDRASTSUBPANDISPL_DPD_MASK (0xFFF0u)
#define CSL_LCDC_LCDRASTSUBPANDISPL_DPD_SHIFT (0x0004u)
#define CSL_LCDC_LCDRASTSUBPANDISPL_DPD_RESETVAL (0x0000u)


#define CSL_LCDC_LCDRASTSUBPANDISPL_RESETVAL (0x0000u)

/* LCDRASTSUBPANDISPM */

#define CSL_LCDC_LCDRASTSUBPANDISPM_SPEN_MASK (0x8000u)
#define CSL_LCDC_LCDRASTSUBPANDISPM_SPEN_SHIFT (0x000Fu)
#define CSL_LCDC_LCDRASTSUBPANDISPM_SPEN_RESETVAL (0x0000u)


#define CSL_LCDC_LCDRASTSUBPANDISPM_HOLS_MASK (0x2000u)
#define CSL_LCDC_LCDRASTSUBPANDISPM_HOLS_SHIFT (0x000Du)
#define CSL_LCDC_LCDRASTSUBPANDISPM_HOLS_RESETVAL (0x0000u)


#define CSL_LCDC_LCDRASTSUBPANDISPM_LPPT_MASK (0x03FFu)
#define CSL_LCDC_LCDRASTSUBPANDISPM_LPPT_SHIFT (0x0000u)
#define CSL_LCDC_LCDRASTSUBPANDISPM_LPPT_RESETVAL (0x0000u)

#define CSL_LCDC_LCDRASTSUBPANDISPM_RESETVAL (0x0000u)

/* LCDDMACRL */


#define CSL_LCDC_LCDDMACRL_BURST_SIZE_MASK (0x0070u)
#define CSL_LCDC_LCDDMACRL_BURST_SIZE_SHIFT (0x0004u)
#define CSL_LCDC_LCDDMACRL_BURST_SIZE_RESETVAL (0x0000u)
/*----BURST_SIZE Tokens----*/
#define CSL_LCDC_LCDDMACRL_BURST_SIZE_BSIZE1 (0x0000u)

#define CSL_LCDC_LCDDMACRL_BYTE_SWP_MASK (0x0008u)
#define CSL_LCDC_LCDDMACRL_BYTE_SWP_SHIFT (0x0003u)
#define CSL_LCDC_LCDDMACRL_BYTE_SWP_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMACRL_EOF_INTEN_MASK (0x0004u)
#define CSL_LCDC_LCDDMACRL_EOF_INTEN_SHIFT (0x0002u)
#define CSL_LCDC_LCDDMACRL_EOF_INTEN_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMACRL_BIGENDIAN_MASK (0x0002u)
#define CSL_LCDC_LCDDMACRL_BIGENDIAN_SHIFT (0x0001u)
#define CSL_LCDC_LCDDMACRL_BIGENDIAN_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMACRL_FRAME_MODE_MASK (0x0001u)
#define CSL_LCDC_LCDDMACRL_FRAME_MODE_SHIFT (0x0000u)
#define CSL_LCDC_LCDDMACRL_FRAME_MODE_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMACRL_RESETVAL (0x0000u)

/* LCDDMACRM */


#define CSL_LCDC_LCDDMACRM_RESETVAL (0x0000u)

/* LCDDMAFB0BARL */

#define CSL_LCDC_LCDDMAFB0BARL_FB0_BASE_MASK (0xFFFCu)
#define CSL_LCDC_LCDDMAFB0BARL_FB0_BASE_SHIFT (0x0002u)
#define CSL_LCDC_LCDDMAFB0BARL_FB0_BASE_RESETVAL (0x0000u)


#define CSL_LCDC_LCDDMAFB0BARL_RESETVAL (0x0000u)

/* LCDDMAFB0BARM */

#define CSL_LCDC_LCDDMAFB0BARM_FB0_BASE_MASK (0xFFFFu)
#define CSL_LCDC_LCDDMAFB0BARM_FB0_BASE_SHIFT (0x0000u)
#define CSL_LCDC_LCDDMAFB0BARM_FB0_BASE_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMAFB0BARM_RESETVAL (0x0000u)

/* LCDDMAFB0CARL */

#define CSL_LCDC_LCDDMAFB0CARL_FB0_CEIL_MASK (0xFFFCu)
#define CSL_LCDC_LCDDMAFB0CARL_FB0_CEIL_SHIFT (0x0002u)
#define CSL_LCDC_LCDDMAFB0CARL_FB0_CEIL_RESETVAL (0x0000u)


#define CSL_LCDC_LCDDMAFB0CARL_RESETVAL (0x0000u)

/* LCDDMAFB0CARM */

#define CSL_LCDC_LCDDMAFB0CARM_FB0_CEIL_MASK (0xFFFFu)
#define CSL_LCDC_LCDDMAFB0CARM_FB0_CEIL_SHIFT (0x0000u)
#define CSL_LCDC_LCDDMAFB0CARM_FB0_CEIL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMAFB0CARM_RESETVAL (0x0000u)

/* LCDDMAFB1BARL */

#define CSL_LCDC_LCDDMAFB1BARL_FB1_BASE_MASK (0xFFFCu)
#define CSL_LCDC_LCDDMAFB1BARL_FB1_BASE_SHIFT (0x0002u)
#define CSL_LCDC_LCDDMAFB1BARL_FB1_BASE_RESETVAL (0x0000u)


#define CSL_LCDC_LCDDMAFB1BARL_RESETVAL (0x0000u)

/* LCDDMAFB1BARM */

#define CSL_LCDC_LCDDMAFB1BARM_FB1_BASE_MASK (0xFFFFu)
#define CSL_LCDC_LCDDMAFB1BARM_FB1_BASE_SHIFT (0x0000u)
#define CSL_LCDC_LCDDMAFB1BARM_FB1_BASE_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMAFB1BARM_RESETVAL (0x0000u)

/* LCDDMAFB1CARL */

#define CSL_LCDC_LCDDMAFB1CARL_FB1_CEIL_MASK (0xFFFCu)
#define CSL_LCDC_LCDDMAFB1CARL_FB1_CEIL_SHIFT (0x0002u)
#define CSL_LCDC_LCDDMAFB1CARL_FB1_CEIL_RESETVAL (0x0000u)


#define CSL_LCDC_LCDDMAFB1CARL_RESETVAL (0x0000u)

/* LCDDMAFB1CARM */

#define CSL_LCDC_LCDDMAFB1CARM_FB1_CEIL_MASK (0xFFFFu)
#define CSL_LCDC_LCDDMAFB1CARM_FB1_CEIL_SHIFT (0x0000u)
#define CSL_LCDC_LCDDMAFB1CARM_FB1_CEIL_RESETVAL (0x0000u)

#define CSL_LCDC_LCDDMAFB1CARM_RESETVAL (0x0000u)

#endif
