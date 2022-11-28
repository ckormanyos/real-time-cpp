///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from

/******************************************************************************************
  Filename    : Cache.c

  Core        : ARM Cortex-M7

  MCU         : STM32H7A3ZI

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 24.11.2022

  Description : Cache maintenance driver implementation

******************************************************************************************/

//=========================================================================================
// Includes
//=========================================================================================
#include <mcal_cache.h>
#include <Scb.h>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

extern "C"
void Cache_EnableICache(void)
{
  if(!SCB->CCR.bit.IC)
  {
    __asm("DSB");
    __asm("ISB");

    /* Invalidate the instruction cache */
    ICIALLU->reg = 0UL;
    __asm("DSB");
    __asm("ISB");

    /* Enable the Instruction cache */
    SCB->CCR.bit.IC = 1U;
    __asm("DSB");
    __asm("ISB");
  }
}

extern "C"
void Cache_DisableICache(void)
{
  if(SCB->CCR.bit.IC)
  {
    __asm("DSB");
    __asm("ISB");

    /* Disable the Instruction cache */
    SCB->CCR.bit.IC = 0U;
    __asm("DSB");
    __asm("ISB");

    /* Invalidate the instruction cache */
    ICIALLU->reg = 0UL;
    __asm("DSB");
    __asm("ISB");
  }
}

extern "C"
void Cache_InvalidateICache(void)
{
  __asm("DSB");
  __asm("ISB");

  /* Invalidate the instruction cache */
  ICIALLU->reg = 0UL;

  __asm("DSB");
  __asm("ISB");
}

extern "C"
void Cache_EnableDCache(void)
{
  uint32_t sets = 0U;
  uint32_t ways = 0U;

  if(!SCB->CCR.bit.DC)
  {
    /* Enable selection of data cache */
    CSSELR->reg = 0U;
    __asm("DSB");

    /* Invalidate the data cache */
    sets = CCSIDR->bits.NumSets;
    __asm("DSB");
    do
    {
      ways = CCSIDR->bits.Associativity;
      __asm("DSB");
      do
      {
        DCISW->reg = (uint32_t) ((uint32_t) (ways << 30U) | (uint32_t) (sets << 5U));
        __asm("DSB");
      }while(ways-- != 0U);
      __asm("DSB");
    
    }while(sets-- != 0U);
    __asm("DSB");

    /* Enable the data cache */
    SCB->CCR.bit.DC = 1U;
    __asm("DSB");
    __asm("ISB");
  }
}

extern "C"
void Cache_DisableDCache(void)
{
  uint32_t sets = 0U;
  uint32_t ways = 0U;

  if(SCB->CCR.bit.DC)
  {
    /* Enable selection of data cache */
    CSSELR->reg = 0U;
    __asm("DSB");

    /* Disable the data cache */
    SCB->CCR.bit.DC = 0U;
    __asm("DSB");
    __asm("ISB");

    /* Clean and invalidate the data cache */
    sets = CCSIDR->bits.NumSets;
    do
    {
      ways = CCSIDR->bits.Associativity;
      __asm("DSB");
      do
      {
        DCCISW->reg = (uint32_t) ((uint32_t) (ways << 30U) | (uint32_t) (sets << 5U));
        __asm("DSB");
      }while(ways-- != 0U);
    
    }while(sets-- != 0U);
    
    __asm("DSB");
    __asm("ISB");
  }
}

extern "C"
void Cache_InvalidateDCache(void)
{
  uint32_t sets = 0U;
  uint32_t ways = 0U;

  /* Enable selection of data cache */
  CSSELR->reg = 0U;
  __asm("DSB");

  /* Invalidate the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.Associativity;
    __asm("DSB");
    do
    {
      DCISW->reg = (uint32_t) ((uint32_t) (ways << 30U) | (uint32_t) (sets << 5U));
      __asm("DSB");
    }while(ways-- != 0U);
  
  }while(sets-- != 0U);
  
  __asm("DSB");
  __asm("ISB");
}

extern "C"
void Cache_CleanDCache(void)
{
  uint32_t sets = 0U;
  uint32_t ways = 0U;

  /* Enable selection of data cache */
  CSSELR->reg = 0U;
  __asm("DSB");

  /* Clean the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.Associativity;
    __asm("DSB");
    do
    {
      DCCSW->reg = (uint32_t) ((uint32_t) (ways << 30U) | (uint32_t) (sets << 5U));
      __asm("DSB");
    }while(ways-- != 0U);
  
  }while(sets-- != 0U);
  
  __asm("DSB");
  __asm("ISB");
}

extern "C"
void Cache_CleanInvlaidateDCache(void)
{
  uint32_t sets = 0U;
  uint32_t ways = 0U;

  /* Enable selection of data cache */
  CSSELR->reg = 0U;
  __asm("DSB");

  /* Clean and invalidate the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.Associativity;
    __asm("DSB");
    do
    {
      DCCISW->reg = (uint32_t) ((uint32_t) (ways << 30U) | (uint32_t) (sets << 5U));
      __asm("DSB");
    }while(ways-- != 0U);
  
  }while(sets-- != 0U);
  
  __asm("DSB");
  __asm("ISB");
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
