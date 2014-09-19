
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Copyright Stephan Hage 2014.
//  Copyright Florin Onufriciuc 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <array>
#include <cstddef>
#include <mcal_cpu.h>

extern "C" void _reset_                     () __attribute__((section(".startup"), used, noinline));
extern "C" void undefined_instruction_vector() __attribute__((interrupt("UNDEF"), used, noinline));
extern "C" void software_interrupt_vector   () __attribute__((interrupt("SWI"),   used, noinline));
extern "C" void prefetch_abort_vector       () __attribute__((interrupt("ABORT"), used, noinline));
extern "C" void data_abort_vector           () __attribute__((interrupt("ABORT"), used, noinline));
extern "C" void interrupt_vector            () __attribute__((interrupt("IRQ"),   used, noinline));
extern "C" void fast_interrupt_vector       () __attribute__((interrupt("FIQ"),   used, noinline));

namespace
{
  typedef void(*function_type)();

  constexpr std::size_t number_of_interrupts_nmi = std::size_t(8U);
}

extern "C" const std::array<function_type, number_of_interrupts_nmi> __isr_vector_nmi __attribute__((section(".isr_vector_nmi")));

void undefined_instruction_vector() { for(;;) { mcal::cpu::nop(); } }
void software_interrupt_vector   () { for(;;) { mcal::cpu::nop(); } }
void prefetch_abort_vector       () { for(;;) { mcal::cpu::nop(); } }
void data_abort_vector           () { for(;;) { mcal::cpu::nop(); } }

extern "C"
void mcal_gpt_timer_interrupt_callback();


// See Section 7.5 of the BCM2836 ARM Peripherals documentation, the base
// address of the controller is actually xxxxB000, but there is a 0x200 offset
// to the first addressable register for the interrupt controller, so offset the
// base to the first register.
#define RPI_INTERRUPT_CONTROLLER_BASE   UINT32_C(0x2000B200)

// The interrupt controller memory mapped register set.
typedef struct
{
  volatile uint32_t IRQ_basic_pending;
  volatile uint32_t IRQ_pending_1;
  volatile uint32_t IRQ_pending_2;
  volatile uint32_t FIQ_control;
  volatile uint32_t Enable_IRQs_1;
  volatile uint32_t Enable_IRQs_2;
  volatile uint32_t Enable_Basic_IRQs;
  volatile uint32_t Disable_IRQs_1;
  volatile uint32_t Disable_IRQs_2;
  volatile uint32_t Disable_Basic_IRQs;
}
rpi_irq_controller_t;

// The BCM2835 Interupt controller peripheral at it's base address.
static rpi_irq_controller_t* rpiIRQController = (rpi_irq_controller_t*) RPI_INTERRUPT_CONTROLLER_BASE;

rpi_irq_controller_t* RPI_GetIrqController();

rpi_irq_controller_t* RPI_GetIrqController()
{
  // Return the IRQ Controller register set.
  return rpiIRQController;
}

void interrupt_vector()
{
  // Clear the ARM timer interrupt.
  
  // TBD: For now, this is the only interrupt we have enabled,
  // so we do not have to query the interrupt source.

  // TBD: Query the interrupt source.
  mcal_gpt_timer_interrupt_callback();
}

void fast_interrupt_vector()
{
}
