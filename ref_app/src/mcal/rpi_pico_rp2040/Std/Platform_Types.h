/******************************************************************************************
  Filename    : Platform_Types.h
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : Platform types header file
  
******************************************************************************************/

#ifndef __PLATFORM_TYPES_H__
#define __PLATFORM_TYPES_H__

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif

typedef uint8_t  uint8;
typedef  int8_t  sint8;
typedef uint16_t uint16;
typedef  int16_t sint16;
typedef uint32_t uint32;
typedef  int32_t sint32;
typedef uint64_t uint64;
typedef  int64_t sint64;

typedef void (*pFunc)(void);

typedef uint8_t boolean;

#if defined(FALSE)
#undef FALSE
#endif

#if defined(TRUE)
#undef TRUE
#endif

#define FALSE ((boolean) UINT8_C(0))
#define  TRUE ((boolean) UINT8_C(1))

#define NULL_PTR (void*) 0U

#if defined(__cplusplus)
}
#endif

#endif // __PLATFORM_TYPES_H__
