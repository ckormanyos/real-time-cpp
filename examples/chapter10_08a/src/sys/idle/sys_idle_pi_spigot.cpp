///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstdint>

#include <math/constants/pi_digits_100th_pi_digits.h>
#include <math/constants/pi_digits_hash_sha1_control.h>
#include <math/constants/pi_spigot_state.h>
#include <mcal_lcd.h>
#include <mcal_memory/mcal_memory_sram_array.h>
#include <mcal_pwm.h>
#include <sys/idle/sys_idle_pi_spigot.h>
#include <util/utility/util_baselexical_cast.h>

namespace
{
  using sys_idle_pi_spigot_pi_spigot_type   = math::constants::pi_spigot_state<1001U, 9U>;

  constexpr mcal_sram_uintptr_t               sys_idle_pi_spigot_input_start_address = UINT32_C(0x00000000);

  constexpr mcal_sram_uintptr_t               sys_idle_pi_spigot_value_start_address =    sys_idle_pi_spigot_input_start_address
                                                                                       + (sys_idle_pi_spigot_pi_spigot_type::get_input_static_size() * sizeof(std::uint32_t));

  using sys_idle_pi_spigot_input_type       = mcal::memory::sram::array<std::uint32_t,
                                                                        sys_idle_pi_spigot_pi_spigot_type::get_input_static_size(),
                                                                        sys_idle_pi_spigot_input_start_address>;

  using sys_idle_pi_spigot_value_type       = mcal::memory::sram::array<std::uint8_t,
                                                                        sys_idle_pi_spigot_pi_spigot_type::get_output_static_size(),
                                                                        sys_idle_pi_spigot_value_start_address>;

  sys_idle_pi_spigot_input_type               sys_idle_pi_spigot_input;
  sys_idle_pi_spigot_value_type               sys_idle_pi_spigot_value;

  sys_idle_pi_spigot_pi_spigot_type           sys_idle_pi_spigot_object;

  mcal_sram_uintptr_t                         sys_idle_pi_spigot_pi_digits;
  mcal_sram_uintptr_t                         sys_idle_pi_spigot_pi_digits_100th_pi_digits_counter;

  using sys_idle_pi_spigot_hash_type        = math::constants::pi_digits_hash_control_base::native_hash_type;

  using sys_idle_pi_spigot_hash_result_type = typename sys_idle_pi_spigot_hash_type::result_type;

  sys_idle_pi_spigot_hash_type                sys_idle_pi_spigot_hash;

  std::uint8_t                                sys_idle_pi_spigot_pi_digits_hash_message_chars[sys_idle_pi_spigot_pi_spigot_type::loop_digit];

  bool                                        sys_idle_pi_spigot_pi_digits_result_is_ok = true;

  std::uint32_t                               sys_idle_pi_spigot_rounds_counter;
}

bool sys::idle::pi_spigot_get_result() noexcept
{
  return sys_idle_pi_spigot_pi_digits_result_is_ok;
}

void sys::idle::pi_spigot_run()
{
  if(sys_idle_pi_spigot_object.is_finished())
  {
    mcal::pwm::pwm0().set_duty(0U);

    char pstr_lcd_line1[10U];

    char* p_end = util::baselexical_cast(sys_idle_pi_spigot_rounds_counter, pstr_lcd_line1);

    mcal::lcd::lcd0().write_n(pstr_lcd_line1, std::uint_fast8_t(p_end - pstr_lcd_line1), 1U, false);

    sys_idle_pi_spigot_pi_digits = 0U;
    sys_idle_pi_spigot_pi_digits_100th_pi_digits_counter = 0U;

    *sys_idle_pi_spigot_input.data() = 0U;
    *sys_idle_pi_spigot_value.data() = 0U;

    sys_idle_pi_spigot_object.initialize();

    sys_idle_pi_spigot_hash.initialize();
  }

  // Calculate the pi spigot algorithm.
  sys_idle_pi_spigot_object.calculate(sys_idle_pi_spigot_input.data(),
                                      sys_idle_pi_spigot_value.data());

  mcal_sram_uintptr_t new_digit_count = 0U;

  // Process any new digits from the pi spigot algorithm.
  while(sys_idle_pi_spigot_pi_digits != sys_idle_pi_spigot_object.get_output_digit_count())
  {
    // Obtain the position of the next 100th digit of pi.
    const mcal_sram_uintptr_t pi_spigot_digits_100th_digit_position =
      mcal_sram_uintptr_t(sys_idle_pi_spigot_pi_digits_100th_pi_digits_counter * UINT32_C(100));

      const std::uint8_t next_digit_value =
        *(sys_idle_pi_spigot_value.cbegin() + mcal_sram_ptrdiff_t(sys_idle_pi_spigot_pi_digits));

    sys_idle_pi_spigot_pi_digits_hash_message_chars[new_digit_count] = next_digit_value + UINT8_C(0x30);

    ++new_digit_count;

    // Verify the next 100th digit of pi.
    if(sys_idle_pi_spigot_pi_digits == pi_spigot_digits_100th_digit_position)
    {
      const std::uint8_t next_100th_digit_cntrl =
        *(  math::constants::pi_digits_100th_pi_digits<mcal_progmem_uintptr_t(UINT32_C(1012))>::pi_digits_control()
          + mcal_progmem_ptrdiff_t(sys_idle_pi_spigot_pi_digits_100th_pi_digits_counter));

      ++sys_idle_pi_spigot_pi_digits_100th_pi_digits_counter;

      sys_idle_pi_spigot_pi_digits_result_is_ok &= (next_digit_value == next_100th_digit_cntrl);
    }

    ++sys_idle_pi_spigot_pi_digits;
  }

  if(new_digit_count != 0U)
  {
    // Set the PWM duty cycle which, in this case, is presented on the LCD.
    const std::uint16_t duty_cycle_value =
      static_cast<std::uint16_t>(  std::uint32_t(sys_idle_pi_spigot_pi_digits * UINT32_C(1000))
                                 / sys_idle_pi_spigot_object.get_output_static_size());

    mcal::pwm::pwm0().set_duty(duty_cycle_value);

    // Process the next digits of pi (bytes represented as chars) in the hash.
    sys_idle_pi_spigot_hash.process(sys_idle_pi_spigot_pi_digits_hash_message_chars, new_digit_count);

    // Check if the pi spigot calculation is finished.
    if(sys_idle_pi_spigot_object.is_finished())
    {
      ++sys_idle_pi_spigot_rounds_counter;

      sys_idle_pi_spigot_hash.finalize();

      sys_idle_pi_spigot_hash_result_type hash_result;

      sys_idle_pi_spigot_hash.get_result(hash_result.data());

      using local_hash_control_type =
        math::constants::pi_digits_hash_control<sys_idle_pi_spigot_pi_spigot_type::get_output_static_size()>;

      const bool hash_result_is_ok = std::equal(hash_result.cbegin(),
                                                hash_result.cend(),
                                                local_hash_control_type::hash_control());

      sys_idle_pi_spigot_pi_digits_result_is_ok &= hash_result_is_ok;
    }
  }
}
