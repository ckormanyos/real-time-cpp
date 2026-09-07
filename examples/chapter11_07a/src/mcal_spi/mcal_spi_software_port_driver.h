///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H
  #define MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H

  #include <cstdint>

  #include <mcal/mcal_helper.h>
  #include <mcal_port.h>
  #include <mcal_port_pin_dummy.h>
  #include <util/utility/util_communication.h>

  namespace mcal { namespace spi {

  template<typename port_pin_sck_type,
           typename port_pin_mosi_type,
           typename port_pin_csn_type,
           typename port_pin_miso_type,
           std::uint_fast16_t nop_count,
           bool has_disable_enable_interrupts>
  class spi_software_port_driver final
  {
  private:
    using communication_type = ::util::communication_base;

  public:
    static auto init() -> void
    {
      port_pin_csn_type::set_pin_high();
      port_pin_sck_type::set_pin_low();
      port_pin_mosi_type::set_pin_low();

      port_pin_csn_type::set_direction_output();
      port_pin_sck_type::set_direction_output();
      port_pin_mosi_type::set_direction_output();
      port_pin_miso_type::set_direction_input();
    }

    static auto send(const std::uint8_t byte_to_send, std::uint8_t& byte_to_recv) -> bool
    {
      using value_type = typename communication_type::buffer_value_type;

      byte_to_recv = value_type { UINT8_C(0) };

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

    static auto send_n(communication_type::send_iterator_type first,
                       communication_type::send_iterator_type last,
                       std::uint8_t& byte_to_recv) -> bool
    {
      while(first != last)
      {
        static_cast<void>(send(static_cast<communication_type::buffer_value_type>(*first++), byte_to_recv));
      }

      return true;
    }

    static auto select() -> void
    {
      mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();
      port_pin_csn_type::set_pin_low();
    }

    static auto deselect() -> void
    {
      port_pin_csn_type::set_pin_high();
      mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();
    }

  private:
    template<std::uint_fast8_t BitMask>
    static auto transceive_bit(const std::uint8_t byte_to_send, std::uint8_t& byte_to_recv) -> void
    {
      using value_type = typename communication_type::buffer_value_type;

      constexpr auto bit_mask = BitMask;
      const bool bit_is_high =
        (static_cast<std::uint_fast8_t>(byte_to_send) & bit_mask) != std::uint_fast8_t { UINT8_C(0) };

      (bit_is_high ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low());
      port_pin_sck_type::set_pin_high();
      mcal::helper::nop_maker<nop_count>();

      if(port_pin_miso_type::read_input_value())
      {
        byte_to_recv = static_cast<value_type>(byte_to_recv | bit_mask);
      }

      port_pin_sck_type::set_pin_low();
    }
  };

  template<typename port_pin_sck_type,
           typename port_pin_mosi_type,
           typename port_pin_csn_type,
           std::uint_fast16_t nop_count,
           bool has_disable_enable_interrupts>
  class spi_software_port_driver<port_pin_sck_type,
                                 port_pin_mosi_type,
                                 port_pin_csn_type,
                                 mcal::port::port_pin_dummy,
                                 nop_count,
                                 has_disable_enable_interrupts> final
  {
  private:
    using communication_type = ::util::communication_base;

  public:
    static auto init() -> void
    {
      port_pin_csn_type::set_pin_high();
      port_pin_sck_type::set_pin_low();
      port_pin_mosi_type::set_pin_low();

      port_pin_csn_type::set_direction_output();
      port_pin_sck_type::set_direction_output();
      port_pin_mosi_type::set_direction_output();
    }

    static auto send(const std::uint8_t byte_to_send) -> bool
    {
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x80) });
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x40) });
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x20) });
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x10) });
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x08) });
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x04) });
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x02) });
      send_bit(byte_to_send, std::uint_fast8_t { UINT8_C(0x01) });

      return true;
    }

    static auto send(const std::uint8_t byte_to_send, std::uint8_t& byte_to_recv) -> bool
    {
      byte_to_recv = std::uint8_t { UINT8_C(0) };
      return send(byte_to_send);
    }

    static auto send_n(communication_type::send_iterator_type first,
                       communication_type::send_iterator_type last,
                       std::uint8_t& byte_to_recv) -> bool
    {
      while(first != last)
      {
        static_cast<void>(send(static_cast<std::uint8_t>(*first++), byte_to_recv));
      }

      return true;
    }

    static auto select() -> void
    {
      mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();
      port_pin_csn_type::set_pin_low();
    }

    static auto deselect() -> void
    {
      port_pin_csn_type::set_pin_high();
      mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();
    }

  private:
    static auto send_bit(const std::uint8_t byte_to_send,
                         const std::uint_fast8_t bit_mask) -> void
    {
      const bool bit_is_high =
        (static_cast<std::uint_fast8_t>(byte_to_send) & bit_mask) != std::uint_fast8_t { UINT8_C(0) };

      (bit_is_high ? port_pin_mosi_type::set_pin_high() : port_pin_mosi_type::set_pin_low());
      port_pin_sck_type::set_pin_high();
      mcal::helper::nop_maker<nop_count>();
      port_pin_sck_type::set_pin_low();
    }
  };

  } // namespace spi
  } // namespace mcal

#endif // MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H
