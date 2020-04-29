///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_irq.h>
#include <mcal_reg.h>

void mcal::irq::init(const config_type*)
{
  // Enable all global interrupts.
  mcal::irq::enable_all();
}

void mcal::irq::set_handler_priority(const std::int32_t irq_n, const std::uint32_t priority)
{
  const std::uint32_t shifted = (std::uint32_t(std::uint32_t(irq_n) & 0x03U) * 8U);

  const std::uint32_t value =
    (std::uint32_t(std::uint32_t(priority << (8U - nvic_priority_bits)) & 0xFFU) << shifted);

  const std::uint32_t mask  = UINT32_C(0xFF) << shifted;

  // Core interrupt
  if(irq_n < 0) {

    const std::uint32_t idx =
      (std::uint32_t(std::uint32_t(std::uint32_t(irq_n) & 0x0FU) - 8U) >> 2U);

    const std::uint32_t address = mcal::reg::scb_shp + (idx * 4U);

    mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_msk(address, value, mask);
  }

  // Peripheral interrupt
  else {

    const std::uint32_t idx     = (std::uint32_t(irq_n) >> 2U);

    const std::uint32_t address = mcal::reg::nvic_ip + (idx * 4);

    mcal::reg::reg_access_dynamic<std::uint32_t,
                                  std::uint32_t>::reg_msk(address, value, mask);
  }
}
