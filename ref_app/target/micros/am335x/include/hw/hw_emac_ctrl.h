/*
 * hw_emac1.h
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef _HW_EMAC_CTRL_H_
#define _HW_EMAC_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define EMAC_CTRL_REVID              (0x0u)
#define EMAC_CTRL_SOFTRESET          (0x4u)
#define EMAC_CTRL_INTCONTROL         (0xCu)
#define EMAC_CTRL_C0RXTHRESHEN       (0x10u)
#define EMAC_CTRL_CnRXEN(n)          (0x14u + (n << 4))
#define EMAC_CTRL_CnTXEN(n)          (0x18u + (n << 4))
#define EMAC_CTRL_CnMISCEN(n)        (0x1Cu + (n << 4))
#define EMAC_CTRL_CnRXTHRESHEN(n)    (0x20u + (n << 4))
#define EMAC_CTRL_C0RXTHRESHSTAT     (0x40u)
#define EMAC_CTRL_C0RXSTAT           (0x44u)
#define EMAC_CTRL_C0TXSTAT           (0x48u)
#define EMAC_CTRL_C0MISCSTAT         (0x4Cu)
#define EMAC_CTRL_C1RXTHRESHSTAT     (0x50u)
#define EMAC_CTRL_C1RXSTAT           (0x54u)
#define EMAC_CTRL_C1TXSTAT           (0x58u)
#define EMAC_CTRL_C1MISCSTAT         (0x5Cu)
#define EMAC_CTRL_C2RXTHRESHSTAT     (0x60u)
#define EMAC_CTRL_C2RXSTAT           (0x64u)
#define EMAC_CTRL_C2TXSTAT           (0x68u)
#define EMAC_CTRL_C2MISCSTAT         (0x6Cu)
#define EMAC_CTRL_C0RXIMAX           (0x70u)
#define EMAC_CTRL_C0TXIMAX           (0x74u)
#define EMAC_CTRL_C1RXIMAX           (0x78u)
#define EMAC_CTRL_C1TXIMAX           (0x7Cu)
#define EMAC_CTRL_C2RXIMAX           (0x80u)
#define EMAC_CTRL_C2TXIMAX           (0x84u)

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

#ifdef __cplusplus
}
#endif


#endif
