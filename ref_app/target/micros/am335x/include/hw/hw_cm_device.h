
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
 *  @Component:   CM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/cm_device_cred.h
 *
 ============================================================================ */


#ifndef _HW_CM_DEVICE_H_
#define _HW_CM_DEVICE_H_


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

#define CM_DEVICE_CM_CLKOUT_CTRL   (0x0)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* CM_CLKOUT_CTRL */
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV   (0x00000038u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_SHIFT   (0x00000003u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV1   (0x0u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV2   (0x1u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV3   (0x2u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV4   (0x3u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV5   (0x4u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV6   (0x5u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV7   (0x6u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_DIV8   (0x7u)

#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN   (0x00000080u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN_SHIFT   (0x00000007u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN_DIS   (0x0u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN_EN   (0x1u)

#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE   (0x00000007u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SHIFT   (0x00000000u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL0   (0x0u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL1   (0x1u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL2   (0x2u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL4   (0x3u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SEL5   (0x4u)



#endif
