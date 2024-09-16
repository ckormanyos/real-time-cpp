/******************************************************************************************
  Filename    : main.c
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : Application main function
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include <mcal_gpt.h>
#include <mcal_irq.h>
#include <mcal_led.h>

#include <util/utility/util_time.h>

//-----------------------------------------------------------------------------------------
/// \brief  main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
int main(void)
{
  /* configure ARM systick timer */
  mcal::gpt::init(nullptr);

  mcal::irq::enable_all();

  while(1)
  {
    using local_timer_type = util::timer<std::uint32_t>;

    constexpr local_timer_type::tick_type
      one_second
      {
        local_timer_type::seconds(local_timer_type::tick_type { UINT32_C(1) })
      };

    local_timer_type::blocking_delay(one_second);

    mcal::led::led0().toggle();
  }
}
