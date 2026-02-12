/******************************************************************************************
  Filename    : main.c
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.01.2026
  
  Description : Application main function
  
******************************************************************************************/

#include <riscv-csr.h>
#include <esp32p4.h>
#include <interrupt.h>
#include <gpio.h>

#include <cstdint>

constexpr unsigned TIMEOUT_500MS { 160000000u };
constexpr unsigned TIMEOUT_1S    { 320000000u };

extern "C"
{
  uint32_t osGetActiveCore(void);
  void __attribute__((interrupt)) Isr_TIMER_Interrupt(void);
}

auto main(void) -> int __attribute__((used,noinline));

auto main(void) -> int
{
  if(0 == osGetActiveCore())
  {
    gpio_cfg_output(7);
    gpio_cfg_output(8);
    gpio_cfg_output(24);
    gpio_cfg_output(25);
    gpio_cfg_output(46);
    gpio_cfg_output(47);
    gpio_cfg_output(48);
    gpio_cfg_output(54);
    gpio_cfg_output(20);
    gpio_cfg_output(19);
    gpio_cfg_output(18);
    gpio_cfg_output(17);
    gpio_cfg_output(16);
    gpio_cfg_output(15);
    gpio_cfg_output(14);
    gpio_cfg_output(33);
    gpio_cfg_output(32);
    gpio_cfg_output(27);
    gpio_cfg_output(26);
    gpio_cfg_output(23);
    gpio_cfg_output(32);
    gpio_cfg_output(21);
  }

  // Set the timer interrupt as hardware vectored in the CLIC.
  CLIC->interrupt[INT_TIMER_ID].clicintattr = 1;

  // Enable the timer machine interrupt in the CLIC.
  CLIC->interrupt[INT_TIMER_ID].clicintie   = 1;

  // Configure the sampling mode of MTIME.
  CLINT_MTIMECTL |= (3ul << 4);

  // Set the MTIME timeout.
  CLINT_MTIMECMP = (uint64_t)(CLINT_MTIME + TIMEOUT_1S);

  // Endless loop: Never return or break.
  while(1)
  {
    asm volatile("nop");
  }
}

extern "C"
void Isr_TIMER_Interrupt(void)
{
  CLINT_MTIMECMP = (uint64_t)(CLINT_MTIME + TIMEOUT_1S);

  const std::uint32_t core_id { osGetActiveCore() };

  if(std::uint32_t { UINT8_C(0) } == core_id)
  {
    gpio_toggle_output_level(54);
  }
  else if(std::uint32_t { UINT8_C(1) } == core_id)
  {
    gpio_toggle_output_level(19);
  }
}
