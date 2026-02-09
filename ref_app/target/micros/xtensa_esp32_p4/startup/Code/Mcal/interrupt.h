/******************************************************************************************
  Filename    : interrrupt.h
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : CLIC and CLINT register definition file
  
******************************************************************************************/

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h>

typedef struct {

  uint8_t clicintip;   /* Interrupt pending register      */
  uint8_t clicintie;   /* Interrupt enable register       */
  uint8_t clicintattr; /* Interrupt attribute register    */
  uint8_t clicintct;   /* Interrupt level control register*/
}clicint_t;

typedef struct {

  uint32_t mcliccfg;                                       /* CLIC machine mode global configuration register */
  uint32_t clicinfo;                                       /* CLIC information register                       */
  uint32_t mintthresh;                                     /* CLIC machine mode interrupt threshold register  */
 clicint_t interrupt[48] __attribute__((aligned(0x1000))); /* CLIC interrupt configuration registers          */
}clic_t;

#define CLIC_BASE   0x20800000ul
#define CLIC        ((volatile clic_t*)(CLIC_BASE))

#define CLINT_BASE      0x20000000ul
#define CLINT_MTIMECMP  (*(volatile uint64_t*)(CLINT_BASE + 0x4000ul))
#define CLINT_MTIMELOAD (*(volatile uint64_t*)(CLINT_BASE + 0x4008ul))
#define CLINT_MTIMECTL  (*(volatile uint32_t*)(CLINT_BASE + 0x4010ul))
#define CLINT_MTIME     (*(volatile uint64_t*)(CLINT_BASE + 0xBFF8ul))


#define INT_SW_ID      3
#define INT_TIMER_ID   7
#define EXT_INT00_ID  16
#define EXT_INT01_ID  17
#define EXT_INT02_ID  18
#define EXT_INT03_ID  19
#define EXT_INT04_ID  20
#define EXT_INT05_ID  21
#define EXT_INT06_ID  22
#define EXT_INT07_ID  23
#define EXT_INT08_ID  24
#define EXT_INT09_ID  25
#define EXT_INT10_ID  26
#define EXT_INT11_ID  27
#define EXT_INT12_ID  28
#define EXT_INT13_ID  29
#define EXT_INT14_ID  30
#define EXT_INT15_ID  31
#define EXT_INT16_ID  32
#define EXT_INT17_ID  33
#define EXT_INT18_ID  34
#define EXT_INT19_ID  35
#define EXT_INT20_ID  36
#define EXT_INT21_ID  37
#define EXT_INT22_ID  38
#define EXT_INT23_ID  39
#define EXT_INT24_ID  40
#define EXT_INT25_ID  41
#define EXT_INT26_ID  42
#define EXT_INT27_ID  43
#define EXT_INT28_ID  44
#define EXT_INT29_ID  45
#define EXT_INT30_ID  46
#define EXT_INT31_ID  47


#endif /* __INTERRUPT_H__ */
