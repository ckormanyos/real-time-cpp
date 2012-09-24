#ifndef _MCAL_IRQ_2010_04_10_H_
  #define _MCAL_IRQ_2010_04_10_H_

  namespace mcal
  {
    namespace irq
    {
      inline void enable_all (void) { asm volatile ("sei"); }
      inline void disable_all(void) { asm volatile ("cli"); }
    }
  }

#endif // _MCAL_IRQ_2010_04_10_H_
