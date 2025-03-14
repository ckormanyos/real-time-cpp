///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:
/******************************************************************************************
  Filename    : Mcu.c
  
  Core        : Xtensa LX7
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : Mcu basic functions for ESP32-S3
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================

#include <mcal_reg.h>

#include <cstdint>

extern "C" {

void Mcu_ClockInit(void);
void Mcu_InitCore(void);

void Mcu_ClockInit(void)
{
  // Set the core clock to 240 MHz and APB clock to 80 MHz.

  // SYSTEM->CPU_PERI_CLK_EN.reg = 7;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::cpu_peri_clk_en, static_cast<std::uint32_t>(UINT32_C(7))>::reg_set();

  //SYSTEM->SYSCLK_CONF.reg = 0x401;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::system::sysclk_conf, static_cast<std::uint32_t>(UINT32_C(0x00000401))>::reg_set();
}

void Mcu_InitCore(void)
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

  // Set all gpio as output low.

  //GPIO->OUT.reg   = 0;
  //GPIO->OUT1.reg  = 0;
  //GPIO->ENABLE_W1TS.reg = 0xFFFFFFFF;
  //GPIO->ENABLE1_W1TS.reg = 0xFFFFFFFF;
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out,          static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::out1,         static_cast<std::uint32_t>(UINT32_C(0x00000000))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable_w1ts,  static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio::enable1_w1ts, static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF))>::reg_set();
}

} // extern "C"
