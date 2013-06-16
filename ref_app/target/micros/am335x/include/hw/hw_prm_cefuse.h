
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
 *  @Filename:    ../../CredDataBase/prcmCRED/prm_cefuse_cred.h
 *
 ============================================================================ */


#ifndef _HW_PRM_CEFUSE_H_
#define _HW_PRM_CEFUSE_H_


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

#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL   (0x0)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST   (0x4)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* PM_CEFUSE_PWRSTCTRL */
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE   (0x00000010u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT   (0x00000004u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_LOWPOWERSTATECHANGE_EN   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE   (0x00000003u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_SHIFT   (0x00000000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_INACT   (0x2u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_ON   (0x3u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTCTRL_POWERSTATE_RESERVED   (0x1u)


/* PM_CEFUSE_PWRSTST */
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION   (0x00100000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION_SHIFT   (0x00000014u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION_NO   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_INTRANSITION_ONGOING   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED   (0x03000000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED_SHIFT   (0x00000018u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LASTPOWERSTATEENTERED_ON   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST   (0x00000004u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST_SHIFT   (0x00000002u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_LOGICSTATEST_ON   (0x1u)

#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST   (0x00000003u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_SHIFT   (0x00000000u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_INACTIVE   (0x2u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_OFF   (0x0u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_ON   (0x3u)
#define PRM_CEFUSE_PM_CEFUSE_PWRSTST_POWERSTATEST_RET   (0x1u)



#endif
