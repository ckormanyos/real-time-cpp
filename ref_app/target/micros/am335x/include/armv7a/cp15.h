/*
 *  \file   cp15.h
 *
 *  \brief  CP15 related function prototypes
 *
 *  This file contains the API prototypes for configuring CP15
*/

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef __CP15_H
#define __CP15_H

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
**                           FUNCTION PROTOTYPES
*****************************************************************************/
extern void CP15DCacheCleanBuff(unsigned int bufPtr, unsigned int size);
extern void CP15ICacheFlushBuff(unsigned int bufPtr, unsigned int size);
extern void CP15ICacheDisable(void);
extern void CP15DCacheDisable(void);
extern void CP15ICacheEnable(void);
extern void CP15DCacheEnable(void);
extern void CP15DCacheCleanFlush(void);
extern void CP15ICacheFlush(void);
extern void CP15Ttb0Set(unsigned int ttb);
extern void CP15TlbInvalidate(void);
extern void CP15MMUDisable(void);
extern void CP15MMUEnable(void);
extern void CP15VectorBaseAddrSet(unsigned int addr);
extern void CP15BranchPredictorInvalidate(void);
extern void CP15BranchPredictionEnable(void);
extern void CP15BranchPredictionDisable(void);
extern void CP15DomainAccessClientSet(void);

#ifdef __cplusplus
}
#endif
#endif /* __CP15_H__ */
