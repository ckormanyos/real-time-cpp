///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <mcal_gpt.h>
#include <mcal_reg_access.h>

namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  mcal::gpt::value_type consistent_microsecond_tick()
  {
    // Return the system tick using a multiple read to ensure
    // data consistency of the high-byte of the system tick.

    typedef std::uint32_t timer_address_type;
    typedef std::uint16_t timer_register_type;

    // Do the first read of the timer4 counter and the system tick.
    const timer_register_type   tim4_cnt_1 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tim4_cnt>::reg_get();
    const mcal::gpt::value_type sys_tick_1 = system_tick;

    // Do the second read of the timer4 counter and the system tick.
    const timer_register_type   tim4_cnt_2 = mcal::reg::access<timer_address_type, timer_register_type, mcal::reg::tim4_cnt>::reg_get();
    const mcal::gpt::value_type sys_tick_2 = system_tick;

    // Perform the consistency check and return the consistent microsecond tick.
    return ((tim4_cnt_2 >= tim4_cnt_1) ? mcal::gpt::value_type(sys_tick_1 | tim4_cnt_1)
                                       : mcal::gpt::value_type(sys_tick_2 | tim4_cnt_2));
  }

  // Define a memory-mapped structure for manipulating
  // the timer4 interrupt priority. This memory-mapped
  // structure has been taken from the STM32 peripheral library,
  // with slight modifications by Chris.
  typedef struct struct_nvic_type
  {
    volatile std::uint32_t iser[8U];        // Offset: 0x000  Interrupt Set Enable Register.
             std::uint32_t reserved0[24U];
    volatile std::uint32_t icer[8U];        // Offset: 0x080  Interrupt Clear Enable Register.
             std::uint32_t reserved1[24U];
    volatile std::uint32_t ispr[8U];        // Offset: 0x100  Interrupt Set Pending Register.
             std::uint32_t reserved2[24U];
    volatile std::uint32_t icpr[8U];        // Offset: 0x180  Interrupt Clear Pending Register.
             std::uint32_t reserved3[24U];
    volatile std::uint32_t iabr[8U];        // Offset: 0x200  Interrupt Active bit Register.
             std::uint32_t reserved4[56U];
    volatile std::uint8_t  ip[240U];        // Offset: 0x300  Interrupt Priority Register (8Bit wide).
             std::uint32_t reserved5[644U];
    volatile std::uint32_t stir;            // Offset: 0xE00  Software Trigger Interrupt Register.
  }
  nvic_type;
}

// TBD: Do we really need interrupt attributes here?
extern "C" void timer4_irq_handler() __attribute__((interrupt));

extern "C" void timer4_irq_handler()
{
  // Clear the interrupt request bit.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_sr, 0x0000U>::reg_set();

  // Increment the second word of the 64-bit system tick by 1.
  system_tick += 0x10000U;
}

void mcal::gpt::init(const config_type*)
{
  // Set up an interrupt on timer4 for a system tick based
  // on the free-running 16-bit timer4 with a frequency of 1MHz.

  // Power management: Enable the power for timer4.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_apb1enr, 0x00000004UL>::reg_or();

  // Compute the timer4 interrupt priority.
  const std::uint32_t aircr_value = mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::aircr>::reg_get();

  // This following code sequence has been inspired by
  // parts of the STM32 peripheral library.
  const std::uint32_t tmp_prio = (0x700UL - (aircr_value & 0x700UL)) >> 0x08;
  const std::uint32_t tmp_pre  = (0x04UL - tmp_prio);
  const std::uint32_t tmp_sub  =  0x0FUL >> tmp_prio;

  constexpr std::uint32_t timer4_nvic_irq_preemption_prio = 0x0FUL;
  constexpr std::uint32_t timer4_nvic_irq_sub_prio        = 0x0FUL;

  constexpr std::size_t timer4_irq_n = 30UL;

  // Place the memory-mapped NVIC configuration structure.
  constexpr nvic_type* nvic = reinterpret_cast<nvic_type*>(0xE000E100UL);

  // Set the timer4 interrupt priority.
  nvic->ip  [timer4_irq_n] = (  static_cast<std::uint32_t>(timer4_nvic_irq_preemption_prio << tmp_pre)
                              | static_cast<std::uint32_t>(timer4_nvic_irq_sub_prio & tmp_sub)
                             ) << 0x04;

  nvic->iser[timer4_irq_n >> 0x05] = static_cast<std::uint32_t>(1UL) << (timer4_irq_n & 0x1FU);

  // Clear the interrupt request bit.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_sr, 0x0000U>::reg_set();

  // Enable the update interrupt.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_dier, 0x0001U>::reg_set();

  // Set the timer prescaler to 24 resulting in a 1MHz frequency.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_psc, 24U - 1U>::reg_set();

  // Set the auto-reload register for the entire 16-bit period of the timer.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_arr, 0xFFFFU>::reg_set();

  // Set the counter direction to counting-up and enable the counter.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_cr1, 0x0001U>::reg_set();

  // Re-initialize the counter and generate an update of the registers.
  mcal::reg::access<std::uint32_t, std::uint16_t, mcal::reg::tim4_egr, 0x0001U>::reg_set();
}

mcal::gpt::value_type mcal::gpt::get_time_elapsed()
{
  return consistent_microsecond_tick();
}

// Implement std::chrono::high_resolution_clock::now()
// for the standard library high-resolution clock.
namespace std
{
  namespace chrono
  {
    high_resolution_clock::time_point high_resolution_clock::now()
    {
      // The source of the high-resolution clock is microseconds.
      typedef std::chrono::time_point<high_resolution_clock, microseconds> microseconds_type;

      // Obtain a time-point from the consistent tick in units of microseconds.
      const microseconds_type my_now(std::chrono::microseconds(::consistent_microsecond_tick()));

      // Return the corresponding duration in microseconds.
      return std::chrono::high_resolution_clock::time_point(my_now);
    }
  }
}
