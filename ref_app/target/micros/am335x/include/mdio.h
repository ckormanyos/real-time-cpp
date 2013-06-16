/**
 *  \file   mdio.h
 *
 *  \brief  MDIO APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef __MDIO_H__
#define __MDIO_H__

#include "hw_mdio.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*
** Prototypes for the APIs
*/
extern unsigned int MDIOPhyAliveStatusGet(unsigned int baseAddr);
extern unsigned int MDIOPhyLinkStatusGet(unsigned int baseAddr);
extern void MDIOInit(unsigned int baseAddr, unsigned int mdioInputFreq,
                     unsigned int mdioOutputFreq);
extern unsigned int MDIOPhyRegRead(unsigned int baseAddr, unsigned int phyAddr,
                                   unsigned int regNum, volatile unsigned short *dataPtr);
extern void MDIOPhyRegWrite(unsigned int baseAddr, unsigned int phyAddr,
                            unsigned int regNum, unsigned short RegVal);

#ifdef __cplusplus
}
#endif
#endif /* __MDIO_H__ */
