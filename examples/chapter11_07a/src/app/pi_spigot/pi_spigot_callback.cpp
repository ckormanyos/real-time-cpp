///////////////////////////////////////////////////////////////////
//                                                               //
//  Copyright Christopher Kormanyos 2023 - 2025.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
//                                                               //
///////////////////////////////////////////////////////////////////

#include <mcal_lcd.h>
#include <util/utility/util_baselexical_cast.h>

#include <cstdint>

extern auto pi_count_of_calculations() -> std::uint32_t;

auto pi_lcd_progress(const std::uint32_t pi_output_digits10) -> void;

auto pi_lcd_progress(const std::uint32_t pi_output_digits10) -> void
{
  char p_str[std::size_t { UINT8_C(20) }];

  {
    std::fill(p_str, p_str + sizeof(p_str), char { INT8_C(0) });

    const char* p_end { util::baselexical_cast(pi_output_digits10, p_str, p_str + sizeof(p_str)) };

    mcal::lcd::write_line(p_str, static_cast<std::size_t>(p_end - p_str), std::size_t { UINT8_C(0) });
  }

  {
    std::fill(p_str, p_str + sizeof(p_str), char { INT8_C(0) });

    const char* p_end = util::baselexical_cast(pi_count_of_calculations(), p_str, p_str + sizeof(p_str));

    mcal::lcd::write_line(p_str, static_cast<std::size_t>(p_end - p_str), std::size_t { UINT8_C(1) });
  }
}
