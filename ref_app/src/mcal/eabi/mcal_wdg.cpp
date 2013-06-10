///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_wdg.h>
#include <mcal_reg_access.h>

void mcal::wdg::init(const config_type*)
{
  // Write access to the IWDG_PR and IWDG_RLR registers is protected
  // Register access  unlock protection
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::iwdg_kr,  0x00005555UL>::reg_set();

  // Set the prescaler to 1/4 (with a register value of 0).
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::iwdg_pr,  0x00000000UL>::reg_set();

  // Register Reload set to 500 for a watchdog period of approximately 50ms.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::iwdg_rlr, 500UL>::reg_set();

  // Start the watchdog and lock the access protection.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::iwdg_kr,  0x0000CCCCUL>::reg_set();

  // Read the status register.
  volatile const std::uint32_t dummy_read = mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::iwdg_sr>::reg_get();
  static_cast<void>(dummy_read);
}

void mcal::wdg::trigger()
{
  // Reload the watchdog counter with value in iwdg_rlr
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::iwdg_kr,  0x0000AAAAUL>::reg_set();
}
