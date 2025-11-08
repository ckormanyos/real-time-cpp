///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_BASE_2020_06_10_H // NOLINT(llvm-header-guard)
  #define MCAL_LCD_BASE_2020_06_10_H

  #include <util/utility/util_noncopyable.h>

  #include <cstddef>
  #include <cstdint>

  #if(__cplusplus >= 201703L)
  namespace mcal::lcd {
  #else
  namespace mcal { namespace lcd { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  class lcd_base : private util::noncopyable // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    virtual ~lcd_base() = default;

    virtual auto init() -> bool = 0;

    virtual auto write(const char* pstr,
                       const std::size_t length,
                       const std::uint_fast8_t line_index) -> bool = 0;

  protected:
    lcd_base() = default; // LCOV_EXCL_LINE

    virtual auto set_line_index(const std::uint8_t index) -> bool { static_cast<void>(index); return true; } // LCOV_EXCL_LINE
  };

  #if(__cplusplus >= 201703L)
  } // namespace mcal::lcd
  #else
  } // namespace lcd
  } // namespace mcal
  #endif

#endif // MCAL_LCD_BASE_2020_06_10_H
