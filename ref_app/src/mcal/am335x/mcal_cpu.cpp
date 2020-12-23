///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_cpu_detail.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  // Disable OPP50 operation and enable OPP100 operation.
  // Use the ratio for 24MHz to 32KHz division.
  // See Chapter 9.3.8 in the am335x manual.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::control::clk32kdivratio_ctrl,
                               UINT32_C(0x00000000)>::reg_set();

  mcal::wdg::init (nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init (nullptr);
}

void mcal::cpu::fpu()
{
  asm volatile("mrc p15, #0, r1, c1, c0, #2");
  asm volatile("orr r1, r1, #0x00F00000");
  asm volatile("mcr p15, #0, r1, c1, c0, #2");
  asm volatile("isb");
  asm volatile("mov r1, #0x40000000");
  asm volatile("vmsr fpexc, r1");
}

void mcal::cpu::post_init()
{
  detail::init();

  detail::user_mode();
}
