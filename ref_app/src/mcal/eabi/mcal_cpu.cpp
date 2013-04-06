#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  // Power management: Enable power for I/O porta and portc.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_apb2enr, 0x00000014UL>::reg_or();

  // Disable all interrupts and clear pending bits.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cir, 0x009F0000UL>::reg_set();

  // Reset the cfgr2 register.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr2, 0x00000000UL>::reg_set();

  // Relocate the vector table to internal flash.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::scb_vtor, 0x08000000UL>::reg_set();

  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
  mcal::wdg::init(nullptr);
}
