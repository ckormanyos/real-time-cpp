#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

typedef struct {
    uint32_t TIDR;                                     //offset:0x00
    uint32_t TIOCP_CFG __attribute__((aligned(0x10))); //offset:0x10
    uint32_t IRQ_EOI   __attribute__((aligned(0x20))); //offset:0x20
    uint32_t IRQSTATUS_RAW;                            //offset:0x24
    uint32_t IRQSTATUS;                                //offset:0x28
    uint32_t IRQSTATUS_SET;                            //offset:0x2C
    uint32_t IRQSTATUS_CLR;                            //offset:0x30
    uint32_t IRQWAKEEN;                                //offset:0x34
    uint32_t TCLR;                                     //offset:0x38
    uint32_t TCRR;                                     //offset:0x3C
    uint32_t TLDR;                                     //offset:0x40
    uint32_t TTGR;                                     //offset:0x44
    uint32_t TWPS;                                     //offset:0x48
    uint32_t TMAR;                                     //offset:0x4C
    uint32_t TCAR1;                                    //offset:0x50
    uint32_t TSICR;                                    //offset:0x54
    uint32_t TCAR2;                                    //offset:0x58
    uint32_t TPIR;                                     //offset:0x5C
    uint32_t TNIR;                                     //offset:0x60
    uint32_t TCVR;                                     //offset:0x64
    uint32_t TOCR;                                     //offset:0x68
    uint32_t TOWR;                                     //offset:0x6C
}timer_reg;

#define TIMER_INPUT_CLK_HZ  25000000  //25MHz

/* all timers base addresses */
#define TIMER0_BASE_ADDR     (uintptr_t)0x02400000
#define TIMER1_BASE_ADDR     (uintptr_t)0x02410000
#define TIMER2_BASE_ADDR     (uintptr_t)0x02420000
#define TIMER3_BASE_ADDR     (uintptr_t)0x02430000
#define TIMER4_BASE_ADDR     (uintptr_t)0x02440000
#define TIMER5_BASE_ADDR     (uintptr_t)0x02450000
#define TIMER6_BASE_ADDR     (uintptr_t)0x02460000
#define TIMER7_BASE_ADDR     (uintptr_t)0x02470000
#define MCU_TIMER0_BASE_ADDR (uintptr_t)0x04800000
#define MCU_TIMER1_BASE_ADDR (uintptr_t)0x04810000
#define MCU_TIMER2_BASE_ADDR (uintptr_t)0x04820000
#define MCU_TIMER3_BASE_ADDR (uintptr_t)0x04830000
#define WKUP_TIMER0_BASE_ADD (uintptr_t)0x2B100000
#define WKUP_TIMER1_BASE_ADD (uintptr_t)0x2B110000

void timer_init(uintptr_t timer_base);
void timer_start(uintptr_t timer_base);
void timer_stop(uintptr_t timer_base);
void timer_set_timeout(uintptr_t timer_base, uint32_t value);
void timer_clear_interrupt(uintptr_t timer_base, uint32_t mask);

#endif /*__TIMER_H__*/
