///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from (but strongly modified from):
/******************************************************************************************
  Filename    : main.c

  Core        : RISC-V

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.02.2025

  Description : Application main function for ULP-RISC-V Co-processor

******************************************************************************************/

#include <mcal_gpt.h>
#include <mcal_port.h>
#include <mcal_pwm/mcal_pwm_port.h>

#include <util/utility/util_attribute.h>

#include <array>

auto main() -> int ATTRIBUTE(used);

namespace
{
  using pwm_port_type = mcal::port::port_pin<UINT32_C(17)>;

  using pwm_type = mcal::pwm::pwm_port<pwm_port_type, mcal::pwm::pwm_base::duty_type { UINT16_C(256) }>;

  using duty_type = typename pwm_type::duty_type;

  pwm_type my_pwm { };

  using duty_array_type = std::array<duty_type, std::size_t { UINT8_C(64) }>;

  constexpr duty_array_type
    duty_table
    {
        1U,   2U,   3U,   4U,   5U,   6U,   7U,   8U,
        9U,  10U,  11U,  12U,  13U,  14U,  15U,  16U,
       17U,  18U,  19U,  20U,  21U,  22U,  23U,  24U,
       25U,  26U,  27U,  28U,  29U,  30U,  31U,  32U,
       33U,  34U,  36U,  38U,  40U,  42U,  44U,  46U,
       48U,  50U,  52U,  54U,  56U,  58U,  60U,  62U,
       64U,  68U,  72U,  76U,  80U,  84U,  88U,  96U,
      112U, 128U, 144U, 160U, 176U, 192U, 224U, 256U
    };

  static_assert
  (
    duty_table.back() <= pwm_type::get_resolution(),
    "Error: Max PWM duty cycle can not exceed the PWM resolution"
  );
}

auto main() -> int
{
  mcal::gpt::init(nullptr);

  static_cast<void>(my_pwm.init());

  unsigned prescaler { UINT8_C(0) };

  for(;;)
  {
    const unsigned
      duty_index
      {
        unsigned { prescaler % static_cast<unsigned>(std::tuple_size<duty_array_type>::value) }
      };

    my_pwm.set_duty(duty_table[duty_index]);

    // Table[Prime[n], {n, 1900, 1905, 1}]
    // {16381, 16411, 16417, 16421, 16427, 16433}

    for(unsigned srv_idx { UINT8_C(0) }; srv_idx < unsigned { UINT16_C(16'411) }; ++srv_idx)
    {
      my_pwm.service();
    }

    ++prescaler;
  }
}
