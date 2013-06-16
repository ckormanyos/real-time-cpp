
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
 *  @Filename:    ../../CredDataBase/prcmCRED/cm_rtc_cred.h
 *
 ============================================================================ */


#ifndef _HW_CM_RTC_H_
#define _HW_CM_RTC_H_


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

#define CM_RTC_RTC_CLKCTRL   (0x0)
#define CM_RTC_CLKSTCTRL   (0x4)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* RTC_CLKCTRL */
#define CM_RTC_RTC_CLKCTRL_IDLEST   (0x00030000u)
#define CM_RTC_RTC_CLKCTRL_IDLEST_SHIFT   (0x00000010u)
#define CM_RTC_RTC_CLKCTRL_IDLEST_DISABLE   (0x3u)
#define CM_RTC_RTC_CLKCTRL_IDLEST_FUNC   (0x0u)
#define CM_RTC_RTC_CLKCTRL_IDLEST_IDLE   (0x2u)
#define CM_RTC_RTC_CLKCTRL_IDLEST_TRANS   (0x1u)

#define CM_RTC_RTC_CLKCTRL_MODULEMODE   (0x00000003u)
#define CM_RTC_RTC_CLKCTRL_MODULEMODE_SHIFT   (0x00000000u)
#define CM_RTC_RTC_CLKCTRL_MODULEMODE_DISABLED   (0x0u)
#define CM_RTC_RTC_CLKCTRL_MODULEMODE_ENABLE   (0x2u)
#define CM_RTC_RTC_CLKCTRL_MODULEMODE_RESERVED   (0x3u)
#define CM_RTC_RTC_CLKCTRL_MODULEMODE_RESERVED_1   (0x1u)


/* CLKSTCTRL */
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_L4_RTC_GCLK   (0x00000100u)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_L4_RTC_GCLK_SHIFT   (0x00000008u)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_L4_RTC_GCLK_ACT   (0x1u)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_L4_RTC_GCLK_INACT   (0x0u)

#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_32KCLK   (0x00000200u)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_32KCLK_SHIFT   (0x00000009u)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_32KCLK_ACT   (0x1u)
#define CM_RTC_CLKSTCTRL_CLKACTIVITY_RTC_32KCLK_INACT   (0x0u)

#define CM_RTC_CLKSTCTRL_CLKTRCTRL   (0x00000003u)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_SHIFT   (0x00000000u)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_HW_AUTO   (0x3u)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_NO_SLEEP   (0x0u)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_SW_SLEEP   (0x1u)
#define CM_RTC_CLKSTCTRL_CLKTRCTRL_SW_WKUP   (0x2u)



#endif
