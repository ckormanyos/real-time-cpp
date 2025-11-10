///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_osc.h>
#include <mcal_reg.h>

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 24MHz using the pll.

  // Setup the pll prescaler to x6, for a maximum of 24 MHz.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr,
                               UINT32_C(0x00100000)>::reg_set();

  // Enable the pll.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cr,
                               std::uint32_t(1UL << 24U)>::reg_or();

  // Set the pll as system clock at 24 MHz.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cfgr,
                               UINT32_C(0x00000002)>::reg_or();
}
