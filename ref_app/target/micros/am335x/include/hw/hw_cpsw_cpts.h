
/* ============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only
 *  Unauthorized reproduction and/or distribution is strictly prohibited.
 *  This product is protected under copyright law and trade secret law
 *  as an unpublished work.
 *  Created 2008, (C) Copyright 2008 Texas Instruments.  All rights reserved.
 *
 */

/**
 *  @Component:   CPSW
 *
 *  @Filename:    cpsw_cpts_cred.h
 *
 ============================================================================ */


#ifndef _HW_CPSW_CPTS_H_
#define _HW_CPSW_CPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************\
 * Register arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundle arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundles Definition
\***********************************************************************/



/*************************************************************************\
 * Registers Definition
\*************************************************************************/

#define CPSW_CPTS_IDVER   (0x00)
#define CPSW_CPTS_CONTROL   (0x04)
#define CPSW_CPTS_RFTCLK_SEL   (0x08)
#define CPSW_CPTS_TS_PUSH   (0x0c)
#define CPSW_CPTS_TS_LOAD_VAL   (0x10)
#define CPSW_CPTS_TS_LOAD_EN   (0x14)
#define CPSW_CPTS_INTSTAT_RAW   (0x20)
#define CPSW_CPTS_INTSTAT_MASKED   (0x24)
#define CPSW_CPTS_INT_ENABLE   (0x28)
#define CPSW_CPTS_EVENT_POP   (0x30)
#define CPSW_CPTS_EVENT_LOW   (0x34)
#define CPSW_CPTS_EVENT_HIGH   (0x38)

/**************************************************************************\
 * Field Definition Macros
\**************************************************************************/

/* CPTS_IDVER */
#define CPSW_CPTS_IDVER_MAJOR_VER   (0x00000700u)
#define CPSW_CPTS_IDVER_MAJOR_VER_SHIFT   (0x00000008u)

#define CPSW_CPTS_IDVER_MINOR_VER   (0x000000FFu)
#define CPSW_CPTS_IDVER_MINOR_VER_SHIFT   (0x00000000u)

#define CPSW_CPTS_IDVER_RTL_VER   (0x0000F800u)
#define CPSW_CPTS_IDVER_RTL_VER_SHIFT   (0x0000000Bu)

#define CPSW_CPTS_IDVER_TX_IDENT   (0xFFFF0000u)
#define CPSW_CPTS_IDVER_TX_IDENT_SHIFT   (0x00000010u)


/* CPTS_CONTROL */
#define CPSW_CPTS_CONTROL_CPTS_EN   (0x00000001u)
#define CPSW_CPTS_CONTROL_CPTS_EN_SHIFT   (0x00000000u)

#define CPSW_CPTS_CONTROL_HW1_TS_PUSH_EN   (0x00000100u)
#define CPSW_CPTS_CONTROL_HW1_TS_PUSH_EN_SHIFT   (0x00000008u)

#define CPSW_CPTS_CONTROL_HW2_TS_PUSH_EN   (0x00000200u)
#define CPSW_CPTS_CONTROL_HW2_TS_PUSH_EN_SHIFT   (0x00000009u)

#define CPSW_CPTS_CONTROL_HW3_TS_PUSH_EN   (0x00000400u)
#define CPSW_CPTS_CONTROL_HW3_TS_PUSH_EN_SHIFT   (0x0000000Au)

#define CPSW_CPTS_CONTROL_HW4_TS_PUSH_EN   (0x00000800u)
#define CPSW_CPTS_CONTROL_HW4_TS_PUSH_EN_SHIFT   (0x0000000Bu)

#define CPSW_CPTS_CONTROL_INT_TEST   (0x00000002u)
#define CPSW_CPTS_CONTROL_INT_TEST_SHIFT   (0x00000001u)


/* CPTS_RFTCLK_SEL */
#define CPSW_CPTS_RFTCLK_SEL_RFTCLK_SEL   (0x0000001Fu)
#define CPSW_CPTS_RFTCLK_SEL_RFTCLK_SEL_SHIFT   (0x00000000u)


/* CPTS_TS_PUSH */
#define CPSW_CPTS_TS_PUSH_TS_PUSH   (0x00000001u)
#define CPSW_CPTS_TS_PUSH_TS_PUSH_SHIFT   (0x00000000u)


/* CPTS_TS_LOAD_VAL */
#define CPSW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL   (0xFFFFFFFFu)
#define CPSW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_SHIFT   (0x00000000u)


/* CPTS_TS_LOAD_EN */
#define CPSW_CPTS_TS_LOAD_EN_TS_LOAD_EN   (0x00000001u)
#define CPSW_CPTS_TS_LOAD_EN_TS_LOAD_EN_SHIFT   (0x00000000u)


/* CPTS_INTSTAT_RAW */
#define CPSW_CPTS_INTSTAT_RAW_TS_PEND_RAW   (0x00000001u)
#define CPSW_CPTS_INTSTAT_RAW_TS_PEND_RAW_SHIFT   (0x00000000u)


/* CPTS_INTSTAT_MASKED */
#define CPSW_CPTS_INTSTAT_MASKED_TS_PEND   (0x00000001u)
#define CPSW_CPTS_INTSTAT_MASKED_TS_PEND_SHIFT   (0x00000000u)


/* CPTS_INT_ENABLE */
#define CPSW_CPTS_INT_ENABLE_TS_PEND_EN   (0x00000001u)
#define CPSW_CPTS_INT_ENABLE_TS_PEND_EN_SHIFT   (0x00000000u)


/* CPTS_EVENT_POP */
#define CPSW_CPTS_EVENT_POP_EVENT_POP   (0x00000001u)
#define CPSW_CPTS_EVENT_POP_EVENT_POP_SHIFT   (0x00000000u)


/* CPTS_EVENT_LOW */
#define CPSW_CPTS_EVENT_LOW_TIME_STAMP   (0xFFFFFFFFu)
#define CPSW_CPTS_EVENT_LOW_TIME_STAMP_SHIFT   (0x00000000u)


/* CPTS_EVENT_HIGH */
#define CPSW_CPTS_EVENT_HIGH_EVENT_TYPE   (0x00F00000u)
#define CPSW_CPTS_EVENT_HIGH_EVENT_TYPE_SHIFT   (0x00000014u)

#define CPSW_CPTS_EVENT_HIGH_MESSAGE_TYPE   (0x000F0000u)
#define CPSW_CPTS_EVENT_HIGH_MESSAGE_TYPE_SHIFT   (0x00000010u)

#define CPSW_CPTS_EVENT_HIGH_PORT_NUMBER   (0x1F000000u)
#define CPSW_CPTS_EVENT_HIGH_PORT_NUMBER_SHIFT   (0x00000018u)

#define CPSW_CPTS_EVENT_HIGH_SEQUENCE_ID   (0x0000FFFFu)
#define CPSW_CPTS_EVENT_HIGH_SEQUENCE_ID_SHIFT   (0x00000000u)



#ifdef __cplusplus
}
#endif

#endif
