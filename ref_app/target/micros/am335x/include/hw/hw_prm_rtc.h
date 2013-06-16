
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
 *  @Component:   PRM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/prm_rtc_cred.h
 *
 ============================================================================ */


#ifndef _HW_PRM_RTC_H_
#define _HW_PRM_RTC_H_


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

#define PRM_RTC_PM_RTC_PWRSTCTRL   (0x0)
#define PRM_RTC_PM_RTC_PWRSTST   (0x4)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* PM_RTC_PWRSTCTRL */
#define PRM_RTC_PM_RTC_PWRSTCTRL_LOGICRETSTATE   (0x00000004u)
#define PRM_RTC_PM_RTC_PWRSTCTRL_LOGICRETSTATE_SHIFT   (0x00000002u)
#define PRM_RTC_PM_RTC_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF   (0x0u)
#define PRM_RTC_PM_RTC_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET   (0x1u)

#define PRM_RTC_PM_RTC_PWRSTCTRL_LOWPOWERSTATECHANGE   (0x00000010u)
#define PRM_RTC_PM_RTC_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT   (0x00000004u)
#define PRM_RTC_PM_RTC_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS   (0x0u)
#define PRM_RTC_PM_RTC_PWRSTCTRL_LOWPOWERSTATECHANGE_EN   (0x1u)


/* PM_RTC_PWRSTST */
#define PRM_RTC_PM_RTC_PWRSTST_INTRANSITION   (0x00100000u)
#define PRM_RTC_PM_RTC_PWRSTST_INTRANSITION_SHIFT   (0x00000014u)
#define PRM_RTC_PM_RTC_PWRSTST_INTRANSITION_NO   (0x0u)
#define PRM_RTC_PM_RTC_PWRSTST_INTRANSITION_ONGOING   (0x1u)

#define PRM_RTC_PM_RTC_PWRSTST_LOGICSTATEST   (0x00000004u)
#define PRM_RTC_PM_RTC_PWRSTST_LOGICSTATEST_SHIFT   (0x00000002u)
#define PRM_RTC_PM_RTC_PWRSTST_LOGICSTATEST_OFF   (0x0u)
#define PRM_RTC_PM_RTC_PWRSTST_LOGICSTATEST_ON   (0x1u)



#endif
