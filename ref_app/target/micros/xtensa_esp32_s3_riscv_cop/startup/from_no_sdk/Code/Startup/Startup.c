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

#include <stddef.h>
#include <stdint.h>

//=========================================================================================
// types definitions
//=========================================================================================
typedef struct
{
  unsigned long  sourceAddr;  /* Source Address (section in ROM memory) */
  unsigned long  targetAddr;  /* Target Address (section in RAM memory) */
  unsigned long  size;        /* length of section (bytes) */
} runtimeCopyTable_t;

typedef struct
{
  unsigned long  Addr;  /* source Address (section in RAM memory) */
  unsigned long  size;  /* length of section (bytes) */
} runtimeClearTable_t;

//=========================================================================================
// linker variables
//=========================================================================================
extern const runtimeCopyTable_t __RUNTIME_COPY_TABLE[];
extern const runtimeClearTable_t __RUNTIME_CLEAR_TABLE[];
extern unsigned long __CPPCTOR_LIST__[];

//=========================================================================================
// defines
//=========================================================================================
#define __STARTUP_RUNTIME_COPYTABLE   (runtimeCopyTable_t*)(&__RUNTIME_COPY_TABLE[0])
#define __STARTUP_RUNTIME_CLEARTABLE  (runtimeClearTable_t*)(&__RUNTIME_CLEAR_TABLE[0])
#define __STARTUP_RUNTIME_CTORS       (unsigned long*)(&__CPPCTOR_LIST__[0])

//=========================================================================================
// function prototypes
//=========================================================================================
void Startup_Init(void) __attribute__((used));
static void Startup_InitRam(void);
static void Startup_InitCtors(void);

extern void main(void);

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
void Startup_Init(void)
{
  /* Initialize the RAM memory */
  Startup_InitRam();

  /* Initialize the non-local C++ objects */
  Startup_InitCtors();

  /* Start the application */
  main();

  /* Catch unexpected exit from main or if main does not exist */
  for(;;) { ; }
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
  unsigned long ClearTableIdx = 0;
  //unsigned long CopyTableIdx  = 0;

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
  while((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size       != (unsigned long)-1
       )
  {
    for(unsigned int cpt = 0; cpt < (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size; cpt++)
    {
      *(volatile unsigned char*)((unsigned long)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr) + cpt) = 
               *(volatile unsigned char*)((unsigned long)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr) + cpt);
    }

    CopyTableIdx++;
  }
#endif
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
  unsigned long CtorIdx = 0U;
  
  while((__STARTUP_RUNTIME_CTORS)[CtorIdx] != ((unsigned long)-1))
  {
    ((void (*)(void))((__STARTUP_RUNTIME_CTORS)[CtorIdx++]))();
  }
}
