/******************************************************************************************
  Filename    : main.c
  
  Core        : ARM Cortex-M4
  
  MCU         : Renesas R7FA4M1AB
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.01.2026
  
  Description : Application main function
  
******************************************************************************************/

//-----------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------
#include <cstdint>

#include <util/utility/util_time.h>

#include "R7FA4M1AB.h"


extern "C" void mcal_gpt_init(void);

int main(void);

int main(void)
{
  /* configure pin P111 as output */
  /* disable register write protection for PFS*/
  PMISC->PWPR.bit.B0WI  = 0;
  PMISC->PWPR.bit.PFSWE = 1;

  /* output low */
  PFS->P111PFS.bit.PODR = 0;

  /* configure the pin as output */
  PFS->P111PFS.bit.PDR  = 1;

  /* Set the LED on */
  PFS->P111PFS.bit.PODR ^= 1;

  mcal_gpt_init();

  using local_timer_type = util::timer<std::uint32_t>;

  local_timer_type blinky_timer { local_timer_type::seconds(UINT8_C(1)) };

  /* endless loop */
  while(1)
  {
    if(blinky_timer.timeout())
    {
      PFS->P111PFS.bit.PODR ^= 1;

      blinky_timer.start_interval(local_timer_type::seconds(UINT8_C(1)));
    }
  }
}
