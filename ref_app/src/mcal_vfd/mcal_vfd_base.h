///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023 - 2024.
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
    static constexpr auto number_of_rows() noexcept -> unsigned { return NumberOfLines; }
    static constexpr auto number_of_cols() noexcept -> unsigned { return NumberOfColumns; }

    ~vacuum_fluorescent_display_base() override = default;

  protected:
    vacuum_fluorescent_display_base() = default;
  };

  } } // namespace mcal::vfd

#endif // MCAL_VFD_BASE_2023_06_08_H
