///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>
#include <am335x_hw_regs.h>

void mcal::cpu::init()
{
  mcal::port::init(nullptr);
  mcal::wdg::init(nullptr);
  mcal::osc::init(nullptr);
}

void mcal::cpu::switch_to_privileged_mode()
{
  // This API can be used to switch from user mode to privileged mode
  // The priviledge mode will be system mode. System mode will share 
  // the same resources as user mode, but with privileges.
  asm volatile("swi 458752");
}

void mcal::cpu::switch_to_user_mode()
{
  // This API can be used to switch from any previleged mode of ARM to 
  // user mode. After this API is called, the program will continue
  // to operate in non-privileged mode, until any exception occurs.
  // After the exception is serviced, execution will continue in user
  // mode.
  asm volatile("mrs r0, cpsr");
  asm volatile("bic r0, #0x0F");
  asm volatile("orr r0, #0x10");
  asm volatile("msr cpsr, r0");
}

std::uint32_t mcal::cpu::read_dfsr()
{
  std::uint32_t status;

  // IRQ and FIQ in CPSR
  asm volatile("mrc p15, #0, %[result], c5, c0, #0\n\t" : [result] "=r" (status));

  return status;
}

std::uint32_t mcal::cpu::read_dfar()
{
  std::uint32_t status;

  // IRQ and FIQ in CPSR.
  asm volatile("mrc p15, #0, %[result], c6, c0, #0\n\t" : [result] "=r" (status));

  return status;
}

extern "C" void cpu_abort_handler()
{
  // This API is called when the CPU is aborted or during execution
  // of any undefined instruction. Both IRQ and FIQ will be disabled
  // when the CPU gets an abort and calls this API. 
  const std::uint32_t fault_type = mcal::cpu::read_dfsr();

  GPIO1->CLEARDATAOUT = std::uint32_t(0x01E00000UL);
  GPIO1->SETDATAOUT   = std::uint32_t(std::uint32_t(fault_type & std::uint32_t(0x0FUL)) << 21U);
}

std::uint32_t mcal::cpu::int_status()
{
  // Wrapper function for the IRQ status.
  std::uint32_t status;

  // IRQ and FIQ in CPSR
  asm volatile("mrs r0, cpsr\n\t"
               "and %[result], r0, #0xC0" : [result] "=r" (status));

  return status;
}

void mcal::cpu::fiqd()
{
  // Wrapper function for the FIQ disable function.

  // Disable FIQ in CPSR
  asm volatile("mrs r0, cpsr");
  asm volatile("orr r0, #0x40");
  asm volatile("msr cpsr, r0");
}

void mcal::cpu::fiqe()
{
  // Wrapper function for the FIQ enable function.

  // Enable FIQ in CPSR
  asm volatile("mrs r0, cpsr");
  asm volatile("bic r0, #0x40");
  asm volatile("msr cpsr, r0");
}
