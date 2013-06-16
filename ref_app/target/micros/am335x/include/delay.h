/*
 * \file   delay.h
 *
 * \brief  This file contains the prototypes of the functions present in
 *         utils/src/delay.c
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


#ifndef _DELAY_H_
#define _DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif
void DelayTimerSetup(void);
void delay(unsigned int milliSec);

/*
* External functions
*/
extern void SysDelayTimerSetup(void);
extern void Sysdelay(unsigned int milliSec);

#ifdef __cplusplus
}
#endif
#endif


