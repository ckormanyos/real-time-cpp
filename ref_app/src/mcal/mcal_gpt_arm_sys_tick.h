///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_ARM_SYS_TICK_2022_11_30_H
  #define MCAL_GPT_ARM_SYS_TICK_2022_11_30_H

  #include <cstdint>
  #include <limits>

  #if defined(__GNUC__)
  extern "C" auto __sys_tick_handler(void) noexcept -> void __attribute__((used, noinline));
  #endif

  namespace mcal { namespace gpt {

  template<const std::uint32_t SysTickMHz,
           typename ValueType,
           typename RegisterAddressType,
           typename RegisterValueType>
  class arm_sys_tick_base
  {
  protected:
    using register_address_type = RegisterAddressType;
    using register_value_type   = RegisterValueType;
    using value_type            = ValueType;

    static constexpr auto scs_base      = static_cast<register_address_type>(UINT32_C(0xE000E000));
    static constexpr auto sys_tick_mhz  = SysTickMHz;
    static constexpr auto sys_tick_base = static_cast<register_address_type>(scs_base        + static_cast<register_address_type>(UINT8_C(0x10)));
    static constexpr auto sys_tick_ctrl = static_cast<register_address_type>(sys_tick_base   + static_cast<register_address_type>(UINT8_C(0x00)));
    static constexpr auto sys_tick_load = static_cast<register_address_type>(sys_tick_base   + static_cast<register_address_type>(UINT8_C(0x04)));
    static constexpr auto sys_tick_val  = static_cast<register_address_type>(sys_tick_base   + static_cast<register_address_type>(UINT8_C(0x08)));
    static constexpr auto sys_tick_cal  = static_cast<register_address_type>(sys_tick_base   + static_cast<register_address_type>(UINT8_C(0x0C)));

    template<const register_address_type address,
             const register_value_type value = static_cast<register_value_type>(0)>
    struct reg_access_static
    {
      static register_value_type
                  reg_get() { volatile register_value_type* pa = reinterpret_cast<register_value_type*>(address); return *pa; }

      static void reg_set() { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa =       value; }

      static void reg_or () { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa | value; }
    };
  };

  template<const std::uint32_t SysTickMHz,
           typename ValueType = std::uint64_t>
  class arm_sys_tick : private arm_sys_tick_base<SysTickMHz, ValueType, std::uint32_t, std::uint32_t>
  {
  private:
    using base_class_type = arm_sys_tick_base<SysTickMHz, ValueType, std::uint32_t, std::uint32_t>;

    using register_address_type = typename base_class_type::register_address_type;
    using register_value_type   = typename base_class_type::register_value_type;

    static_assert(std::numeric_limits<register_address_type>::digits == 32,
                  "Error: Wrong width of register address type");

    static_assert(std::numeric_limits<register_value_type>::digits == 32,
                  "Error: Wrong width of register value type");

  public:
    using value_type = typename base_class_type::value_type;

    static auto init() noexcept -> void
    {
      if(!my_is_init)
      {
        my_is_init = true;

        // Set up an interrupt on the ARM(R) sys-tick.

        base_class_type::template reg_access_static<base_class_type::sys_tick_ctrl, static_cast<register_value_type>(UINT8_C(0))>::reg_set();

        // Set the sys-tick reload register.
        base_class_type::template reg_access_static<base_class_type::sys_tick_load, static_cast<register_value_type>(UINT32_C(0x00FFFFFF))>::reg_set();

        // Initialize the sys-tick counter value.
        base_class_type::template reg_access_static<base_class_type::sys_tick_val,  static_cast<register_value_type>(UINT8_C(0))>::reg_set();

        // Set the sys-tick clock source to be the processor clock.
        base_class_type::template reg_access_static<base_class_type::sys_tick_ctrl, static_cast<register_value_type>(UINT8_C(4))>::reg_or();

        // Enable the sys-tick interrupt.
        base_class_type::template reg_access_static<base_class_type::sys_tick_ctrl, static_cast<register_value_type>(UINT8_C(2))>::reg_or();

        // Enable the sys-tick timer.
        base_class_type::template reg_access_static<base_class_type::sys_tick_ctrl, static_cast<register_value_type>(UINT8_C(1))>::reg_or();
      }
    }

    static auto get_time_elapsed() noexcept -> value_type
    {
      return
        static_cast<value_type>
        (
          my_is_init ? get_consistent_microsecond_tick() : static_cast<value_type>(UINT8_C(0))
        );
    }

  private:
    static volatile value_type my_sys_tick_value;
    static          bool       my_is_init;

    static auto get_consistent_microsecond_tick() noexcept -> value_type
    {
      // Return the system tick using a multiple read to ensure data consistency.

      // Do the first read of the sys-tick counter and the sys-tick
      // value. Handle reverse counting for sys-tick counter, which is
      // counting down.

      const auto sys_tick_counter_1 =
        static_cast<register_value_type>
        (
          static_cast<register_value_type>
          (
              static_cast<register_value_type>(UINT32_C(0x00FFFFFF))
            - static_cast<register_value_type>(base_class_type::template reg_access_static<base_class_type::sys_tick_val>::reg_get())
          )
        );

      const auto sys_tick_value = my_sys_tick_value;

      // Do the second read of the sys-tick counter and the sys-tick
      // value. Handle reverse counting for sys-tick counter, which is
      // counting down.

      const auto sys_tick_counter_2 =
        static_cast<register_value_type>
        (
          static_cast<register_value_type>
          (
              static_cast<register_value_type>(UINT32_C(0x00FFFFFF))
            - static_cast<register_value_type>(base_class_type::template reg_access_static<base_class_type::sys_tick_val>::reg_get())
          )
        );

      // Perform the consistency check.

      const auto sys_tick_consistent_value =
        static_cast<std::uint64_t>
        (
          ((sys_tick_counter_2 >= sys_tick_counter_1)
            ? static_cast<std::uint64_t>(   sys_tick_value | sys_tick_counter_1)
            : static_cast<std::uint64_t>(my_sys_tick_value | sys_tick_counter_2))
        );

      // Perform scaling and include a rounding correction.
      return
        static_cast<value_type>
        (
            static_cast<std::uint64_t>
            (
                sys_tick_consistent_value
              + static_cast<std::uint32_t>(base_class_type::sys_tick_mhz / static_cast<std::uint32_t>(UINT8_C(2)))
            )
          / base_class_type::sys_tick_mhz
        );
    }

    #if defined(__GNUC__)
    friend auto ::__sys_tick_handler(void) noexcept -> void;
    #endif
  };

  template<const std::uint32_t SysTickMHz, typename ValueType>          bool                                                     arm_sys_tick<SysTickMHz, ValueType>::my_is_init;
  template<const std::uint32_t SysTickMHz, typename ValueType> volatile typename arm_sys_tick<SysTickMHz, ValueType>::value_type arm_sys_tick<SysTickMHz, ValueType>::my_sys_tick_value;

  } }

#endif // MCAL_GPT_ARM_SYS_TICK_2022_11_30_H
