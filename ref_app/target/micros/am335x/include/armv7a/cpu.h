/*
 *  \file   cpu.h
 *
 *  \brief  CPU related function prototypes
 *
 *  This file contains the API prototypes for configuring CPU
*/

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef __CPU_H
#define __CPU_H

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
**                           FUNCTION PROTOTYPES
*****************************************************************************/
extern void CPUSwitchToUserMode(void);
extern void CPUSwitchToPrivilegedMode(void);

/****************************************************************************/
/*
** Functions used internally
*/
extern void CPUAbortHandler(void);
extern void CPUirqd(void);
extern void CPUirqe(void);
extern void CPUfiqd(void);
extern void CPUfiqe(void);
extern unsigned int CPUIntStatus(void);

#ifdef __cplusplus
}
#endif
#endif /* __CPU_H__ */
