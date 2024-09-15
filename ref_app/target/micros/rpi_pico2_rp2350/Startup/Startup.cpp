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

extern "C"
{
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

  extern const runtimeCopyTable_t __RUNTIME_COPY_TABLE[];
  extern const runtimeClearTable_t __RUNTIME_CLEAR_TABLE[];
  extern unsigned long __CPPCTOR_LIST__[];

  void __my_startup(void) __attribute__((used));

  extern int main(void);
  extern void RP2350_ClockInit(void) __attribute__((weak));
  extern void RP2350_InitCore (void) __attribute__((weak));
}

namespace crt
{
  auto init_ram  () -> void;
  auto init_ctors() -> void;
}

//=========================================================================================
// macros
//=========================================================================================
#define __STARTUP_RUNTIME_COPYTABLE   (runtimeCopyTable_t*)(&__RUNTIME_COPY_TABLE[0])
#define __STARTUP_RUNTIME_CLEARTABLE  (runtimeClearTable_t*)(&__RUNTIME_CLEAR_TABLE[0])
#define __STARTUP_RUNTIME_CTORS       (unsigned long*)(&__CPPCTOR_LIST__[0])

#define ENABLE_IRQ()  __asm("CPSIE i")
#define DISABLE_IRQ() __asm("CPSID i")

//-----------------------------------------------------------------------------------------
/// \brief  __my_startup function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void __my_startup(void)
{
  /* Initialize the CPU Core */
  RP2350_InitCore();

  /* Configure the system clock */
  RP2350_ClockInit();

  /* Initialize the RAM memory */
  crt::init_ram();

  /* Initialize the non-local C++ objects */
  crt::init_ctors();

  /* Start the application */
  // Jump to main on core 1 (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");
}
