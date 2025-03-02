///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
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
// Date        : 04.09.2024
// 
// Description : C/C++ Runtime Setup (Crt0)
// 
// ***************************************************************************************

#include <mcal_cpu.h>

#include <cstdint>

extern "C" {

//=========================================================================================
// types definitions
//=========================================================================================

typedef struct
{
  unsigned long  sourceAddr;  /* Source Address (section in ROM memory) */
  unsigned long  targetAddr;  /* Target Address (section in RAM memory) */
  unsigned long  size;        /* length of section (bytes) */
}
runtimeCopyTable_t;

typedef struct
{
  unsigned long  Addr;  /* source Address (section in RAM memory) */
  unsigned long  size;  /* length of section (bytes) */
}
runtimeClearTable_t;

//=========================================================================================
// linker variables
//=========================================================================================
extern const runtimeCopyTable_t  __RUNTIME_COPY_TABLE [];
extern const runtimeClearTable_t __RUNTIME_CLEAR_TABLE[];

extern unsigned long __CPPCTOR_LIST__[];

//=========================================================================================
// defines
//=========================================================================================
#define __STARTUP_RUNTIME_COPYTABLE   (runtimeCopyTable_t*)(&__RUNTIME_COPY_TABLE[0])
#define __STARTUP_RUNTIME_CLEARTABLE  (runtimeClearTable_t*)(&__RUNTIME_CLEAR_TABLE[0])
#define __STARTUP_RUNTIME_CTORS       (unsigned long*)(&__CPPCTOR_LIST__[0])

//=========================================================================================
// function prototype
//=========================================================================================
void Startup_Init() __attribute__((used));

static void Startup_InitRam();
static void Startup_InitCtors();

//=========================================================================================
// extern function prototype
//=========================================================================================
int main() __attribute__((weak));
void Mcu_ClockInit() __attribute__((weak));
void Mcu_InitCore() __attribute__((weak));

//=========================================================================================
// macros
//=========================================================================================

//-----------------------------------------------------------------------------------------
/// \brief  Startup_Init function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void Startup_Init()
{
  mcal::cpu::init();

  // Initialize the RAM memory.
  Startup_InitRam();

  // Initialize the non-local C++ objects.
  Startup_InitCtors();

  // Start the application.

  // Check the weak function.
  if((unsigned int) main != 0)
  {
    // Call the main function.

    static_cast<void>(main());
  }

  // Catch unexpected exit from main or if main does not exist.
  for(;;)
  {
    ;
  }
}

static void Startup_InitRam()
{
  unsigned long ClearTableIdx = 0;

  /* Clear Table */

  while((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].Addr != (unsigned long)-1 && (__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].size != (unsigned long)-1)
  {
    for(unsigned int cpt = 0; cpt < (__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].size; cpt++)
    {
      *(volatile unsigned char*)((unsigned long)((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].Addr) + cpt) = 0;
    }

    ClearTableIdx++;
  }

  /* Copy Table (ESP32-S3 does not need to intialize it as we get copied to SRAM by the bootROM) */
  #if 0
  unsigned long CopyTableIdx  = 0;

  while((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size       != (unsigned long)-1
       )
  {
    for(unsigned int cpt = 0; cpt < (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size; cpt++)
    {
      *(volatile unsigned char*)((unsigned long)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr) + cpt) = 
               *(volatile const unsigned char*)((unsigned long)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr) + cpt);
    }

    CopyTableIdx++;
  }
  #endif
}

static void Startup_InitCtors()
{
  unsigned long CtorIdx = 0U;

  while((__STARTUP_RUNTIME_CTORS)[CtorIdx] != ((unsigned long)-1))
  {
    ((void (*)())((__STARTUP_RUNTIME_CTORS)[CtorIdx++]))();
  }
}

} // extern "C"
