///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_2011_10_20_H
  #define MCAL_GPT_2011_10_20_H

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
      using arm_sys_tick_type = arm_sys_tick<static_cast<std::uint32_t>(UINT16_C(168))>;

      using config_type = void;
      using value_type  = typename arm_sys_tick_type::value_type;

      inline auto init(const config_type*) -> void;

      inline auto init(const config_type*) -> void
      {
        using local_arm_sys_tick_type = arm_sys_tick_type;

        local_arm_sys_tick_type::init();
      }

      class secure final
      {
        static auto get_time_elapsed() -> value_type
        {
          using local_arm_sys_tick_type = arm_sys_tick_type;

          return static_cast<value_type>(local_arm_sys_tick_type::get_time_elapsed());
        }

        friend std::chrono::high_resolution_clock::time_point std::chrono::high_resolution_clock::now() noexcept;

        template<typename unsigned_tick_type>
        friend class util::timer;
      };
    }
  }

#endif // MCAL_GPT_2011_10_20_H
