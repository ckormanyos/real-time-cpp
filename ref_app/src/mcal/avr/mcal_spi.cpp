///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_reg.h>
#include <mcal_spi.h>

#if 0
#include <util/utility/util_time.h>
#endif

void mcal::spi::init(const mcal::spi::config_type*)
{
#if 0
  // Set the special port pins ss, mosi and sck to output.
  // Do this even though the ss pin will not be used.
  constexpr std::uint8_t pdir_mask =   mcal::reg::bval2
                                     | mcal::reg::bval3
                                     | mcal::reg::bval5;

  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::ddrb,
                               pdir_mask>::reg_or();

  // Enable spi as master mode, clock idle to high, etc.
  // Set the spi clock to f_osc/16 = 1MHz.
  constexpr std::uint8_t spcr_mask =   mcal::reg::bval0
                                     | mcal::reg::bval2
                                     | mcal::reg::bval3
                                     | mcal::reg::bval4
                                     | mcal::reg::bval6;

  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::spcr,
                               spcr_mask>::reg_set();
#endif
}

bool mcal::spi::spi_communication::send(const std::uint8_t byte_to_send)
{
#if 0
  bool result_is_ok;

  if(mcal::reg::reg_access_static<std::uint8_t, std::uint8_t, mcal::reg::spsr, UINT8_C(7)>::reg_get() == true)
  {
    result_is_ok = false;
  }
  else
  {
    using local_timer_type = util::timer<std::uint16_t>;

    // Send the byte over spi.
    mcal::reg::reg_access_dynamic<std::uint8_t,
                                  std::uint8_t>::reg_set(mcal::reg::spdr, byte_to_send);

    const local_timer_type transmission_has_timeout_timer(local_timer_type::milliseconds(10U));

    // Wait for transmission complete.
    while(   (mcal::reg::reg_access_static<std::uint8_t, std::uint8_t, mcal::reg::spsr, UINT8_C(7)>::reg_get() == false)
          && (transmission_has_timeout_timer.timeout() == false))
    {
      mcal::cpu::nop();
    }

    result_is_ok = (transmission_has_timeout_timer.timeout() == false);

    if(result_is_ok)
    {
      recv_buffer_is_full = true;

      const volatile std::uint8_t dummy_read =
        mcal::reg::reg_access_static<std::uint8_t, std::uint8_t, mcal::reg::spsr>::reg_get();

      static_cast<void>(dummy_read);

      communication_buffer_depth_one_byte::recv_buffer =
        mcal::reg::reg_access_static<std::uint8_t, std::uint8_t, mcal::reg::spdr>::reg_get();
    }
  }

  return result_is_ok;
#endif

  return true;
}

util::communication_base& mcal::spi::spi0()
{
  static mcal::spi::spi_communication com;

  return com;
}
