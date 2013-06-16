/*
 * hw_types.h
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef _HW_TYPES_H_
#define _HW_TYPES_H_

//*****************************************************************************
//
// Define a boolean type, and values for true and false.
//
//*****************************************************************************
typedef unsigned char tBoolean;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef NULL
#define NULL ((void*) 0)
#endif
//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x)                                                              \
        (*((volatile unsigned int *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((unsigned int)(x) & 0xF0000000) | 0x02000000 |                \
              (((unsigned int)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((unsigned int)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned int)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((unsigned int)(x) & 0xF0000000) | 0x02000000 |               \
               (((unsigned int)(x) & 0x000FFFFF) << 5) | ((b) << 2))

#define TRUE    1
#define FALSE   0

#endif // __HW_TYPES_H__
