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
//=========================================================================================
// Types definitions
//=========================================================================================
typedef struct
{
  unsigned long  sourceAddr;  /* Source Address (section in ROM memory) */
  unsigned long  targetAddr;  /* Target Address (section in RAM memory) */
  unsigned long  size;        /* length of section (bytes)              */
} runtimeCopyTable_t;

typedef struct
{
  unsigned long  addr;  /* Source Address (section in RAM memory) */
  unsigned long  size;  /* Length of section (bytes)              */
} runtimeClearTable_t;

//=========================================================================================
// Linker variables
//=========================================================================================
extern const runtimeCopyTable_t __RUNTIME_COPY_TABLE[];
extern const runtimeClearTable_t __RUNTIME_CLEAR_TABLE[];
extern unsigned long __CTOR_LIST__[];

//=========================================================================================
// Defines
//=========================================================================================
#define __STARTUP_RUNTIME_COPYTABLE   (runtimeCopyTable_t*)(&__RUNTIME_COPY_TABLE[0])
#define __STARTUP_RUNTIME_CLEARTABLE  (runtimeClearTable_t*)(&__RUNTIME_CLEAR_TABLE[0])
#define __STARTUP_RUNTIME_CTORS       (unsigned long*)(&__CTOR_LIST__[0])

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
int main(void) __attribute__((weak));
void Mcu_HwInitialization(void) __attribute__((weak));

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
  unsigned long ClearTableIdx = 0;
  unsigned long CopyTableIdx  = 0;

  /* Clear Table */
  while((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].addr != (unsigned long)-1 && (__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].size != (unsigned long)-1)
  {
    for(unsigned long idx = 0; idx < ((unsigned long)((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].size) / 4); idx++)
    {
     ((unsigned long*)((__STARTUP_RUNTIME_CLEARTABLE)[ClearTableIdx].addr))[idx] = 0;
    }

    ClearTableIdx++;
  }

  /* Copy Table */
  while((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr != (unsigned long)-1 &&
        (__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size       != (unsigned long)-1
       )
  {
    for(unsigned long idx = 0; idx < ((unsigned long)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].size) / 4); idx++)
    {
     ((unsigned long*)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].targetAddr))[idx] = 
     ((unsigned long*)((__STARTUP_RUNTIME_COPYTABLE)[CopyTableIdx].sourceAddr))[idx];
    }

    CopyTableIdx++;
  }
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
  if((unsigned int) &main != 0)
  {
    /* Call the main function */
    main();
  }

  /* Catch unexpected exit from main or if main does not exist */
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
  if(0 != (unsigned long) &Mcu_HwInitialization)
  {
    Mcu_HwInitialization();
  }
}