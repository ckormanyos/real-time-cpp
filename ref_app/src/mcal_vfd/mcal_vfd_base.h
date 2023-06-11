///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_VFD_BASE_2023_06_08_H
  #define MCAL_VFD_BASE_2023_06_08_H

  #include <cstddef>
  #include <cstdint>

  #include <util/utility/util_display.h>

  namespace mcal { namespace vfd {

  template<const unsigned NumberOfLines,
           const unsigned NumberOfColumns>
  class vacuum_fluorescent_display_base : public ::util::display_multiline_base
  {
  public:
    static constexpr unsigned number_of_lines   = NumberOfLines;
    static constexpr unsigned number_of_columns = NumberOfColumns;

    vacuum_fluorescent_display_base(const vacuum_fluorescent_display_base&) = delete;
    vacuum_fluorescent_display_base(vacuum_fluorescent_display_base&&) noexcept = delete;

    virtual ~vacuum_fluorescent_display_base() = default;

    auto operator=(const vacuum_fluorescent_display_base&) -> vacuum_fluorescent_display_base& = delete;
    auto operator=(vacuum_fluorescent_display_base&&) noexcept -> vacuum_fluorescent_display_base& = delete;

    virtual auto init() noexcept -> bool = 0;

    virtual auto write(const char* pstr,
                       const std::uint_fast8_t length,
                       const std::uint_fast8_t line_index) -> bool = 0;

    virtual auto clear_line(const unsigned line_number) noexcept -> bool = 0;

    virtual auto set_line_index(const std::uint8_t) noexcept -> bool = 0;

  protected:
    vacuum_fluorescent_display_base() = default;
  };

  } } // namespace mcal::vfd

#endif // MCAL_VFD_BASE_2023_06_08_H
