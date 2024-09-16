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

#include <Platform_Types.h>
#include <Cpu.h>

#include <util/utility/util_time.h>

//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// Prototypes
//=============================================================================
extern "C" void main_Core0(void);
extern "C" void main_Core1(void);
extern "C" void BlockingDelay(uint32 delay);

extern "C"
{
  extern void core_1_run_flag_set(bool);
}

//-----------------------------------------------------------------------------------------
/// \brief  main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
int main(void)
{
  /* Run the main function of the core 0, it will start the core 1 */
  main_Core0();

  /* Synchronize with core 1 */
  RP2350_MulticoreSync((uint32_t)HW_PER_SIO->CPUID.reg);

  /* endless loop on the core 0 */
  for(;;) { ; }

  /* never reached */
  return(0);
}

//-----------------------------------------------------------------------------------------
/// \brief  main_Core0 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void main_Core0(void)
{
  /* Disable interrupts on core 0 */
  __asm volatile("CPSID i");

  /* Start the Core 1 and turn on the led to be sure that we passed successfully the core 1 initiaization */
  if(TRUE == RP2350_StartCore1())
  {
    mcal::led::led0().toggle();
  }
  else
  {
    /* Loop forever in case of error */
    while(1)
    {
      __asm volatile("NOP");
    }
  }
}

//-----------------------------------------------------------------------------------------
/// \brief  main_Core1 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void main_Core1(void)
{
  core_1_run_flag_set(true);

  /* Note: Core 1 is started with interrupt enabled by the BootRom */

  /* Clear the stiky bits of the FIFO_ST on core 1 */
  HW_PER_SIO->FIFO_ST.reg = 0xFFu;

  /*Setting EXTEXCLALL allows external exclusive operations to be used in a configuration with no MPU.
  This is because the default memory map does not include any shareable Normal memory.*/
  SCnSCB->ACTLR |= (1ul<<29);

  __asm volatile("DSB");

  /* Clear all pending interrupts on core 1 */
  NVIC->ICPR[0] = (uint32)-1;

  /* Synchronize with core 0 */
  RP2350_MulticoreSync((uint32_t)HW_PER_SIO->CPUID.reg);

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
