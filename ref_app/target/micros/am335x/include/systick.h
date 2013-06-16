/*
 * \file   systick.h
 *
 * \brief  This file contains the prototypes of the functions present in
 *         utils/src/systick.c
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

void SystickConfigure(void (*pfnHandler)(void));
void SystickPeriodSet(unsigned int milliSec);
void SystickEnable(void);
void SystickDisable(void);

/*
*External functions.
*/
extern void TimerTickConfigure(void (*pfnHandler)(void));
extern void TimerTickPeriodSet(unsigned int milliSec);
extern void TimerTickEnable(void);
extern void TimerTickDisable(void);


#ifdef __cplusplus
}
#endif
#endif


