
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg_access.h>


// See Section 7.5 of the BCM2836 ARM Peripherals documentation.
// The base address of the controller is actually xxxxB000.
// But there is a 0x200 offset to the first addressable register
// for the interrupt controller. So offset the base to the
// first register.

#define RPI_INTERRUPT_CONTROLLER_BASE   0x2000B200

// The interrupt controller memory mapped register set.
typedef struct
{
  volatile std::uint32_t IRQ_basic_pending;
  volatile std::uint32_t IRQ_pending_1;
  volatile std::uint32_t IRQ_pending_2;
  volatile std::uint32_t FIQ_control;
  volatile std::uint32_t Enable_IRQs_1;
  volatile std::uint32_t Enable_IRQs_2;
  volatile std::uint32_t Enable_Basic_IRQs;
  volatile std::uint32_t Disable_IRQs_1;
  volatile std::uint32_t Disable_IRQs_2;
  volatile std::uint32_t Disable_Basic_IRQs;
}
rpi_irq_controller_t;


// Bits in the Enable_Basic_IRQs register to enable various interrupts.
//    See the BCM2835 ARM Peripherals manual, section 7.5.
#define RPI_BASIC_ARM_TIMER_IRQ         (UINT32_C(1) << 0)
#define RPI_BASIC_ARM_MAILBOX_IRQ       (UINT32_C(1) << 1)
#define RPI_BASIC_ARM_DOORBELL_0_IRQ    (UINT32_C(1) << 2)
#define RPI_BASIC_ARM_DOORBELL_1_IRQ    (UINT32_C(1) << 3)
#define RPI_BASIC_GPU_0_HALTED_IRQ      (UINT32_C(1) << 4)
#define RPI_BASIC_GPU_1_HALTED_IRQ      (UINT32_C(1) << 5)
#define RPI_BASIC_ACCESS_ERROR_1_IRQ    (UINT32_C(1) << 6)
#define RPI_BASIC_ACCESS_ERROR_0_IRQ    (UINT32_C(1) << 7)

// See the documentation for the ARM side timer
// (Section 14 of the BCM2835 Peripherals PDF).
#define RPI_ARMTIMER_BASE               0x2000B400

// 16-bit counters - 1 : 23-bit counter.
#define RPI_ARMTIMER_CTRL_23BIT         ( UINT32_C(1) << 1 )

#define RPI_ARMTIMER_CTRL_PRESCALE_1    ( UINT32_C(0) << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_16   ( UINT32_C(1) << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_256  ( UINT32_C(2) << 2 )

// Timer interrupt disabled - 1 : Timer interrupt enabled.
#define RPI_ARMTIMER_CTRL_INT_ENABLE    ( UINT32_C(1) << 5 )
#define RPI_ARMTIMER_CTRL_INT_DISABLE   ( UINT32_C(0) << 5 )

// Timer disabled - 1 : Timer enabled.
#define RPI_ARMTIMER_CTRL_ENABLE        ( UINT32_C(1) << 7 )
#define RPI_ARMTIMER_CTRL_DISABLE       ( UINT32_C(0) << 7 )

// See Section 14.2 of the BCM2835 Peripherals documentation
// for additional details on the register layout for the ARM
// side timer.

typedef struct
{
  // The timer load register sets the time for the timer to count down.
  // This value is loaded into the timer value register after the load
  // register has been written or if the timer-value register has counted
  // down to 0.
  volatile uint32_t Load;

  // This register holds the current timer value and is counted down when
  // the counter is running. It is counted down each timer clock until the
  // value 0 is reached. Then the value register is re-loaded from the
  // timer load register and the interrupt pending bit is set. The timer
  // count down speed is set by the timer pre-divide register.
  volatile uint32_t Value;

  // The standard SP804 timer control register consist of 8 bits but in the
  // BCM implementation there are more control bits for the extra features.
  // Control bits 0-7 are identical to the SP804 bits, albeit some
  // functionality of the SP804 is not implemented. All new control bits
  // start from bit 8 upwards.
  volatile uint32_t Control;

  // The timer IRQ clear register is write only. When writing this register
  // the interrupt-pending bit is cleared. When reading this register it
  // returns 0x544D5241 which is the ASCII reversed value for "ARMT".
  volatile uint32_t IRQClear;

  // The raw IRQ register is a read-only register. It shows the status of
  // the interrupt pending bit.
  //   0 : The interrupt pending bits is clear.
  //   1 : The interrupt pending bit is set.
  // The interrupt pending bits is set each time the value register is
  // counted down to zero. The interrupt pending bit can not by itself
  //  generates interrupts. Interrupts can only be generated if the
  //  interrupt enable bit is set.
  volatile uint32_t RAWIRQ;

  // The masked IRQ register is a read-only register. It shows the status
  // of the interrupt signal. It is simply a logical AND of the interrupt
  // pending bit and the interrupt enable bit. 0 : Interrupt line not
  // asserted. 1 :Interrupt line is asserted, (the interrupt pending and
  // the interrupt enable bit are set.)
  volatile uint32_t MaskedIRQ;

  // This register is a copy of the timer load register. The difference is
  // that a write to this register does not trigger an immediate reload of
  // the timer value register. Instead the timer load register value is
  // only accessed if the value register has finished counting down to
  // zero.
  volatile uint32_t Reload;

  // The Pre-divider register is not present in the SP804. The pre-divider
  // register is 10 bits wide and can be written or read from. This
  // register has been added as the SP804 expects a 1MHz clock which we do
  // not have. Instead the pre-divider takes the APB clock and divides it
  // down according to:
  // timer_clock = apb_clock/(pre_divider+1)
  // The reset value of this register is 0x7D so gives a divide by 126.
  volatile uint32_t PreDivider;

  // The free running counter is not present in the SP804. The free running
  // counter is a 32 bits wide read only register. The register is enabled
  // by setting bit 9 of the Timer control register. The free running
  // counter is incremented immediately after it is enabled. The timer can
  // not be reset but when enabled, will always increment and roll-over.

  // The free running counter is also running from the APB clock and has
  // its own clock pre-divider controlled by bits 16-23 of the timer
  // control register.

  // This register will be halted too if bit 8 of the control register is
  // set and the ARM is in Debug Halt mode.
  volatile uint32_t FreeRunningCounter;
}
rpi_arm_timer_t;


namespace
{
  // The one (and only one) system tick.
  volatile mcal::gpt::value_type system_tick;

  bool& gpt_is_initialized()
  {
    static bool is_init = false;

    return is_init;
  }

  // The BCM2835 Interupt controller peripheral at it's base address.
  rpi_irq_controller_t* rpiIRQController = (rpi_irq_controller_t*) RPI_INTERRUPT_CONTROLLER_BASE;

  rpi_irq_controller_t* RPI_GetIrqController()
  {
    // Return the irq Controller register set.
    return rpiIRQController;
  }

  rpi_arm_timer_t* rpiArmTimer = (rpi_arm_timer_t*) RPI_ARMTIMER_BASE;

  rpi_arm_timer_t* RPI_GetArmTimer(void)
  {
    return rpiArmTimer;
  }
}

extern "C"
void mcal_gpt_timer_interrupt_callback();

void mcal_gpt_timer_interrupt_callback()
{
  // Clear the ARM timer interrupt.
  RPI_GetArmTimer()->IRQClear = 1;

  system_tick += UINT32_C(0x10000);
}

void mcal::gpt::init(const config_type*)
{
  if(gpt_is_initialized() == false)
  {
    gpt_is_initialized() = true;

    // Setup the system timer interrupt.
    // Timer frequency = Clk/1 * 0x10000.
    RPI_GetArmTimer()->Load = UINT32_C(0x10000);

    // Setup the ARM Timer.
    RPI_GetArmTimer()->Control =   RPI_ARMTIMER_CTRL_23BIT
                                 | RPI_ARMTIMER_CTRL_ENABLE
                                 | RPI_ARMTIMER_CTRL_INT_ENABLE
                                 | RPI_ARMTIMER_CTRL_PRESCALE_1;

    // Enable the timer interrupt IRQ.
    RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;
  }
}

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  if(gpt_is_initialized())
  {
    // Return the system tick using a multiple read to ensure data consistency.

    typedef std::uint32_t timer_register_type;

    // Do the first read of the timer value and the system tick.
    const timer_register_type   tmr_tick_1 = UINT32_C(0x10000) - RPI_GetArmTimer()->Value;
    const mcal::gpt::value_type sys_tick_1    = system_tick;

    // Do the second read of the timer value and the system tick.
    const timer_register_type   tmr_tick_2 = UINT32_C(0x10000) - RPI_GetArmTimer()->Value;
    const mcal::gpt::value_type sys_tick_2 = system_tick;

    // Perform the consistency check.
    const mcal::gpt::value_type consistent_microsecond_tick
      = ((tmr_tick_2 >= tmr_tick_1) ? mcal::gpt::value_type(sys_tick_1 | tmr_tick_1)
                                    : mcal::gpt::value_type(sys_tick_2 | tmr_tick_2));

    return consistent_microsecond_tick;
  }
  else
  {
    return mcal::gpt::value_type(0U);
  }
}
