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
#include <Cache.h>
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
    SCB->CCR.bit.IC = 1u;
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
    SCB->CCR.bit.IC = 0u;
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
  uint32_t sets = 0;
  uint32_t ways = 0;

  if(!SCB->CCR.bit.DC)
  {
    /* Enable selection of data cache */
    CSSELR->reg = 0;
    __asm("DSB");

    /* Invalidate the data cache */
    sets = CCSIDR->bits.NumSets;
    do
    {
      ways = CCSIDR->bits.LineSize;
      
      do
      {
        DCISW->bits.Set = sets;
        DCISW->bits.Way = ways;
      }while(ways-- != 0);
    
    }while(sets-- != 0);
    __asm("DSB");

    /* Enable the data cache */
    SCB->CCR.bit.DC = 1u;
    __asm("DSB");
    __asm("ISB");
  }
}

extern "C"
void Cache_DisableDCache(void)
{
  uint32_t sets = 0;
  uint32_t ways = 0;

  if(SCB->CCR.bit.DC)
  {
    /* Enable selection of data cache */
    CSSELR->reg = 0;
    __asm("DSB");

    /* Disable the data cache */
    SCB->CCR.bit.DC = 0u;
    __asm("DSB");
    __asm("ISB");

    /* Clean and invalidate the data cache */
    sets = CCSIDR->bits.NumSets;
    do
    {
      ways = CCSIDR->bits.LineSize;
      
      do
      {
        DCCISW->bits.Set = sets;
        DCCISW->bits.Way = ways;
      }while(ways-- != 0);
    
    }while(sets-- != 0);
    
    __asm("DSB");
    __asm("ISB");
  }
}

extern "C"
void Cache_InvalidateDCache(void)
{
  uint32_t sets = 0;
  uint32_t ways = 0;

  /* Enable selection of data cache */
  CSSELR->reg = 0;
  __asm("DSB");

  /* Invalidate the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.LineSize;
    
    do
    {
      DCISW->bits.Set = sets;
      DCISW->bits.Way = ways;
    }while(ways-- != 0);
  
  }while(sets-- != 0);
  
  __asm("DSB");
  __asm("ISB");
}

extern "C"
void Cache_CleanDCache(void)
{
  uint32_t sets = 0;
  uint32_t ways = 0;

  /* Enable selection of data cache */
  CSSELR->reg = 0;
  __asm("DSB");

  /* Clean the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.LineSize;
    
    do
    {
      DCCSW->bits.Set = sets;
      DCCSW->bits.Way = ways;
    }while(ways-- != 0);
  
  }while(sets-- != 0);
  
  __asm("DSB");
  __asm("ISB");
}

extern "C"
void Cache_CleanInvlaidateDCache(void)
{
  uint32_t sets = 0;
  uint32_t ways = 0;

  /* Enable selection of data cache */
  CSSELR->reg = 0;
  __asm("DSB");

  /* Clean and invalidate the data cache */
  sets = CCSIDR->bits.NumSets;
  do
  {
    ways = CCSIDR->bits.LineSize;
    
    do
    {
      DCCISW->bits.Set = sets;
      DCCISW->bits.Way = ways;
    }while(ways-- != 0);
  
  }while(sets-- != 0);
  
  __asm("DSB");
  __asm("ISB");
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
