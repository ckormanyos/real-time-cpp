///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from

/******************************************************************************************
  Filename    : Cache.h

  Core        : ARM Cortex-M7

  MCU         : STM32H7A3ZI

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 24.11.2022

  Description : Cache maintenance header file

******************************************************************************************/
#ifndef CACHE_2022_11_25_H_
#define CACHE_2022_11_25_H_

#if defined(__cplusplus)
extern "C"
{
#endif

/* =========================================================================================================================== */
/* ================                                           CACHE                                           ================ */
/* =========================================================================================================================== */
typedef union
{
  struct
  {
    unsigned long ICL1 :1;
    unsigned long DCL1 :1;
    unsigned long      :22;
    unsigned long LOC  :3;
    unsigned long LOU  :3;
    unsigned long      :2;
  }bits;

  unsigned long reg;
}CLIDR_Type;


typedef union
{
  struct
  {
    unsigned long IminLine :4;
    unsigned long          :12;
    unsigned long DMinLine :4;
    unsigned long ERG      :4;
    unsigned long CWG      :4;
    unsigned long          :1;
    unsigned long Format   :3;

  }bits;

  unsigned long reg;
}CTR_Type;


typedef union
{
  struct
  {
    unsigned long LineSize      :3;
    unsigned long Associativity :10;
    unsigned long NumSets       :15;
    unsigned long WA            :1;
    unsigned long RA            :1;
    unsigned long WB            :1;
    unsigned long WT            :1;
  }bits;

  unsigned long reg;
}CCSIDR_Type;

typedef union
{
  struct
  {
    unsigned long InD   :1;
    unsigned long Level :3;
    unsigned long       :28;
  }bits;

  unsigned long reg;
}CSSELR_Type;

typedef union
{
  struct
  {
    unsigned long MVA :32;
  }bits;

  unsigned long reg;
}ICIALLU_Type;

typedef union
{
  struct
  {
    unsigned long     :5;
    unsigned long Set :9;
    unsigned long     :16;
    unsigned long Way :2;
  }bits;

  unsigned long reg;
}ICIMVAU_Type;

typedef union
{
  struct
  {
    unsigned long MVA :32;
  }bits;

  unsigned long reg;
}DCIMVAC_Type;

typedef union
{
  struct
  {
    unsigned long     :5;
    unsigned long Set :9;
    unsigned long     :16;
    unsigned long Way :2;
  }bits;

  unsigned long reg;
}DCISW_Type;

typedef union
{
  struct
  {
    unsigned long MVA :32;
  }bits;

  unsigned long reg;
}DCCMVAU_Type;

typedef union
{
  struct
  {
    unsigned long MVA :32;
  }bits;

  unsigned long reg;
}DCCMVAC_Type;

typedef union
{
  struct
  {
    unsigned long     :5;
    unsigned long Set :9;
    unsigned long     :16;
    unsigned long Way :2;
  }bits;

  unsigned long reg;
}DCCSW_Type;

typedef union
{
  struct
  {
    unsigned long MVA :32;
  }bits;

  unsigned long reg;
}DCCIMVAC_Type;

typedef union
{
  struct
  {
    unsigned long     :5;
    unsigned long Set :9;
    unsigned long     :16;
    unsigned long Way :2;
  }bits;

  unsigned long reg;
}DCCISW_Type;

/* =========================================================================================================================== */
/* ================                                           CACHE REGISTERS                                 ================ */
/* =========================================================================================================================== */
#define CLIDR    ((volatile const CLIDR_Type*   )(0xE000ED78UL))
#define CTR      ((volatile const CTR_Type*     )(0xE000ED7CUL))
#define CCSIDR   ((volatile const CCSIDR_Type*  )(0xE000ED80UL))
#define CSSELR   ((volatile       CSSELR_Type*  )(0xE000ED84UL))
#define ICIALLU  ((volatile       ICIALLU_Type* )(0xE000EF50UL))
#define ICIMVAU  ((volatile       ICIMVAU_Type* )(0xE000EF58UL))
#define DCIMVAC  ((volatile       DCIMVAC_Type* )(0xE000EF5CUL))
#define DCISW    ((volatile       DCISW_Type*   )(0xE000EF60UL))
#define DCCMVAU  ((volatile       DCCMVAU_Type* )(0xE000EF64UL))
#define DCCMVAC  ((volatile       DCCMVAC_Type* )(0xE000EF68UL))
#define DCCSW    ((volatile       DCCSW_Type*   )(0xE000EF6CUL))
#define DCCIMVAC ((volatile       DCCIMVAC_Type*)(0xE000EF70UL))
#define DCCISW   ((volatile       DCCISW_Type*  )(0xE000EF74UL))

void Cache_EnableICache(void);
void Cache_DisableICache(void);
void Cache_InvalidateICache(void);
void Cache_EnableDCache(void);
void Cache_DisableDCache(void);
void Cache_InvalidateDCache(void);
void Cache_CleanDCache(void);
void Cache_CleanInvlaidateDCache(void);

#if defined(__cplusplus)
}
#endif

#endif // CACHE_2022_11_25_H_
