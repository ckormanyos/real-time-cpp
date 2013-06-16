/*
 * \file   uartStdio.h
 *
 * \brief  This file contains the prototypes of the functions present in
 *         utils/src/uartStdio.c
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


#ifndef _UARTSTDIO_H_
#define _UARTSTDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                    MACRO DEFINITIONS
****************************************************************************/

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

extern unsigned int UARTPuts(char *pTxBuffer, int numBytesToWrite);
extern unsigned int UARTGets(char *pRxBuffer, int numBytesToRead);
extern int UARTwrite(const char *pcBuf, unsigned long ulLen);
extern void UARTprintf(const char *pcString, ...);
extern void UARTPutHexNum(unsigned int hexValue);
extern void UARTPutc(unsigned char byteTx);
extern unsigned char UARTGetc(void);
extern void UARTPutNum(int value);
extern void UARTStdioInit(void);
extern int UARTGetNum(void);

#ifdef __cplusplus
}
#endif
#endif
