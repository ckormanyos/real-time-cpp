#ifndef _MCAL_CPU_2009_02_14_H_
  #define _MCAL_CPU_2009_02_14_H_

  namespace mcal
  {
    namespace cpu
    {
      inline void nop() { asm volatile("nop"); }
      void init();
    }
  }

#endif // _MCAL_CPU_2009_02_14_H_
