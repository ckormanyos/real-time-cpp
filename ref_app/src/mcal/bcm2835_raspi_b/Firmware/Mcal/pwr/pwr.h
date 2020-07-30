/**
 * @file pwr.h
 *
 * Definitions specific to the BCM2835 SoC used in the Raspberry Pi.
 *
 * Note that although some of the numbers defined in this file are documented in
 * Broadcom's "BCM2835 ARM Peripherals" document, unfortunately some could only
 * be found in the Linux source (arch/arm/mach-bcm2708/include/mach/platform.h).
 */

#ifndef _PWR_H_
#define _PWR_H_

#include "Platform_Types.h"

/********************************************************************
 * ARM physical memory addresses of selected BCM2835 peripherals    *
 ********************************************************************/

/* Start of memory-mapped peripherals address space  */
#define PERIPHERALS_BASE 0x20000000

/* System timer  */
#define SYSTEM_TIMER_REGS_BASE (PERIPHERALS_BASE + 0x3000)

/* Interrupt controller (for ARM)  */
#define INTERRUPT_REGS_BASE    (PERIPHERALS_BASE + 0xB200)

/* Mailbox  */
#define MAILBOX_REGS_BASE      (PERIPHERALS_BASE + 0xB880)

/* Power management / watchdog timer  */
#define PM_REGS_BASE           (PERIPHERALS_BASE + 0x100000)

/* PL011 UART  */
#define PL011_REGS_BASE        (PERIPHERALS_BASE + 0x201000)

/* SD host controller  */
#define SDHCI_REGS_BASE        (PERIPHERALS_BASE + 0x300000)

/* Synopsys DesignWare Hi-Speed USB 2.0 On-The-Go Controller  */
#define DWC_REGS_BASE          (PERIPHERALS_BASE + 0x980000)


/***************************************************************************
 * IRQ lines of selected BCM2835 peripherals.  Note about the numbering    *
 * used here:  IRQs 0-63 are those shared between the GPU and CPU, whereas *
 * IRQs 64+ are CPU-specific.                                              *
 ***************************************************************************/

/* System timer - one IRQ line per output compare register.  */
#define IRQ_SYSTEM_TIMER_0 0
#define IRQ_SYSTEM_TIMER_1 1
#define IRQ_SYSTEM_TIMER_2 2
#define IRQ_SYSTEM_TIMER_3 3

/* Timer IRQ to use by default.  Note: this only be either 1 or 3, since 0 and 2
 * are already used by the VideoCore.  */
#define IRQ_TIMER          IRQ_SYSTEM_TIMER_3

/* Synopsys DesignWare Hi-Speed USB 2.0 On-The-Go Controller  */
#define IRQ_USB            9

/* PCM sound  */
#define IRQ_PCM            55

/* PL011 UART  */
#define IRQ_PL011          57

/* SD card host controller  */
#define IRQ_SD             62


/************************************
 * Board-specific power management  *
 ************************************/

enum board_power_feature {
    POWER_SD     = 0,
    POWER_UART_0 = 1,
    POWER_UART_1 = 2,
    POWER_USB    = 3,
};

#if defined(__cplusplus)
extern "C"
{
#endif

int bcm2835_setpower(enum board_power_feature feature, boolean on);

/************************************************************************
 * Interfaces to memory barriers for peripheral access.                 *
 *                                                                      *
 * These are necessary due to the memory ordering caveats documented in *
 * section 1.3 of Broadcom's "BCM2835 ARM Peripherals" document.        *
 ************************************************************************/

void dmb(void);

#if defined(__cplusplus)
}
#endif

/* Memory barriers needed before/after one or more reads from a peripheral  */
#define pre_peripheral_read_mb    dmb
#define post_peripheral_read_mb   dmb

/* Memory barriers needed before/after one or more writes to a peripheral  */
#define pre_peripheral_write_mb   dmb
#define post_peripheral_write_mb  dmb

/* Memory barriers needed before/after one or more reads and writes from/to a
 * peripheral  */
#define pre_peripheral_access_mb  dmb
#define post_peripheral_access_mb dmb

#endif /* _BCM2835_H_ */
