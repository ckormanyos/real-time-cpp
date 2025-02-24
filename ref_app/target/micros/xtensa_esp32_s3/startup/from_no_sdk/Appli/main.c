/******************************************************************************************
  Filename    : main.c
  
  Core        : Xtensa LX7
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : Application main function
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include "Platform_Types.h"
#include "esp32s3.h"

//=============================================================================
// Macros
//=============================================================================

//=============================================================================
// Defines
//=============================================================================
#define CORE0_LED  (1ul << 7)
#define CORE1_LED  (1ul << 6)
#define APB_FREQ_MHZ  80000000

//=============================================================================
// Prototypes
//=============================================================================
void main(void);
void main_c1(void);
void blink_led(void);

extern void Mcu_StartCore1(void);
extern uint32_t get_core_id(void);
extern void enable_irq(uint32_t mask);
extern void set_cpu_private_timer1(uint32_t ticks);

//=============================================================================
// Globals
//=============================================================================
volatile uint32_t x = 0xa5a5a5a5;
volatile uint32_t y;

//-----------------------------------------------------------------------------------------
/// \brief  main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void main(void)
{
  GPIO->OUT.reg |= CORE0_LED;

  /* enable all interrupts on core 0 */
  enable_irq((uint32_t)-1);

  Mcu_StartCore1();

  /* set the private cpu timer1 for core 0 */
  set_cpu_private_timer1(APB_FREQ_MHZ);

  for(;;);
}

//-----------------------------------------------------------------------------------------
/// \brief  main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void main_c1(void)
{
  GPIO->OUT.reg |= CORE1_LED;

  /* enable all interrupts on core 1 */
  enable_irq((uint32_t)-1);

  /* set the private cpu timer1 for core 1 */
  set_cpu_private_timer1(APB_FREQ_MHZ);

  for(;;);
}
//-----------------------------------------------------------------------------------------
/// \brief  main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void blink_led(void)
{
  /* reload the private timer1 */
  set_cpu_private_timer1(APB_FREQ_MHZ);
  
  /* toggle the leds */
  if(get_core_id())
  {
    GPIO->OUT.reg ^= CORE1_LED;
  }
  else
  {
    GPIO->OUT.reg ^= CORE0_LED;
  }
}
