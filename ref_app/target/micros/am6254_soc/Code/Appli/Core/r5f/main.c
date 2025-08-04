#include <stdint.h>
#include "timer.h"
#include "vim.h"

__attribute__((aligned(4))) void timer_irq(void);
__attribute__((aligned(4))) void unhandled_irq(void);

extern void vim_irq_handler(void);
extern void EnableIRQ(void);
extern void EnableFIQ(void);

volatile uint64_t ticks = 0;

#define WKUP_TIMER1_INT_IRQ   139


//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void main(void)
{
  volatile vim_reg* vim = (volatile vim_reg*)VIM_BASE_ADDRESS;

  for(uint32_t i=0; i < VIM_TOTAL_SUPPORTED_INT_NUM; i++)
  {
    vim->vim_interrupt_q_vector[i] = (uint32_t)unhandled_irq;
  }

  /* configure the interrupt for the timer */
  vim->vim_interrupt_q_vector[WKUP_TIMER1_INT_IRQ] = (uint32_t)vim_irq_handler;

  const uint32_t int_group = (uint32_t)(WKUP_TIMER1_INT_IRQ / VIM_GROUP_SIZE);
  const uint32_t int_pos   = (uint32_t)(WKUP_TIMER1_INT_IRQ % VIM_GROUP_SIZE);

  vim->vim_group_m[int_group].vim_group_m_interrupt_enabled_set |= (1ul << int_pos);

  /**/
  __asm("dsb");
  __asm("isb");

  /* enable global interrupt */
  EnableIRQ();
  EnableFIQ();

  /* start the timer */
  timer_init(WKUP_TIMER1_BASE_ADD);
  timer_set_timeout(WKUP_TIMER1_BASE_ADD, TIMER_INPUT_CLK_HZ);
  timer_start(WKUP_TIMER1_BASE_ADD);

  while(1);
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
void timer_irq(void)
{
  volatile vim_reg* vim = (volatile vim_reg*)VIM_BASE_ADDRESS;

  /* get the active IRQ number */
  uint32_t irq_num = (vim->vim_active_irq) & 0x1ful;
  const uint32_t int_group = (uint32_t)(irq_num / VIM_GROUP_SIZE);
  const uint32_t int_pos   = (uint32_t)(irq_num % VIM_GROUP_SIZE);

  /* clear the interrupt */
  vim->vim_group_m[int_group].vim_group_m_interrupt_enabled_status_clear |= (1ul << int_pos);

  /* clear timer interrupt */
  timer_clear_interrupt(WKUP_TIMER1_BASE_ADD, 2);

  /* clear the valid bit of the Active IRQ */
  vim->vim_irq_vector_address = 0;

  /* increment the 1s tick */
  ticks++;

  /* restart the timer */
  timer_init(WKUP_TIMER1_BASE_ADD);
  timer_set_timeout(WKUP_TIMER1_BASE_ADD, TIMER_INPUT_CLK_HZ);
  timer_start(WKUP_TIMER1_BASE_ADD);
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
void unhandled_irq(void)
{
  for(;;);
}
