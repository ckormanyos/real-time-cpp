///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

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

#include<stdint.h>

//=========================================================================================
// Function prototype
//=========================================================================================
void Startup_Init(void);
static void Startup_InitRam(void);
static void Startup_InitCtors(void);
static void Startup_RunApplication(void);
static void Startup_Unexpected_Exit(void);
static void Startup_InitMcuSystem(void);

//=========================================================================================
// Extern function prototype
//=========================================================================================
extern int main_x(void) __attribute__((used,noinline));

//-----------------------------------------------------------------------------------------
/// \brief  Startup_Init function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void Startup_Init(void)
{
  /* Initialize the MCU system */
  Startup_InitMcuSystem();

  /* Initialize the RAM memory */
  Startup_InitRam();

  /* Initialize the non-local C++ objects */
  Startup_InitCtors();

  /* Run the main application */
  Startup_RunApplication();
}

//-----------------------------------------------------------------------------------------
/// \brief  Startup_InitRam function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
static void Startup_InitRam(void)
{
  // Use my own standard static RAM initialization.

  extern void crt_init_ram(void);

  crt_init_ram();
}

//-----------------------------------------------------------------------------------------
/// \brief Startup_InitCtors function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
static void Startup_InitCtors(void)
{
  // Use my own standard static constructor initialization.

  extern void crt_init_ctors();

  crt_init_ctors();
}

//-----------------------------------------------------------------------------------------
/// \brief  Startup_RunApplication function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
static void Startup_RunApplication(void)
{
  /* check the weak function */
  if((unsigned int) &main_x != 0)
  {
#ifdef HP_CORES_SMP_MODE
     // note: RISC-V has no WFE/SEV instructions to synchronize SMP system
     //       so I am using CLINT to synchronize both HP cores on ESP32-P4

     // Notify core1 that the setup of the runtime environment is done
     // by setting the SW interrupt pending bit in CLINT on core1.

    *(volatile uint32_t*)0x20010000 = 1;
#endif

    // Call the main function.
    main_x();
  }

  // Catch unexpected exit from main or if main does not exist.
  Startup_Unexpected_Exit();
}

//-----------------------------------------------------------------------------------------
/// \brief  Startup_Unexpected_Exit function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
static void Startup_Unexpected_Exit(void)
{
  for(;;);
}

//-----------------------------------------------------------------------------------------
/// \brief  Startup_InitMcuSystem function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
static void Startup_InitMcuSystem(void)
{
  // The system clock is set by the SBL.
}
