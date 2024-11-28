///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_BUFFERED_INSTANCE_2024_02_07_H // NOLINT(llvm-header-guard)
  #define MCAL_LCD_BUFFERED_INSTANCE_2024_02_07_H

  #include <mcal_lcd/mcal_lcd_base.h>

  #include <algorithm>
  #include <array>

  #if(__cplusplus >= 201703L)
  namespace mcal::lcd {
  #else
  namespace mcal { namespace lcd { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<typename BackendDisplayType,
           const unsigned HeightInRows,
           const unsigned WidthInCols>
  class lcd_buffered_instance : public mcal::lcd::lcd_base
  {
  private:
    using backend_display_type = BackendDisplayType;

    using row_array_type = std::array<char, static_cast<std::size_t>(WidthInCols)>;

    using row_col_array_buffer_type = std::array<row_array_type, static_cast<std::size_t>(HeightInRows)>;

  public:
    explicit lcd_buffered_instance(backend_display_type& backend_display)
      : my_backend_display(backend_display)
    {
      for(auto& row : row_col_array_buffer)
      {
        row.fill(' ');
      }
    }

    lcd_buffered_instance() = delete;

    ~lcd_buffered_instance() override = default;

    static constexpr auto width () noexcept -> std::size_t { return std::tuple_size<row_array_type>::value; }
    static constexpr auto height() noexcept -> std::size_t { return std::tuple_size<row_col_array_buffer_type>::value; }

    auto init() -> bool override { return my_backend_display.init(); }

    auto write(const char* pstr,
               const std::size_t length,
               const std::uint_fast8_t line_index) -> bool override
    {
      bool result_write_is_ok { };

      if(line_index < static_cast<std::uint_fast8_t>(height()))
      {
        result_write_is_ok = true;

        row_array_type candidate_row;

        candidate_row.fill(' ');

        const auto length_to_copy = (std::min)(static_cast<std::ptrdiff_t>(length), static_cast<std::ptrdiff_t>(width()));

        std::copy(pstr, pstr + length_to_copy, candidate_row.begin());

        if(candidate_row != row_col_array_buffer[static_cast<std::size_t>(line_index)])
        {
          result_write_is_ok =
            my_backend_display.write
            (
              candidate_row.data(),
              static_cast<std::size_t>(width()),
              line_index
            );

          row_col_array_buffer[static_cast<std::size_t>(line_index)] = candidate_row;
        }
      }

      return result_write_is_ok;
    }

  private:
    backend_display_type& my_backend_display;

    row_col_array_buffer_type row_col_array_buffer { };
  };

  #if(__cplusplus >= 201703L)
  } // namespace mcal::lcd
  #else
  } // namespace lcd
  } // namespace mcal
  #endif

#endif // MCAL_LCD_BUFFERED_INSTANCE_2024_02_07_H
