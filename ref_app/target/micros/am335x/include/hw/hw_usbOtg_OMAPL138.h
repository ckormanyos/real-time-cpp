/**
 * \file  hw_usbOtg_OMAPL138.h
 *
 * \brief This file contains the offset of USB OTG registers
 */

/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED */

#ifndef __HW_USBOTG_H__
#define __HW_USBOTG_H__

/* If building with a C++ compiler, make all of the definitions in this header
 * have a C binding. */
#ifdef __cplusplus
extern "C"
{
#endif

/* The following are defines for the Univeral Serial Bus OTG register offsets. */

#define USB_0_OTGBASE				SOC_USB_0_OTG_BASE

#define USB_0_REVISION				0x00
#define USB_0_CTRL	            	0x04
#define USB_0_STAT	            	0x08
#define USB_0_EMULATION				0x08
#define USB_0_MODE					0x10    
#define USB_0_AUTOREQ 	        	0x14
#define USB_0_SRP_FIX_TIME 	    	0x18
#define USB_0_TEARDOWN 	        	0x1c
#define USB_0_INTR_SRC        		0x20
#define USB_0_INTR_SRC_SET 	    	0x24
#define USB_0_INTR_SRC_CLEAR 		0x28
#define USB_0_INTR_MASK 	       	0x2c
#define USB_0_INTR_MASK_SET 	   	0x30
#define USB_0_INTR_MASK_CLEAR 	 	0x34
#define USB_0_INTR_SRC_MASKED 	 	0x38
#define USB_0_END_OF_INTR 	     	0x3c

#define USB_0_GEN_RNDIS_SIZE_EP1	0x50
#define USB_0_GEN_RNDIS_SIZE_EP2	0x54
#define USB_0_GEN_RNDIS_SIZE_EP3	0x58
#define USB_0_GEN_RNDIS_SIZE_EP4	0x5C
#define USB_0_GENR_INTR				0x22

#ifdef __cplusplus
}
#endif

#endif /* __HW_USBOTG_H__ */
