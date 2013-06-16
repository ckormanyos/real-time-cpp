/** ============================================================================
 *   \file  hw_usbOtg.h
 *
 *   \brief This file contains the offset of USB OTG registers
 *
 *  ============================================================================
 */

/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

//*****************************************************************************
//
// hw_usbOtg.h - Macros for use in accessing the USB registers.
//
//*****************************************************************************
#ifndef __HW_USBOTG_H__
#define __HW_USBOTG_H__

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

//*****************************************************************************
//
// The following are defines for the Univeral Serial Bus OTG register offsets.
//
//*****************************************************************************

//
//USB subsystem base address
//
#define USBSS_BASE					0x47400000
//
//USB0 base address
//
#define USB_0_OTGBASE				0x47401000
//
//USB1 base address
//
#define USB_1_OTGBASE				0x47401800

//
//USB subsystem register offsets
//
#define USBSS_IRQ_EOI				0x20
#define USBSS_IRQ_STATUS_RAW		0x24
#define USBSS_IRQ_STATUS			0x28
#define USBSS_IRQ_ENABLE_SET		0x2C
#define USBSS_IRQ_ENABLE_CLR		0x30

//
//USB0 offset register offsets
//
#define USB_0_REVISION				0x00
#define USB_0_CTRL	            	0x14
#define USB_0_STAT	            	0x18
#define USB_0_IRQ_MERGED_STATUS		0x20
#define USB_0_IRQ_EOI				0x24
#define USB_0_IRQ_STATUS_RAW_0 		0x28
#define USB_0_IRQ_STATUS_RAW_1 		0x2C
#define USB_0_IRQ_STATUS_0     		0x30
#define USB_0_IRQ_STATUS_1     		0x34
#define USB_0_IRQ_ENABLE_SET_0 		0x38
#define USB_0_IRQ_ENABLE_SET_1 		0x3C
#define USB_0_IRQ_ENABLE_CLR_0 		0x40
#define USB_0_IRQ_ENABLE_CLR_1 		0x44

#define USB_0_TX_MODE				0x70
#define USB_0_RX_MODE				0x74

#define USB_0_GEN_RNDIS_SIZE_EP1	0x80
#define USB_0_GEN_RNDIS_SIZE_EP2	0x84
#define USB_0_GEN_RNDIS_SIZE_EP3	0x88
#define USB_0_GEN_RNDIS_SIZE_EP4	0x8C
#define USB_0_GEN_RNDIS_SIZE_EP5	0x90
#define USB_0_GEN_RNDIS_SIZE_EP6	0x94
#define USB_0_GEN_RNDIS_SIZE_EP7	0x98
#define USB_0_GEN_RNDIS_SIZE_EP8	0x9C
#define USB_0_GEN_RNDIS_SIZE_EP9	0xA0
#define USB_0_GEN_RNDIS_SIZE_EP10	0xA4
#define USB_0_GEN_RNDIS_SIZE_EP11	0xA8
#define USB_0_GEN_RNDIS_SIZE_EP12	0xAC
#define USB_0_GEN_RNDIS_SIZE_EP13	0xB0
#define USB_0_GEN_RNDIS_SIZE_EP14	0xB4
#define USB_0_GEN_RNDIS_SIZE_EP15	0xB8

#define USB_0_AUTO_REQ				0xD0 						
#define USB_0_SRP_FIX_TIME          0xD4
#define USB_0_TEARDOWN              0xD8
#define USB_0_THRESHOLD_XDMA_IDLE   0xDC
#define USB_0_PHY_UTMI              0xE0
#define USB_0_MGC_UTMI_LOOPBACK     0xE4
#define USB_0_MODE                  0xE8

#ifdef __cplusplus
}
#endif

#endif // __HW_USBOTG_H__

