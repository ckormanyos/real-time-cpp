#include "led.h"
#include "core_macros.h"
#include "gic-500.h"

#include <stdbool.h>
#include <stdint.h>

void timer_isr(void);

uint64_t mcal_gpt_get_time_elapsed(void);

extern uint32_t GetActiveCoreId(void);

#if defined(__GNUC__)
__attribute__((used,noinline))
#endif
static void main_init(const uint32_t ActiveCore);

#if defined(__GNUC__)
__attribute__((used,noinline))
#endif
static void timer_isr_core(const uint32_t ActiveCore);

extern volatile uint64_t mcal_gpt_system_tick;

static void main_init(const uint32_t ActiveCore)
{
  /* configure the gic */
  volatile gic500_gicdRegs* pGICD = (volatile gic500_gicdRegs* const)GICD_BASE;
  volatile gic500_gicrRegs* pGICR = (volatile gic500_gicrRegs* const)GICR_BASE;

  /* configure the GIC-500 distributor */
  pGICD->CTLR = (1 << 5) | (1 << 4);
  pGICD->CTLR = 1 | (1 << 5) | (1 << 4);

  /* configure the GIC-500 redistributor */
  /* clear GICR_WAKER.ProcessorSleep */
  pGICR->CORE[ActiveCore].CONTROL.WAKER &= ~((uint32_t)2UL);

  /* wait for GICR_WAKER.ChildrenAsleep to become zero */
  while((pGICR->CORE[ActiveCore].CONTROL.WAKER & 4) != 0)
  {
    __asm volatile("nop");
  }

  /* disable all SGI and PPI */
  pGICR->CORE[ActiveCore].SGI_PPI.ISENABLER0 = 0;

  /* assign all PPI and SGI to Group 0 */
  pGICR->CORE[ActiveCore].SGI_PPI.IGROUPR_SGI_PPI = 0;

  /* configure the GIC cpu interface */
  ARM64_WRITE_SYSREG(ICC_SRE_EL3, 0x0f);
  ARM64_WRITE_SYSREG(ICC_IGRPEN0_EL1, 1);
  ARM64_WRITE_SYSREG(ICC_IGRPEN1_EL1, 0);
  ARM64_WRITE_SYSREG(ICC_IGRPEN1_EL3, 0);
  ARM64_WRITE_SYSREG(ICC_PMR_EL1, 0xff);

  /* enable PPI29 (timer interrrupt) */
  pGICR->CORE[ActiveCore].SGI_PPI.ISENABLER0 |= (1ul << 29);

  /* Set priority of INTID 29 */
  ((volatile uint8_t*)&pGICR->CORE[ActiveCore].SGI_PPI.IPRIORITYR[0])[29] = 0; /* highest prio*/

  /* Set level-triggered */
  pGICR->CORE[ActiveCore].SGI_PPI.ICFGR0 &= ~(uint32_t)(1 << ((29 - 16) * 2)); // clear bit to set level-triggered

  /* enable global interrupt */
  arch_enable_ints();
  arch_enable_fiqs();

  /* start the timer */
  ARM64_WRITE_SYSREG(CNTPS_TVAL_EL1, UINT32_C(0x0BEBC200));
  ARM64_WRITE_SYSREG(CNTPS_CTL_EL1, 1);
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
void main(void)
{
  const uint32_t ActiveCore = GetActiveCoreId();

  // Move the core initialization functions into main_init().
  main_init(ActiveCore);

  if(ActiveCore == UINT32_C(0))
  {
    // TBD: Run my cooperative scheduler, and replace the while-loop.
    while(1) { ; }
  }
  else
  {
    while(1) { ; }
  }
}

static void timer_isr_core(const uint32_t ActiveCore)
{
  static uint32_t cpt[4] = {0u};
  static uint64_t intid[4] = {0u};

  intid[ActiveCore] = ARM64_READ_SYSREG(ICC_IAR0_EL1);

  const bool switch_on = (cpt[ActiveCore] % 2u == 0u);

  if(switch_on)
  {
    switch(ActiveCore)
    {
       case 0: LED_1_ON(); break;
       case 1: LED_2_ON(); break;
       case 2: LED_3_ON(); break;
       case 3: LED_4_ON(); break;
       default: break;
    }
  }
  else
  {
    switch(ActiveCore)
    {
       case 0: LED_1_OFF(); break;
       case 1: LED_2_OFF(); break;
       case 2: LED_3_OFF(); break;
       case 3: LED_4_OFF(); break;
       default: break;
    }
  }

  ARM64_WRITE_SYSREG(CNTPS_TVAL_EL1, UINT32_C(0x0BEBC200));
  cpt[ActiveCore]++;
  ARM64_WRITE_SYSREG(ICC_EOIR0_EL1, intid[ActiveCore]);
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
void timer_isr(void)
{
  const uint32_t ActiveCore = GetActiveCoreId();

  timer_isr_core(ActiveCore);

  if(ActiveCore == UINT32_C(0))
  {
    mcal_gpt_system_tick += UINT32_C(200000000);
  }
}

uint64_t mcal_gpt_get_time_elapsed(void)
{
  // Return the system tick using a multiple read to ensure data consistency.

  typedef uint64_t timer_register_type;
  typedef uint64_t value_type;

  // Do the first read of the timer counter and the system tick.
  const timer_register_type timer_cnt_1 = ARM64_READ_SYSREG(CNTPCT_EL0);
  const value_type sys_tick_1 = mcal_gpt_system_tick;

  // Do the second read of the timer0 counter.
  const timer_register_type timer_cnt_2 = ARM64_READ_SYSREG(CNTPCT_EL0);

  // Perform the consistency check.
  value_type consistent_microsecond_tick =
    ((timer_cnt_2 >= timer_cnt_1) ? (value_type) (sys_tick_1           | timer_cnt_1)
                                  : (value_type) (mcal_gpt_system_tick | timer_cnt_2));

  // Convert the consistent tick to microseconds.
  consistent_microsecond_tick = (value_type) ((value_type) (consistent_microsecond_tick + UINT64_C(100)) / UINT64_C(200));

  return consistent_microsecond_tick;
}
