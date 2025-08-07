///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2010_04_10_H
  #define MCAL_IRQ_2010_04_10_H

  #include <core_macros.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  static inline void mcal_irq_enable_all(void);
  static inline void mcal_irq_disable_all(void);

  #if defined(__cplusplus)
  }
  #endif

  #if defined(__cplusplus)
  namespace mcal
  {
    namespace irq
    {
      using config_type = void;

      void init(const config_type*);

      inline void enable_all() { ::mcal_irq_enable_all(); }
      inline void disable_all() { ::mcal_irq_disable_all(); }
    }
  }
  #endif

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  static inline void mcal_irq_enable_all(void) { arch_enable_ints(); arch_enable_fiqs(); }
  static inline void mcal_irq_disable_all(void) { arch_disable_fiqs(); arch_disable_ints(); }

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_IRQ_2010_04_10_H
