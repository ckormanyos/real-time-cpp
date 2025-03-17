///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

#include <cstdint>

void mcal::wdg::init(const config_type*)
{
  // Disable the super watchdog.

  // RTC_CNTL->SWD_WPROTECT.reg = 0x8F1D312A;
  // RTC_CNTL->WDTCONFIG1.reg = 0;
  // RTC_CNTL->SWD_CONF.reg = (1ul << 30);
  // RTC_CNTL->SWD_WPROTECT.reg = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::swd_wprotect, static_cast<std::uint32_t>(UINT32_C(0x8F1D312A))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::wdtconfig1,   static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::swd_conf,     static_cast<std::uint32_t>(UINT32_C(0x40000000))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rtc_cntl::swd_wprotect, static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();

  // Disable Timer Group 0 WDT.

  // TIMG0->WDTWPROTECT.reg = 0x50D83AA1;
  // TIMG0->WDTCONFIG0.reg  = 0;
  // TIMG0->WDTWPROTECT.reg = 0;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::timg0::wdtwprotect, static_cast<std::uint32_t>(UINT32_C(0x50D83AA1))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::timg0::wdtconfig0,  static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::timg0::wdtwprotect, static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
}

void mcal::wdg::secure::trigger()
{
}
