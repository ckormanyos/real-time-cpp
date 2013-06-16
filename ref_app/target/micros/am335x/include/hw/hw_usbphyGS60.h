/** ============================================================================
 *   \file  hw_usbphyGS60.h
 *
 *   \brief This file contains the bit field values to use with the USB phy register
 *
 *  ============================================================================
 */

/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef __HW_USBPHYGS60_H__
#define __HW_USBPHYGS60_H__

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
#define CFGCHIP2_USBPHYCTRL 	SOC_USB_0_PHY_REGS	


/******************************************************************************
**                      BIT FIELDS TO USE WITH PHY REGISTER
*******************************************************************************/
#define CFGCHIP2_PHYCLKGD       (1 << 17)

#define CFGCHIP2_VBUSSENSE      (1 << 16)

#define CFGCHIP2_RESET          (1 << 15)

#define CFGCHIP2_OTGMODE        (3 << 13)

#define CFGCHIP2_NO_OVERRIDE    (0 << 13)

#define CFGCHIP2_FORCE_HOST     (1 << 13)

#define CFGCHIP2_FORCE_DEVICE   (2 << 13)

#define CFGCHIP2_FORCE_HOST_VBUS_LOW (3 << 13)

#define CFGCHIP2_USB1PHYCLKMUX  (1 << 12)

#define CFGCHIP2_USB2PHYCLKMUX  (1 << 11)

#define CFGCHIP2_PHYPWRDN       (1 << 10)

#define CFGCHIP2_OTGPWRDN       (1 << 9)

#define CFGCHIP2_DATPOL         (1 << 8)

#define CFGCHIP2_USB1SUSPENDM   (1 << 7)

#define CFGCHIP2_PHY_PLLON      (1 << 6)        /* override PLL suspend */

#define CFGCHIP2_SESENDEN       (1 << 5)        /* Vsess_end comparator */

#define CFGCHIP2_VBDTCTEN       (1 << 4)        /* Vbus comparator */

#define CFGCHIP2_REFFREQ        (0xf << 0)

#define CFGCHIP2_REFFREQ_12MHZ  (1 << 0)

#define CFGCHIP2_REFFREQ_24MHZ  (2 << 0)

#define CFGCHIP2_REFFREQ_48MHZ  (3 << 0)

void UsbPhyOn(void);
void UsbPhyOff(void);

#ifdef __cplusplus
}
#endif

#endif // __HW_USBPHY_AM1808_H__



