///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <core_macros.h>
#include <gic-500.h>
#include <mcal_cpu.h>
#include <mcal_irq.h>

#include <stdbool.h>
#include <stdint.h>

#if defined(__GNUC__)
#define ATTRIBUTE_USED __attribute__((used))
#else
#define ATTRIBUTE_USED
#endif

extern uint32_t GetActiveCoreId(void);

extern ATTRIBUTE_USED int main(void);

//extern void main_core0(void);
extern void main_core1(void);
extern void main_core2(void);
extern void main_core3(void);
extern void main_core0_init(void);

ATTRIBUTE_USED void timer_isr(void);
ATTRIBUTE_USED void main_x(void);
ATTRIBUTE_USED static void main_init(const uint32_t ActiveCore);

void main_x(void)
{
  const uint32_t ActiveCore = GetActiveCoreId();

  // Move the core initialization functions into main_init().
  main_init(ActiveCore);

  if     (ActiveCore == UINT32_C(0)) { main_core0_init(); (void) main(); }
  else if(ActiveCore == UINT32_C(1)) { main_core1(); }
  else if(ActiveCore == UINT32_C(2)) { main_core2(); }
  else if(ActiveCore == UINT32_C(3)) { main_core3(); }
  else                               { for(;;) { mcal_cpu_nop(); } }
}

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
  mcal_irq_enable_all();

  /* start the timer */
  ARM64_WRITE_SYSREG(CNTPS_TVAL_EL1, UINT64_C(0x0BEBC200));
  ARM64_WRITE_SYSREG(CNTPS_CTL_EL1, 1);
}

void timer_isr(void)
{
  static uint32_t cpt[4] = {0u};
  static uint64_t intid[4] = {0u};

  const uint32_t ActiveCore = GetActiveCoreId();

  intid[ActiveCore] = ARM64_READ_SYSREG(ICC_IAR0_EL1);

  ARM64_WRITE_SYSREG(CNTPS_TVAL_EL1, UINT64_C(0x0BEBC200));
  cpt[ActiveCore]++;
  ARM64_WRITE_SYSREG(ICC_EOIR0_EL1, intid[ActiveCore]);
}
