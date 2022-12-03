///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_ARM_SYS_TICK_2022_11_30_H_
  #define MCAL_GPT_ARM_SYS_TICK_2022_11_30_H_

  #include <cstdint>

  #include <mcal_reg.h>

  extern "C" auto __sys_tick_handler(void) noexcept -> void
  #if defined(__GNUC__)
  __attribute__((used, noinline))
  #endif
  ;

  namespace mcal { namespace gpt {

  template<const std::uint32_t SysTickMHz,
           typename ValueType         = std::uint64_t,
           typename TimerAddressType  = std::uint32_t,
           typename TimerRegisterType = std::uint32_t>
  class arm_sys_tick
  {
  private:
    using timer_address_type  = TimerAddressType;
    using timer_register_type = TimerRegisterType;
    using value_type          = ValueType;

    static constexpr auto sys_tick_mhz = SysTickMHz;

    static constexpr auto scs_base        = static_cast<timer_address_type>(UINT32_C(0xE000E000));
    static constexpr auto sys_tick_base   = static_cast<timer_address_type>(scs_base        + static_cast<timer_address_type>(UINT8_C(0x10)));
    static constexpr auto sys_tick_ctrl   = static_cast<timer_address_type>(sys_tick_base   + static_cast<timer_address_type>(UINT8_C(0x00)));
    static constexpr auto sys_tick_load   = static_cast<timer_address_type>(sys_tick_base   + static_cast<timer_address_type>(UINT8_C(0x04)));
    static constexpr auto sys_tick_val    = static_cast<timer_address_type>(sys_tick_base   + static_cast<timer_address_type>(UINT8_C(0x08)));
    static constexpr auto sys_tick_cal    = static_cast<timer_address_type>(sys_tick_base   + static_cast<timer_address_type>(UINT8_C(0x0C)));

  public:
    static auto init() noexcept -> void
    {
      if(!my_is_init)
      {
        // Set up an interrupt on ARM(R) sys tick.

        mcal::reg::reg_access_static<timer_address_type, timer_register_type, sys_tick_ctrl, static_cast<timer_register_type>(UINT8_C(0))>::reg_set();

        // Set sys tick reload register.
        mcal::reg::reg_access_static<timer_address_type, timer_register_type, sys_tick_load, static_cast<timer_register_type>(UINT32_C(0x00FFFFFF))>::reg_set();

        // Initialize sys tick counter value.
        mcal::reg::reg_access_static<timer_address_type, timer_register_type, sys_tick_val,  static_cast<timer_register_type>(UINT8_C(0))>::reg_set();

        // Set sys tick clock source to ahb.
        mcal::reg::reg_access_static<timer_address_type, timer_register_type, sys_tick_ctrl, static_cast<timer_register_type>(UINT8_C(4))>::reg_or();

        // Enable sys tick interrupt.
        mcal::reg::reg_access_static<timer_address_type, timer_register_type, sys_tick_ctrl, static_cast<timer_register_type>(UINT8_C(2))>::reg_or();

        // Enable sys tick timer.
        mcal::reg::reg_access_static<timer_address_type, timer_register_type, sys_tick_ctrl, static_cast<timer_register_type>(UINT8_C(1))>::reg_or();

        my_is_init = true;
      }
    }

    static auto get_time_elapsed() noexcept -> value_type
    {
      if(my_is_init)
      {
        // Return the system tick using a multiple read to ensure data consistency.

        // Do the first read of the sys tick counter and the system tick.
        // Handle reverse counting for sys tick counting down.
        const auto sys_tick_val_1 =
          static_cast<timer_register_type>
          (
            static_cast<timer_register_type>
            (
                static_cast<timer_register_type>(UINT32_C(0x00FFFFFF))
              - mcal::reg::reg_access_static<timer_address_type,
                                             timer_register_type,
                                             sys_tick_val>::reg_get()
            )
          );

        const auto system_tick_gpt = my_system_tick;

        // Do the second read of the sys tick counter.
        // Handle reverse counting for sys tick counting down.
        const auto sys_tick_val_2 =
          static_cast<timer_register_type>
          (
            static_cast<timer_register_type>
            (
                static_cast<timer_register_type>(UINT32_C(0x00FFFFFF))
              - mcal::reg::reg_access_static<timer_address_type,
                                             timer_register_type,
                                             sys_tick_val>::reg_get()
            )
          );

        // Perform the consistency check.
        const auto tick_is_consistent = (sys_tick_val_2 >= sys_tick_val_1);

        const auto consistent_tick_value =
          static_cast<std::uint64_t>
          (
            (tick_is_consistent ? static_cast<std::uint64_t>(system_tick_gpt | sys_tick_val_1)
                                : static_cast<std::uint64_t>(my_system_tick  | sys_tick_val_2))
          );

        // Perform scaling and include a rounding correction.
        return
          static_cast<value_type>
          (
              static_cast<std::uint64_t>
              (
                consistent_tick_value + static_cast<std::uint32_t>(sys_tick_mhz / 2U)
              )
            / sys_tick_mhz
          );
      }
      else
      {
        return static_cast<value_type>(UINT8_C(0));
      }
    }

  private:
    static volatile value_type my_system_tick;
    static          bool       my_is_init;

    friend auto ::__sys_tick_handler(void) noexcept -> void;
  };

  template<const std::uint32_t SysTickMHz, typename ValueType, typename TimerAddressType, typename TimerRegisterType> bool              arm_sys_tick<SysTickMHz, ValueType, TimerAddressType, TimerRegisterType>::my_is_init;
  template<const std::uint32_t SysTickMHz, typename ValueType, typename TimerAddressType, typename TimerRegisterType> volatile typename arm_sys_tick<SysTickMHz, ValueType, TimerAddressType, TimerRegisterType>::value_type arm_sys_tick<SysTickMHz, ValueType, TimerAddressType, TimerRegisterType>::my_system_tick;

  } }

#endif // MCAL_GPT_ARM_SYS_TICK_2022_11_30_H_
