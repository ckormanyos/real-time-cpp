///////////////////////////////////////////////////////////////////
//                                                               //
//  Copyright Christopher Kormanyos 2023 - 2026.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
//                                                               //
///////////////////////////////////////////////////////////////////

#include <mcal_lcd.h>
#include <util/utility/util_baselexical_cast.h>

#include <array>
#include <cstddef>
#include <cstdint>

extern auto pi_count_of_calculations() -> std::uint32_t;

namespace local
{
  auto write_progress_value(const std::uint32_t value, const std::size_t line) -> void;

  auto write_progress_value(const std::uint32_t value, const std::size_t line) -> void
  {
    std::array<char, 16U> buffer { };

    const auto* const p_end { util::baselexical_cast(value, buffer.data(), buffer.data() + buffer.size()) };

    mcal::lcd::write_line(buffer.data(), static_cast<std::size_t>(p_end - buffer.data()), line);
  }
} // namespace local

auto pi_lcd_progress(const std::uint32_t pi_output_digits10) -> void;

auto pi_lcd_progress(const std::uint32_t pi_output_digits10) -> void
{
  local::write_progress_value(pi_output_digits10, std::size_t { UINT8_C(0) });
  local::write_progress_value(pi_count_of_calculations(), std::size_t { UINT8_C(1) });
}
