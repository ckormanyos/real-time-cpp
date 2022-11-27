///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  // Set 64-bit access in flash_acr.
  mcal::reg::reg_access_static<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::flash_acr,
                    2U>::bit_set();

  // Verify 64-bit access in flash_acr.
  const bool acc64_is_ok =
    mcal::reg::reg_access_static<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::flash_acr,
                      2U>::bit_get();

  if(acc64_is_ok == false)
  {
    for(;;)
    {
      mcal::cpu::nop();
    }
  }

  // Set latency of 1 wait state in flash_acr.
  mcal::reg::reg_access_static<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::flash_acr,
                    0U>::bit_set();

  // Verify latency access in flash_acr.
  const bool latency_is_ok =
    mcal::reg::reg_access_static<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::flash_acr,
                      0U>::bit_get();

  if(latency_is_ok == false)
  {
    for(;;)
    {
      mcal::cpu::nop();
    }
  }

  // Disable all interrupts and clear pending bits.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cir, 0x00000000UL>::reg_set();

  // Relocate the vector table to internal flash.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_vtor, static_cast<std::uint32_t>(UINT32_C(0x08000000))>::reg_set();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
