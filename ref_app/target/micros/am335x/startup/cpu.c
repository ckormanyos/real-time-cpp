/**
 *  \file   cpu.c
 *
 *  \brief  CPU related definitions
 *
 *  This file contains the API definitions for configuring CPU
*/

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include "cpu.h"
#include <am335x_hw_regs.h>
#include <Bfx.h>
#include <string.h>

/*****************************************************************************
**                   FUNCTION DEFINITIONS
******************************************************************************/
/**
 * \brief     This API can be used to switch from user mode to privileged mode
 *            The priviledge mode will be system mode. System mode will share 
 *            the same resources as user mode, but with privileges.
 *
 * \param     None.
 *
 * \return    None.
 *
 * Note : All the access to system configuration which needs privileged access
 *        can be done after calling this API.
 **/
void CPUSwitchToPrivilegedMode(void)
{
    __asm__ volatile ("    SWI   458752");
}

/**
 * \brief     This API can be used to switch from any previleged mode of ARM to 
 *            user mode. After this API is called, the program will continue
 *            to operate in non-privileged mode, until any exception occurs.
 *            After the exception is serviced, execution will continue in user
 *            mode.
 *
 * \param     None.
 *
 * \return    None.
 *
 * Note : All the access to system configuration which needs privileged access
 *        shall be done before this API is called.
 **/
void CPUSwitchToUserMode(void)
{
    __asm__ volatile ("    mrs     r0, CPSR\n\t"
                      "    bic     r0, #0x0F\n\t"
                      "    orr     r0, #0x10\n\t "
                      "    msr     CPSR, r0");
}

unsigned int CPUReadDFSR(void)
{
    unsigned int stat;

    /* IRQ and FIQ in CPSR */
    __asm__ volatile ("    mrc p15, #0, %[result], c5, c0, #0\n\t" : [result] "=r" (stat));

    return stat;
}

unsigned int CPUReadDFAR(void)
{
    unsigned int stat;

    /* IRQ and FIQ in CPSR */
    __asm__ volatile ("    mrc p15, #0, %[result], c6, c0, #0\n\t" : [result] "=r" (stat));

    return stat;
}

char buf[256];
char bufStr[64];

/**
 * \brief     This API is called when the CPU is aborted or during execution
 *            of any undefined instruction. Both IRQ and FIQ will be disabled
 *            when the CPU gets an abort and calls this API. 
 *
 * \param     None.
 *
 * \return    None.
 *
 * Note : The user can perform error handling such as an immediate reset 
 *        inside this API if required.
 **/
void CPUAbortHandler(void)
{
	uint32_t faulttype = CPUReadDFSR();
	// uint32 faultadr = CPUReadDFAR();
//	GPIO1->SETDATAOUT   = 0x00200000u;
	GPIO1->CLEARDATAOUT = 0x01E00000u;
	GPIO1->SETDATAOUT   = (faulttype & 0x0Fu) << 21u;

//    uint32 lcrRegValue = UART0->LCR;
//    UART0->LCR = 0;
//
//    strcat(buf, "\r\nAbort Handler:\n\rType: 0x");
//    itoa(faulttype, bufStr, 16);
//    strcat(buf, bufStr);
//    strcat(buf, "\r\nAdress: 0x");
//    itoa(faultadr, bufStr, 16);
//    strcat(buf, bufStr);
//    strcat(buf, "\n\r");
//
//    int count;
//    for (count = 0; count < sizeof(buf); count++) {
//    	while ((UART0->LSR_XON2ADDR & 0x60u) != 0x60u);
//    	UART0->RHR_THR_DLL = buf[count];
//    }
      /* ; Perform Nothing */
}

/*
**
** Wrapper function for the IRQ status
**
*/
unsigned int CPUIntStatus(void)
{
    unsigned int stat;

    /* IRQ and FIQ in CPSR */
    __asm__ volatile ("    mrs     r0, CPSR\n\t"
                      "    and     %[result], r0, #0xC0" : [result] "=r" (stat));

    return stat;
}

/*
**
** Wrapper function for the IRQ disable function
**
*/
void CPUirqd(void)
{
    /* Disable IRQ in CPSR */
    __asm__ volatile ("    mrs     r0, CPSR\n\t"
                      "    orr     r0, #0x80\n\t"
                      "    msr     CPSR, r0");
}

/*
**
** Wrapper function for the IRQ enable function
**
*/
void CPUirqe(void)
{
    /* Enable IRQ in CPSR */
    __asm__ volatile ("    mrs     r0, CPSR\n\t"
                      "    bic     r0, #0x80\n\t"
                      "    msr     CPSR, r0");
}

/*
**
** Wrapper function for the FIQ disable function
**
*/
void CPUfiqd(void)
{
    /* Disable FIQ in CPSR */
    __asm__ volatile ("    mrs     r0, CPSR\n\t"
                      "    orr     r0, #0x40\n\t"
                      "    msr     CPSR, r0");
}

/*
**
** Wrapper function for the FIQ enable function
**
*/
void CPUfiqe(void)
{
    /* Enable FIQ in CPSR */
    __asm__ volatile ("    mrs     r0, CPSR\n\t"
                      "    bic     r0, #0x40\n\t"
                      "    msr     CPSR, r0");
}

/**************************** End Of File ************************************/
