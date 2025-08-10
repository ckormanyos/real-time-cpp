///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_2011_10_20_H
  #define MCAL_GPT_2011_10_20_H

  #include <cstdint>

  namespace mcal
  {
    namespace gpt
    {
      typedef void          config_type;
      typedef std::uint64_t value_type;

      void init(const config_type*);

      struct secure final
      {
        static value_type get_time_elapsed();
      };

      constexpr std::uint32_t systick_ctrl_enable    = UINT32_C(1UL << 0);   // 32-bit register.  enable
      constexpr std::uint32_t systick_ctrl_tickint   = UINT32_C(1UL << 1);   // 32-bit register.  tickint
      constexpr std::uint32_t systick_ctrl_clksource = UINT32_C(1UL << 2);   // 32-bit register.  clksource
    }
  }

#endif // MCAL_GPT_2011_10_20_H
