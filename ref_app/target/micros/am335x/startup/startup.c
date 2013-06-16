/*
 * \file startup.c
 *
 * \brief  Configures the PLL registers to achieve the required Operating 
 *         frequency. Power and sleep controller is activated for UART and
 *         Interuppt controller. Interrupt vector is copied to the shared Ram.
 *         After doing all the above, controller is given to the application. 
 *  
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include "soc_AM335x.h"
#include "hw_types.h"
#include "cp15.h"

/***********************************************************************
**                            MACRO DEFINITIONS
***********************************************************************/
#define E_PASS                         (0)
#define E_FAIL                         (-1)


/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/
extern void Entry(void);
extern void UndefInstHandler(void);
extern void SVCHandler(void);
extern void AbortHandler(void);
extern void IRQHandler(void);
extern void FIQHandler(void);

/**********************************************************************
*                   INTERNAL FUNCTION PROTOTYPES
**********************************************************************/

unsigned int PLL0Init(unsigned char clk_src, unsigned char pllm,
                      unsigned char prediv, unsigned char postdiv,
                      unsigned char div1, unsigned char div3,
                      unsigned char div7);
unsigned int PLL1Init(unsigned char pllm, unsigned char postdiv,
                      unsigned char div1, unsigned char div2,
                      unsigned char div3);
unsigned int DDR_Init ( unsigned int freq );
static void CopyVectorTable(void);
void BootAbort(void);
int main(void);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
const unsigned int AM335X_VECTOR_BASE = 0x4030FC00;

static unsigned int const vecTbl[14]=
{
  0xE59FF018,
  0xE59FF018,
  0xE59FF018,
  0xE59FF018,
  0xE59FF014,
  0xE24FF008,
  0xE59FF010,
  0xE59FF010,
  (unsigned int)Entry,
  (unsigned int)UndefInstHandler,
  (unsigned int)SVCHandler,
  (unsigned int)AbortHandler,
  (unsigned int)IRQHandler,
  (unsigned int)FIQHandler
};


/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * \brief   Boot strap function which enables the PLL(s) and PSC(s) for basic
 *          module(s)
 *
 * \param   none
 *
 * \return  None.
 * 
 * This function is the first function that needs to be called in a system.
 * This should be set as the entry point in the linker script if loading the
 * elf binary via a debugger, on the target. This function never returns, but
 * gives control to the application entry point
 **/
unsigned int start_boot(void) 
{
  CopyVectorTable();

  /* Calling the main */
  main();

  while(1)
  {
    ;
  }
}

static void CopyVectorTable(void)
{
  unsigned int *dest = (unsigned int *)AM335X_VECTOR_BASE;
  unsigned int *src =  (unsigned int *)vecTbl;
  unsigned int count;

  CP15VectorBaseAddrSet(AM335X_VECTOR_BASE);

  for(count = 0; count < sizeof(vecTbl)/sizeof(vecTbl[0]); count++)
  {
    dest[count] = src[count];
  }
}


void BootAbort(void)
{
  while(1)
  {
    ;
  }
}
