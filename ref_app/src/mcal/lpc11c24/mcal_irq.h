///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_IRQ_2010_04_10_H_
  #define MCAL_IRQ_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace irq
    {
      typedef void config_type;
      void init(const config_type*);
      void set_handler_priority(const std::int32_t irq, const std::uint32_t priority);

      inline void enable_all () { asm volatile("cpsie i"); }
      inline void disable_all() { asm volatile("cpsid i"); }

      // Number of Bits NVIC uses for Priority Levels
      constexpr std::uint32_t nvic_priority_bits = UINT32_C(2); 

      // Core Interrupts
      constexpr std::int32_t systick_irqn = INT32_C(-1);

      // Peripheral Interrupts
      constexpr std::uint32_t wdt_irqn = UINT32_C(25);
      constexpr std::uint32_t ccan_irqn = UINT32_C(25);
    }
  }

#endif // MCAL_IRQ_2010_04_10_H_
