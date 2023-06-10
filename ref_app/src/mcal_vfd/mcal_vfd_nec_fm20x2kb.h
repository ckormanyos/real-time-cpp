///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_VFD_NEC_FM20X2KB_2023_06_08_H
  #define MCAL_VFD_NEC_FM20X2KB_2023_06_08_H

  #include <algorithm>
  #include <array>

  #include <util/utility/util_communication.h>
  #include <mcal_vfd/mcal_vfd_base.h>

  namespace mcal { namespace vfd {

  class vacuum_fluorescent_display_nec_fm20x2kb
    : public ::mcal::vfd::vacuum_fluorescent_display_base<static_cast<unsigned>(UINT8_C(1)),
                                                          static_cast<unsigned>(UINT8_C(40))>
  {
  private:
    using base_class_type =
      ::mcal::vfd::vacuum_fluorescent_display_base<static_cast<unsigned>(UINT8_C(1)),
                                                   static_cast<unsigned>(UINT8_C(40))>;

  public:
    vacuum_fluorescent_display_nec_fm20x2kb(util::communication_base& ser)
      : my_serial(ser) { }

    ~vacuum_fluorescent_display_nec_fm20x2kb() override = default;

    auto init() noexcept -> bool override
    {
      const auto clr = [this]() { return this->clear_line(static_cast<unsigned>(UINT8_C(0))); };

      auto result_init_is_ok = clr();

      blocking_delay(timer_type::microseconds(static_cast<unsigned>(UINT8_C(500))));

      {
        using cmd_id_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(5))>;

        constexpr auto cmd_id =
          cmd_id_array_type
          {
            static_cast<std::uint8_t>(UINT8_C(0x1B)),
            static_cast<std::uint8_t>(UINT8_C(0x5B)),
            static_cast<std::uint8_t>(UINT8_C(0x31)),
            static_cast<std::uint8_t>(UINT8_C(0x31)),
            static_cast<std::uint8_t>(UINT8_C(0x48))
          };

        result_init_is_ok = (my_serial.send_n(cmd_id.cbegin(), cmd_id.cend()) && result_init_is_ok);

        blocking_delay(timer_type::microseconds(static_cast<unsigned>(UINT8_C(500))));
      }

      {
        using cmd_tst_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(4))>;

        constexpr auto cmd_tst =
          cmd_tst_array_type
          {
            static_cast<std::uint8_t>(UINT8_C(0x1B)),
            static_cast<std::uint8_t>(UINT8_C(0x5B)),
            static_cast<std::uint8_t>(UINT8_C(0x30)),
            static_cast<std::uint8_t>(UINT8_C(0x62))
          };

        result_init_is_ok = (my_serial.send_n(cmd_tst.cbegin(), cmd_tst.cend()) && result_init_is_ok);

        blocking_delay(timer_type::microseconds(static_cast<unsigned>(UINT8_C(500))));
      }

      result_init_is_ok = (clr() && result_init_is_ok);

      blocking_delay(timer_type::microseconds(static_cast<unsigned>(UINT8_C(500))));

      return result_init_is_ok;
    }

    auto write(const char* pstr,
               const std::uint_fast8_t length,
               const std::uint_fast8_t line_index) -> bool override
    {
      static_cast<void>(line_index);

      using cmd_line_array_type =
        std::array<std::uint8_t, static_cast<std::size_t>(number_of_columns + static_cast<unsigned>(UINT8_C(2)))>;

      auto line_cmd_array = cmd_line_array_type { };

      line_cmd_array.fill(static_cast<std::uint8_t>(' '));

      line_cmd_array[static_cast<std::size_t>(UINT8_C(0))] = static_cast<std::uint8_t>(UINT8_C(0x1B));
      line_cmd_array[static_cast<std::size_t>(UINT8_C(1))] = static_cast<std::uint8_t>(UINT8_C(0x5B));

      const auto my_count = (std::min)(static_cast<unsigned>(length), base_class_type::number_of_columns);

      std::copy(pstr,
                pstr + static_cast<std::size_t>(my_count),
                line_cmd_array.begin() + static_cast<std::size_t>(UINT8_C(2)));

      const auto result_write_is_ok = my_serial.send_n(line_cmd_array.cbegin(), line_cmd_array.cend());

      return result_write_is_ok;
    }

    auto clear_line(const unsigned line_number) noexcept -> bool override
    {
      using cmd_clr_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(4))>;

      constexpr auto cmd_clr =
        cmd_clr_array_type
        {
          static_cast<std::uint8_t>(UINT8_C(0x1B)),
          static_cast<std::uint8_t>(UINT8_C(0x5B)),
          static_cast<std::uint8_t>(UINT8_C(0x0D)),
          static_cast<std::uint8_t>(UINT8_C(0x0A))
        };

      const auto result_clr_is_ok = my_serial.send_n(cmd_clr.cbegin(), cmd_clr.cend());

      return result_clr_is_ok;
    }

    auto set_line_index(const std::uint8_t) noexcept -> bool override { return true; }

  private:
    ::util::communication_base& my_serial;
  };

  } } // namespace mcal::vfd

#endif // MCAL_VFD_NEC_FM20X2KB_2023_06_08_H
