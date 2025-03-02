///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_2025_02_22_H
  #define MCAL_GPT_2025_02_22_H

  #include <chrono>
  #include <cstdint>

  #include <mcal/mcal_gpt_arm_sys_tick.h>

  // Forward declaration of the util::timer template class.
  namespace util
  {
    template<typename unsigned_tick_type>
    class timer;
  }

  namespace mcal
  {
    namespace gpt
    {
      namespace detail
      {
        constexpr inline auto timer1_max   () noexcept -> std::uint32_t { return UINT32_C(80000000); }
        constexpr inline auto timer1_reload() noexcept -> std::uint32_t { return timer1_max() - UINT32_C(1); }
      }

      using detail::timer1_max;
      using detail::timer1_reload;

      using config_type = void;
      using value_type  = std::uint64_t;

      auto init(const config_type*) -> void;

      struct secure final
      {
        static auto get_time_elapsed() -> value_type;

        friend auto std::chrono::high_resolution_clock::now() noexcept -> std::chrono::high_resolution_clock::time_point;

        template<typename unsigned_tick_type>
        friend class util::timer;
      };
    }
  }

#endif // MCAL_GPT_2011_10_20_H
