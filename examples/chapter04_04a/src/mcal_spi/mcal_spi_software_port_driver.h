///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H_
  #define MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H_

  // Consider:
  // https://en.wikipedia.org/wiki/Serial_Peripheral_Interface

  // Timing applies to both the master and the slave device.

  // CPOL determines the polarity of the clock.
  //   CPOL=0:
  //   The clock idles to 0 and each cycle consists
  //   of a pulse of 1. The leading edge is a rising edge
  //   and the trailing edge is a falling edge.
  //   CPOL=1:
  //   The clock idles to 1, and each cycle consists
  //   of a pulse of 0. The leading edge is a falling edge
  //   and the trailing edge is a rising edge.
  //
  // CPHA determines the phase of the data relative to SCK.
  //   CPHA=0:
  //   Data out changes on the trailing edge of the
  //   preceding clock cycle, while data in is captured
  //   on (or shortly after) the leading edge of the
  //   clock cycle.
  //   CPHA=1:
  //   Data out changes on the leading edge of the
  //   current clock cycle, while data in is captured
  //   on (or shortly after) the trailing edge of the
  //   clock cycle.

  // The MOSI and MISO signals are usually stable at their
  // reception points) for the half cycle until the next
  // clock transition. SPI master and slave devices can
  // sample data at different points in that half cycle.

  #include <mcal_cpu.h>
  #include <mcal_irq.h>

  #include <util/utility/util_communication.h>

  namespace mcal { namespace spi {

  namespace detail {

  template<const std::size_t nop_count>
  struct spi_nop_maker
  {
    static void execute_n()
    {
      spi_nop_maker<nop_count - 1U>::execute_n();

      mcal::cpu::nop();
    }
  };

  template<>
  struct spi_nop_maker<1U>
  {
    static void execute_n() { mcal::cpu::nop(); }
  };

  template<>
  struct spi_nop_maker<0U>
  {
    static void execute_n() { }
  };

  } // namespace detail

  template<typename port_pin_sck__type,
           typename port_pin_miso_type,
           typename port_pin_mosi_type,
           typename port_pin_csn__type,
           const std::size_t nop_count>
  class spi_software_port_driver : public util::communication_buffer_depth_one_byte
  {
  private:
    using base_class_type = util::communication_buffer_depth_one_byte;

  public:
    // This class implements the SPI protocol with CPOL=0, CPHA=1.

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
      std::uint_fast8_t bit_mask = std::uint8_t(0x80U);

      base_class_type::recv_buffer = 0U;

      mcal::irq::disable_all();

      for(std::uint_fast8_t i = 0U; i < 8U; ++i)
      {
        const bool mosi_write_is_high = (std::uint_fast8_t(byte_to_send & bit_mask) != 0U);

        (mosi_write_is_high ? port_pin_mosi_type::set_pin_high()
                            : port_pin_mosi_type::set_pin_low());

        port_pin_sck__type::set_pin_high();
        detail::spi_nop_maker<nop_count>::execute_n();

        if(port_pin_miso_type::read_input_value())
        {
          base_class_type::recv_buffer |= bit_mask;
        }

        bit_mask >>= 1U;

        port_pin_sck__type::set_pin_low();
      }

      mcal::irq::enable_all();

      return true;
    }

    virtual void   select() { port_pin_csn__type::set_pin_low (); }
    virtual void deselect() { port_pin_csn__type::set_pin_high(); }
  };

  } } // namespace mcal::spi

#endif // MCAL_SPI_SOFTWARE_PORT_DRIVER_2020_04_09_H_
