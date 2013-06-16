/** ============================================================================
 *   \file  hw_usbphy_AM335x.h
 *
 *   \brief This file contains the bit field values to use with the USB phy register
 *
 *  ============================================================================
 */

/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef __HW_USBPHY_AM335x_H__
#define __HW_USBPHY_AM335x_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
**                      PHY REGISTER ADDRESS
*******************************************************************************/
#define CFGCHIP2_USBPHYCTRL 	0x44E10620	


/******************************************************************************
**                      BIT FIELDS TO USE WITH PHY REGISTER
*******************************************************************************/
#define	USBPHY_CM_PWRDN				(1 << 0)
#define	USBPHY_OTG_PWRDN			(1 << 1)
#define	USBPHY_OTGVDET_EN			(1 << 19)
#define	USBPHY_OTGSESSEND_EN		(1 << 20)

void UsbPhyOn(void);
void UsbPhyOff(void);

#ifdef __cplusplus
}
#endif

#endif // __HW_USBPHY_AM335x_H__
