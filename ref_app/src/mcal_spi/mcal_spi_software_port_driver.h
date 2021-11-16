///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H_
  #define MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H_

  #include <mcal_port.h>
  #include <mcal_port_pin_dummy.h>
  #include <mcal/mcal_helper.h>

  #include <util/utility/util_communication.h>

  namespace mcal { namespace spi {

  template<typename port_pin_sck__type,
           typename port_pin_mosi_type,
           typename port_pin_csn__type,
           typename port_pin_miso_type,
           const std::uint_fast16_t nop_count,
           const bool has_disable_enable_interrupts>
  class spi_software_port_driver : public util::communication_buffer_depth_one_byte
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

    using base_class_type = util::communication_buffer_depth_one_byte;

  public:
    spi_software_port_driver()
    {
      port_pin_csn__type::set_pin_high();
      port_pin_sck__type::set_pin_low();
      port_pin_mosi_type::set_pin_low();

      port_pin_csn__type::set_direction_output();
      port_pin_sck__type::set_direction_output();
      port_pin_mosi_type::set_direction_output();
      port_pin_miso_type::set_direction_input();
    }

    virtual ~spi_software_port_driver() = default;

    virtual bool send(const std::uint8_t byte_to_send)
    {
      base_class_type::recv_buffer = 0U;

      for(std::uint_fast8_t bit_mask = UINT8_C(0x80); bit_mask != UINT8_C(0); bit_mask = std::uint_fast8_t(bit_mask >> 1U))
      {
        ((std::uint_fast8_t(byte_to_send & bit_mask) != UINT8_C(0)) ? port_pin_mosi_type::set_pin_high()
                                                                    : port_pin_mosi_type::set_pin_low());

        mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();

        port_pin_sck__type::set_pin_high();
        mcal::helper::nop_maker<nop_count>();

        port_pin_sck__type::set_pin_low ();
        mcal::helper::nop_maker<nop_count>();

        if(port_pin_miso_type::read_input_value())
        {
          base_class_type::recv_buffer =
            base_class_type::buffer_type(base_class_type::recv_buffer | bit_mask);
        }

        mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();
      }

      return true;
    }

    virtual void   select() { port_pin_csn__type::set_pin_low(); }
    virtual void deselect() { port_pin_csn__type::set_pin_high(); }
  };

  template<typename port_pin_sck__type,
           typename port_pin_mosi_type,
           typename port_pin_csn__type>
  class spi_software_port_driver<port_pin_sck__type,
                                 port_pin_mosi_type,
                                 port_pin_csn__type,
                                 mcal::port::port_pin_dummy,
                                 0U,
                                 true> : public util::communication_buffer_depth_one_byte
  {
  public:
    spi_software_port_driver()
    {
      port_pin_csn__type::set_pin_high();
      port_pin_sck__type::set_pin_low();
      port_pin_mosi_type::set_pin_low();

      port_pin_csn__type::set_direction_output();
      port_pin_sck__type::set_direction_output();
      port_pin_mosi_type::set_direction_output();
    }

    virtual ~spi_software_port_driver() = default;

    virtual bool send(const std::uint8_t byte_to_send)
    {
      for(std::uint_fast8_t bit_mask  = UINT8_C(0x80);
                            bit_mask != UINT8_C(0);
                            bit_mask  = std::uint_fast8_t(bit_mask >> 1U))
      {
        ((std::uint_fast8_t(byte_to_send & bit_mask) != UINT8_C(0)) ? port_pin_mosi_type::set_pin_high()
                                                                    : port_pin_mosi_type::set_pin_low());

        mcal::helper::disable_all_interrupts<true>();

        port_pin_sck__type::set_pin_high();
        port_pin_sck__type::set_pin_low();

        mcal::helper::enable_all_interrupts<true>();
      }

      return true;
    }

    virtual void   select() { port_pin_csn__type::set_pin_low(); }
    virtual void deselect() { port_pin_csn__type::set_pin_high(); }
  };

  } } // namespace mcal::spi

#endif // MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H_
