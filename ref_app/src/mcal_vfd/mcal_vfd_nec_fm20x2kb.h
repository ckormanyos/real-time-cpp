///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_VFD_NEC_FM20X2KB_2023_06_08_H
  #define MCAL_VFD_NEC_FM20X2KB_2023_06_08_H

  #include <mcal_vfd/mcal_vfd_base.h>
  #include <util/utility/util_communication.h>

  #include <array>

  namespace mcal { namespace vfd {

  class vacuum_fluorescent_display_nec_fm20x2kb
    : public ::mcal::vfd::vacuum_fluorescent_display_base<static_cast<unsigned>(UINT8_C(1)),
                                                          static_cast<unsigned>(UINT8_C(40))>
  {
  private:
    using base_class_type =
      ::mcal::vfd::vacuum_fluorescent_display_base<static_cast<unsigned>(UINT8_C(1)),
                                                   static_cast<unsigned>(UINT8_C(40))>;

    using cmd_line_buffer_type =
      std::array<std::uint8_t, static_cast<std::size_t>(base_class_type::number_of_cols() + static_cast<unsigned>(UINT8_C(2)))>;

  public:
    explicit vacuum_fluorescent_display_nec_fm20x2kb(util::communication_base& ser)
      : my_serial(ser) { }

    vacuum_fluorescent_display_nec_fm20x2kb() = delete;

    ~vacuum_fluorescent_display_nec_fm20x2kb() override = default;

    auto init() -> bool override
    {
      const auto clr = [this]() { return this->clear_line(static_cast<unsigned>(UINT8_C(0))); };

      auto result_init_is_ok = clr();

      blocking_delay(timer_type::microseconds(static_cast<unsigned>(UINT8_C(500))));

      {
        using cmd_id_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(5))>;

        constexpr auto cmd_id =
          cmd_id_array_type
          {
            std::uint8_t { UINT8_C(0x1B) },
            std::uint8_t { UINT8_C(0x5B) },
            std::uint8_t { UINT8_C(0x31) },
            std::uint8_t { UINT8_C(0x31) },
            std::uint8_t { UINT8_C(0x48) }
          };

        result_init_is_ok = (my_serial.send_n(cmd_id.cbegin(), cmd_id.cend()) && result_init_is_ok);

        blocking_delay(timer_type::microseconds(unsigned { UINT8_C(500) }));
      }

      {
        using cmd_tst_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(4))>;

        constexpr auto cmd_tst =
          cmd_tst_array_type
          {
            std::uint8_t { UINT8_C(0x1B) },
            std::uint8_t { UINT8_C(0x5B) },
            std::uint8_t { UINT8_C(0x30) },
            std::uint8_t { UINT8_C(0x62) }
          };

        result_init_is_ok = (my_serial.send_n(cmd_tst.cbegin(), cmd_tst.cend()) && result_init_is_ok);

        blocking_delay(timer_type::microseconds(unsigned { UINT8_C(500) }));
      }

      result_init_is_ok = (clr() && result_init_is_ok);

      blocking_delay(timer_type::microseconds(unsigned { UINT8_C(500) }));

      return result_init_is_ok;
    }

    auto write(const char* pstr,
               const std::uint_fast8_t length,
               const std::uint_fast8_t line_index) -> bool override
    {
      static_cast<void>(line_index);

      my_cmd_line_buffer.fill(static_cast<std::uint8_t>(' '));

      my_cmd_line_buffer[std::size_t {  UINT8_C(0) }] = std::uint8_t { UINT8_C(0x1B) };
      my_cmd_line_buffer[std::size_t {  UINT8_C(1) }] = std::uint8_t { UINT8_C(0x5B) };

      const auto my_count = (std::min)(static_cast<unsigned>(length), base_class_type::number_of_cols());

      std::copy(pstr,
                pstr + static_cast<std::size_t>(my_count),
                my_cmd_line_buffer.begin() + static_cast<std::size_t>(UINT8_C(2)));

      const auto result_write_is_ok = my_serial.send_n(my_cmd_line_buffer.cbegin(), my_cmd_line_buffer.cend());

      return result_write_is_ok;
    }

    auto clear_line(const unsigned = static_cast<unsigned>(UINT8_C(0))) -> bool override
    {
      using cmd_clr_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(4))>;

      constexpr auto cmd_clr =
        cmd_clr_array_type
        {
          std::uint8_t { UINT8_C(0x1B) },
          std::uint8_t { UINT8_C(0x5B) },
          std::uint8_t { UINT8_C(0x0D) },
          std::uint8_t { UINT8_C(0x0A) }
        };

      const auto result_clr_is_ok = my_serial.send_n(cmd_clr.cbegin(), cmd_clr.cend());

      return result_clr_is_ok;
    }

    auto set_line_index(const std::uint8_t) -> bool override { return true; }

  private:
    ::util::communication_base& my_serial;
    cmd_line_buffer_type my_cmd_line_buffer { };
  };

  } } // namespace mcal::vfd

#endif // MCAL_VFD_NEC_FM20X2KB_2023_06_08_H
