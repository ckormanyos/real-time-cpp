/******************************************************************************************
  Filename    : main.c
  
  Core        : ARM Cortex-M4
  
  MCU         : Renesas R7FA4M1AB
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.01.2026
  
  Description : Application main function
  
******************************************************************************************/

#include <mcal_led.h>
#include <util/utility/util_time.h>

#include <cstdint>

extern "C" void mcal_gpt_init(void);

int main(void);

int main(void)
{
  mcal_gpt_init();

  using local_timer_type = util::timer<std::uint32_t>;

  mcal::led::led0().toggle();

  local_timer_type blinky_timer { local_timer_type::seconds(UINT8_C(1)) };

  /* endless loop */
  while(1)
  {
    if(blinky_timer.timeout())
    {
      mcal::led::led0().toggle();

      blinky_timer.start_interval(local_timer_type::seconds(UINT8_C(1)));
    }
  }
}
