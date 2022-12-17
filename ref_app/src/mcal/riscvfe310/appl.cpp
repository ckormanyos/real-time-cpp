#include "FE310.h"
#include "mtimer.h"
#include "riscv-csr.h"

#define MTIME_TIMEOUT_LED_PHASE 1000U

extern "C" void Isr_MachineTimerInterrupt(void);

extern "C" auto appl_main(void) -> void;

extern "C" auto appl_main(void) -> void
{
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
  GPIO0->output_val.bit.pin5 ^= 1;

  /* reload the mtimer */
  mtimer_ReloadTimer(MTIME_TIMEOUT_MS(MTIME_TIMEOUT_LED_PHASE));
}
