// ***************************************************************************************
// Filename    : Startup.c
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 11.03.2020
// 
// Description : C/C++ Runtime Setup (Crt0)
// 
// ***************************************************************************************

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>

//=========================================================================================
// Function prototype
//=========================================================================================
extern "C"
{
  extern void Startup_InitRam(void);
  extern void Startup_InitCtors(void);
}

[[noreturn]] static void Startup_RunApplication(void);

//=========================================================================================
// Extern function prototype
//=========================================================================================
extern "C"
{
  int main(void);
}

asm (".extern __STACK_TOP");
asm (".extern InterruptVectorTable");

extern "C"
{
  void __my_startup(void) __attribute__ ((section(".startup")));
}

extern "C" void __my_startup(void)
{
  /* setup the stack pointer */
  asm volatile("la sp, __STACK_TOP");

  /* setup the interrupt vector table */
  asm volatile("la x1, InterruptVectorTable");
  asm volatile("ori x1, x1, 3");
  asm volatile("csrw mtvec, x1");

  mcal::cpu::init();

  /* Initialize the RAM memory */
  Startup_InitRam();

  /* Initialize the non-local C++ objects */
  Startup_InitCtors();

  /* Run the main application */
  Startup_RunApplication();
}

//-----------------------------------------------------------------------------------------
/// \brief  Startup_RunApplication function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
[[noreturn]] static void Startup_RunApplication(void)
{
  /* check the weak function */
  if((unsigned int) &main != 0)
  {
    /* Call the main function */
    main();
  }

  /* Catch unexpected exit from main or if main does not exist */
  for(;;) { ; }
}
