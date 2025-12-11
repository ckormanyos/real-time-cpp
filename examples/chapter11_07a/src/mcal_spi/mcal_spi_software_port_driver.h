///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H
  #define MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H

  #include <mcal/mcal_helper.h>
  #include <mcal_port.h>
  #include <mcal_port_pin_dummy.h>
  #include <util/utility/util_attribute.h>
  #include <util/utility/util_communication.h>

  namespace mcal { namespace spi {

  template<typename port_pin_sck__type,
           typename port_pin_mosi_type,
           typename port_pin_csn__type,
           typename port_pin_miso_type,
           const std::uint_fast16_t nop_count,
           const bool has_disable_enable_interrupts>
  class spi_software_port_driver : public ::util::communication_base
  {
  private:
    // Consider:
    // https://en.wikipedia.org/wiki/Serial_Peripheral_Interface

    // Timing applies to both the master and the slave device.

    // CPOL=0:
    //   The clock idles to 0 and each cycle consists
    //   of a pulse of 1. The leading edge is a rising edge
    //   and the trailing edge is a falling edge.

    // CPHA=0:
    //   Data out changes on the trailing edge of the
    //   preceding clock cycle, while data in is captured
    //   on (or shortly after) the leading edge of the
    //   clock cycle.

    using base_class_type = ::util::communication_base;

  public:
    static auto init() -> void
    {
      port_pin_csn__type::set_pin_high();
      port_pin_sck__type::set_pin_low();
      port_pin_mosi_type::set_pin_low();

      port_pin_csn__type::set_direction_output();
      port_pin_sck__type::set_direction_output();
      port_pin_mosi_type::set_direction_output();
      port_pin_miso_type::set_direction_input();
    }

    static auto send(const std::uint8_t byte_to_send, std::uint8_t& byte_to_recv) -> bool
    {
      using value_type = typename base_class_type::buffer_value_type;

      byte_to_recv = static_cast<value_type>(UINT8_C(0));

      transceive_bit<std::uint_fast8_t { UINT8_C(0x80) }>(byte_to_send, byte_to_recv);
      transceive_bit<std::uint_fast8_t { UINT8_C(0x40) }>(byte_to_send, byte_to_recv);
      transceive_bit<std::uint_fast8_t { UINT8_C(0x20) }>(byte_to_send, byte_to_recv);
      transceive_bit<std::uint_fast8_t { UINT8_C(0x10) }>(byte_to_send, byte_to_recv);
      transceive_bit<std::uint_fast8_t { UINT8_C(0x08) }>(byte_to_send, byte_to_recv);
      transceive_bit<std::uint_fast8_t { UINT8_C(0x04) }>(byte_to_send, byte_to_recv);
      transceive_bit<std::uint_fast8_t { UINT8_C(0x02) }>(byte_to_send, byte_to_recv);
      transceive_bit<std::uint_fast8_t { UINT8_C(0x01) }>(byte_to_send, byte_to_recv);

      return true;
    }

    static auto send_n(base_class_type::send_iterator_type first,
                       base_class_type::send_iterator_type last,
                       std::uint8_t& byte_to_recv) -> bool
    {
      while(first != last)
      {
        using value_type = typename base_class_type::buffer_value_type;

        const auto byte_to_send { static_cast<value_type>(*first++) };

        static_cast<void>(send(byte_to_send, byte_to_recv));
      }

      return true;
    }

    static auto select() -> void
    {
      mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();

      port_pin_csn__type::set_pin_low();
    }

    static auto deselect() -> void
    {
      port_pin_csn__type::set_pin_high();

      mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();
    }

  private:
    template<const std::uint_fast8_t BitMask>
    static auto transceive_bit(const std::uint8_t byte_to_send, std::uint8_t& byte_to_recv) -> void
    {
      using value_type = typename base_class_type::buffer_value_type;

      constexpr std::uint_fast8_t bit_mask { BitMask };

      const bool
        bit_is_high
        {
          (static_cast<std::uint_fast8_t>(static_cast<std::uint_fast8_t>(byte_to_send) & bit_mask) != static_cast<std::uint_fast8_t>(UINT8_C(0)))
        };

      (bit_is_high ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low());

      port_pin_sck__type::set_pin_high();
      mcal::helper::nop_maker<nop_count>();

      if(port_pin_miso_type::read_input_value())
      {
        byte_to_recv =
          static_cast<value_type>
          (
            static_cast<std::uint_fast8_t>(byte_to_recv) | bit_mask
          );
      }

      port_pin_sck__type::set_pin_low();
    }
  };

  template<typename port_pin_sck__type,
           typename port_pin_mosi_type,
           typename port_pin_csn__type,
           const bool has_disable_enable_interrupts>
  class spi_software_port_driver<port_pin_sck__type,
                                 port_pin_mosi_type,
                                 port_pin_csn__type,
                                 mcal::port::port_pin_dummy,
                                 static_cast<std::uint_fast16_t>(UINT8_C(0)),
                                 has_disable_enable_interrupts> : public util::communication_base
  {
  public:
    static auto init() -> void
    {
      port_pin_csn__type::set_pin_high();
      port_pin_sck__type::set_pin_low();
      port_pin_mosi_type::set_pin_low();

      port_pin_csn__type::set_direction_output();
      port_pin_sck__type::set_direction_output();
      port_pin_mosi_type::set_direction_output();
    }

    static auto send(const std::uint8_t byte_to_send) -> bool
    {
      const std::uint_fast8_t by { static_cast<std::uint_fast8_t>(byte_to_send) };

      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x80))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();
      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x40))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();
      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x20))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();
      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x10))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();
      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x08))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();
      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x04))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();
      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x02))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();
      (static_cast<std::uint_fast8_t>(by & static_cast<std::uint_fast8_t>(UINT8_C(0x01))) != static_cast<std::uint_fast8_t>(UINT8_C(0))) ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low(); port_pin_sck__type::set_pin_high(); port_pin_sck__type::set_pin_low();

      return true;
    }

    static auto select() -> void
    {
      mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();

      port_pin_csn__type::set_pin_low();
    }

    static auto deselect() -> void
    {
      port_pin_csn__type::set_pin_high();

      mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();
    }
  };

  } // namespace spi
  } // namespace mcal

#endif // MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H
