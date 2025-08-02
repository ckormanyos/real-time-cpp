

#include "timer.h"

volatile uint64_t mcal_gpt_system_tick;

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void timer_init(uintptr_t timer_base)
{
  volatile timer_reg* pTimer = (volatile timer_reg*)timer_base;

  /* reset the timer */
  pTimer->TIOCP_CFG |= 1;
}

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void timer_start(uintptr_t timer_base)
{
  volatile timer_reg* pTimer = (volatile timer_reg*)timer_base;

  /* start the timer */
  pTimer->TCLR |= 1;
}

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void timer_stop(uintptr_t timer_base)
{
  volatile timer_reg* pTimer = (volatile timer_reg*)timer_base;

  /* stop the timer */
  pTimer->TCLR &= (uint32_t)(~1);
}

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void timer_set_timeout(uintptr_t timer_base, uint32_t value)
{
  volatile timer_reg* pTimer = (volatile timer_reg*)timer_base;

  /* set the reload value */
  pTimer->TCRR = (uint32_t)((uint32_t)(-1) - value - 1ul);

  /* enable overflow interrupt */
  pTimer->IRQSTATUS_SET |= 2ul;
}

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void timer_clear_interrupt(uintptr_t timer_base, uint32_t mask)
{
  volatile timer_reg* pTimer = (volatile timer_reg*)timer_base;

  /* clear interrupt interrupt */
  pTimer->IRQSTATUS_CLR |= (uint32_t)(mask & 0x07ul);
}
