///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

namespace mcal { namespace cpu { namespace detail {

void enable_i_cache();
void enable_d_cache();

} } } // namespace mcal::cpu::detail

void mcal::cpu::init()
{
  // Configure the flash wait states (280 MHz --> 6 WS).
  //Flash->ACR.bit.LATENCY = 6u;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::flash_acr, static_cast<std::uint32_t>(UINT8_C(6))>::template reg_msk<UINT32_C(7)>();

  // Relocate the vector table to internal flash.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_vtor, static_cast<std::uint32_t>(UINT32_C(0x08000000))>::reg_set();

  // Initialize the FPU: Enable CP10 and CP11.
  //CPACR |= 0x00F00000UL;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_cpacr, static_cast<std::uint32_t>(UINT32_C(0x00F00000))>::reg_or();

  // Enable ITCM and DTCM.
  //ITCMCR |= 1UL;
  //DTCMCR |= 1UL;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_itcmcr, static_cast<std::uint32_t>(UINT8_C(1))>::reg_or();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_dtcmcr, static_cast<std::uint32_t>(UINT8_C(1))>::reg_or();

  asm volatile("dsb");
  asm volatile("isb");

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}

void mcal::cpu::post_init()
{
  // Enable the Cache-I and Cache-D.
  detail::enable_i_cache();
  detail::enable_d_cache();
}

void mcal::cpu::detail::enable_i_cache()
{
  if(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_ccr, static_cast<std::uint32_t>(UINT8_C(17))>::bit_get())
  {
    asm volatile("dsb");
    asm volatile("isb");

    // Invalidate the instruction cache.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_iciallu, static_cast<std::uint32_t>(UINT8_C(0))>::reg_set();
    asm volatile("dsb");
    asm volatile("isb");

    // Enable the Instruction cache.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_ccr, static_cast<std::uint32_t>(UINT8_C(17))>::bit_set();
    asm volatile("dsb");
    asm volatile("isb");
  }
}

void mcal::cpu::detail::enable_d_cache()
{
  //uint32_t sets = 0U;
  if(!mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_ccr, static_cast<std::uint32_t>(UINT8_C(16))>::bit_get())
  {
    // Enable selection of data cache.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_csselr, static_cast<std::uint32_t>(UINT8_C(0))>::reg_set();
    asm volatile("dsb");

    // Invalidate the data cache.
    auto sets =
      static_cast<std::uint32_t>
      (
          static_cast<std::uint32_t>
          (
               mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_ccsidr>::reg_get()
            >> static_cast<unsigned>(UINT8_C(13))
          )
        &
          static_cast<std::uint32_t>(UINT32_C(0x7FFF))
      );
    asm volatile("dsb");

    do
    {
      auto ways = mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_ccsidr>::reg_get();
      asm volatile("dsb");

      ways =
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(ways >> static_cast<unsigned>(UINT8_C(3)))
          & static_cast<std::uint32_t>(UINT32_C(0x3FF))
        );

      do
      {
        const auto dcisw_reg_val =
          static_cast<std::uint32_t>
          (
              static_cast<std::uint32_t>(ways << static_cast<unsigned>(UINT8_C(30)))
            | static_cast<std::uint32_t>(sets << static_cast<unsigned>(UINT8_C( 5)))
          );

        mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set(mcal::reg::scb_dcisw, dcisw_reg_val);
        asm volatile("dsb");
      }
      while(ways-- != static_cast<std::uint32_t>(UINT8_C(0)));
      asm volatile("dsb");

    }
    while(sets-- != static_cast<std::uint32_t>(UINT8_C(0)));
    asm volatile("dsb");

    // Enable the data cache.
    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::scb_ccr, static_cast<std::uint32_t>(UINT8_C(16))>::bit_set();
    asm volatile("dsb");
    asm volatile("isb");
  }
}
