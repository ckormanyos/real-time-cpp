///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_2022_12_16_H
  #define MCAL_GPT_2022_12_16_H

  #include <cstdint>

  namespace mcal
  {
    namespace gpt
    {
      using config_type = void;
      using value_type  = std::uint64_t;

      auto init(const config_type*) -> void;

      struct secure final
      {
        static auto get_time_elapsed() -> value_type;
        static auto get_time_elapsed_core1() -> value_type;
      };

      struct timer_core1_backend
      {
        using tick_type = std::uint64_t;

        static auto get_now() -> tick_type { return static_cast<tick_type>(mcal::gpt::secure::get_time_elapsed_core1()); }
      };
    }
  }

#endif // MCAL_GPT_2022_12_16_H
