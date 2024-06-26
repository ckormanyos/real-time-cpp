/******************************************************************************************
  Filename    : SysTick.h
  
  Core        : QingKe V4F (RISC-V)
  
  MCU         : CH32V307VCT6 (WCH)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 23.01.2023
  
  Description : system tick timer driver header file
  
******************************************************************************************/

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

//=========================================================================================
// Includes
//=========================================================================================
#include <CH32V30xxx.h>
#include <Platform_Types.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//=========================================================================================
// Types definitions
//=========================================================================================
typedef union
{
 struct
 {
  uint32 u1STE   : 1;
  uint32 u1STIE  : 1;
  uint32 u1STCLK : 1;
  uint32 u1STRE  : 1;
  uint32 u1MODE  : 1;
  uint32 u1INIT  : 1;
  uint32 : 25;
  uint32 u1SWIE : 1;
 }bit;

 uint32 u32Reg;

}stStkCtrl;

typedef union
{
 struct
 {
  uint32 u1CNTIF : 1;
  uint32 : 31;
 }bit;

 uint32 u32Reg;

}stStkSr;

typedef union
{
 struct
 {
  uint32 u32CNTL : 32;
 }bit;

 uint32 u32Reg;

}stStkCntl;

typedef union
{
 struct
 {
  uint32 u32CNTH : 32;
 }bit;

 uint32 u32Reg;

}stStkCnth;

typedef union
{
 struct
 {
  uint32 u32CMPLR : 32;
 }bit;

 uint32 u32Reg;

}stStkCmplr;

typedef union
{
 struct
 {
  uint32 u32CMPHR : 32;
 }bit;

 uint32 u32Reg;

}stStkCmphr;

//=========================================================================================
// Defines
//=========================================================================================
#define STK_BASE_ADDRESS  0xE000F000ul

#define R32_STK_CTLR   ((volatile stStkCtrl*) (STK_BASE_ADDRESS + 0x00ul))
#define R32_STK_SR     ((volatile stStkSr*)   (STK_BASE_ADDRESS + 0x04ul))
#define R32_STK_CNTL   ((volatile stStkCntl*) (STK_BASE_ADDRESS + 0x08ul))
#define R32_STK_CNTH   ((volatile stStkCnth*) (STK_BASE_ADDRESS + 0x0Cul))
#define R32_STK_CMPLR  ((volatile stStkCmplr*)(STK_BASE_ADDRESS + 0x10ul))
#define R32_STK_CMPHR  ((volatile stStkCmphr*)(STK_BASE_ADDRESS + 0x14ul))

//=========================================================================================
// Macros
//=========================================================================================
#define CORE_FREQ_MHZ              (uint64)144000000ull
#define SYSTICK_TIMEOUT_SEC(t)     (uint64)(CORE_FREQ_MHZ * t)
#define SYSTICK_TIMEOUT_MSEC(t)    (uint64)((uint64)(CORE_FREQ_MHZ * t) / 1000U)
#define SYSTICK_TIMEOUT_USEC(t)    (uint64)((uint64)(CORE_FREQ_MHZ * t) / 1000000UL)

//=========================================================================================
// Function prototypes
//========================================================================================= 
void   SysTick_Init(void);
uint64 SysTick_Get();

#if defined(__cplusplus)
}
#endif

#endif /* __SYSTICK_H__ */
