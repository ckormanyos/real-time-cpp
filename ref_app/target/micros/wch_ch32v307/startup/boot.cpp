
asm (".align 4");
asm (".extern __STACK_TOP");
asm (".extern InterruptVectorTable");

extern "C"
{
  extern void Startup_Init(void);

  void __my_startup(void) __attribute__ ((section(".startup"), naked, no_reorder, optimize(0), used, noinline));
}

asm (".align 4");
extern "C" void __my_startup(void)
{
  /* setup the stack pointer */
  asm volatile("la sp, __STACK_TOP");

  /* setup the interrupt vector table */
  asm volatile("la x1, InterruptVectorTable");
  asm volatile("ori x1, x1, 3");
  asm volatile("csrw mtvec, x1");

  /* enable both the global interrupt flag and the FPU */
  asm volatile("li x1, 0x2008");
  asm volatile("csrw mstatus, x1");

  /* jump to the C runtime initialization */
  Startup_Init();
}
