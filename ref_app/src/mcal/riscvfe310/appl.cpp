#include <cstddef>

#include "FE310.h"
#include "mtimer.h"
#include "riscv-csr.h"
#include <mcal_port.h>

#include <mcal_led/mcal_led_port.h>

#define MTIME_TIMEOUT_LED_PHASE 1000U

extern "C" void Isr_MachineTimerInterrupt(void);

extern "C" auto appl_main(void) -> void;

namespace
{
  using led0_port_type = mcal::port::port_pin<std::uint32_t,
                                              std::uint32_t,
                                              mcal::reg::gpio0_base,
                                              UINT8_C(5)>;

  using led0_led_type = mcal::led::led_port<led0_port_type>;

  led0_led_type l0;
}

extern "C" auto appl_main(void) -> void
{
  //led0_port_type::set_pin_low();
  //led0_port_type::set_direction_output();

  /* start the mtimer */
  mtimer_StartTimer(MTIME_TIMEOUT_MS(MTIME_TIMEOUT_LED_PHASE));

  /* endless loop*/
  for(;;)
  {
    ;
  }
}

extern "C"
void Isr_MachineTimerInterrupt(void)
{
  /* toggle the blue led */
  //led0_port_type::toggle_pin();
  GPIO0->output_val.bit.pin5 ^= 1;

  /* reload the mtimer */
  mtimer_ReloadTimer(MTIME_TIMEOUT_MS(MTIME_TIMEOUT_LED_PHASE));
}

void operator delete(void*)        noexcept;
void operator delete(void*, void*) noexcept;
#if(__cplusplus >= 201400L)
void operator delete(void*, std::size_t) noexcept;
#endif

void operator delete(void*)              noexcept { }
void operator delete(void*, void*)       noexcept { }
#if(__cplusplus >= 201400L)
void operator delete(void*, std::size_t) noexcept { }
#endif
