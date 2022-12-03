///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_2011_10_20_H_
  #define MCAL_GPT_2011_10_20_H_

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
      using arm_sys_tick_type =
        arm_sys_tick<static_cast<std::uint32_t>(UINT32_C(280)), std::uint64_t>;

      using config_type = void;
      using value_type  = typename arm_sys_tick_type::value_type;

      void init(const config_type*);

      class secure final
      {
        static value_type get_time_elapsed();

        friend std::chrono::high_resolution_clock::time_point std::chrono::high_resolution_clock::now() noexcept;

        template<typename unsigned_tick_type>
        friend class util::timer;
      };
    }
  }

#endif // MCAL_GPT_2011_10_20_H_
