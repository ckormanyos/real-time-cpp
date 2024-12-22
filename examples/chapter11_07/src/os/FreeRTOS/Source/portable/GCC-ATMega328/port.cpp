/*
 * FreeRTOS Kernel V10.4.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 * 1 tab == 4 spaces!
 */

/*
Changes from V2.6.0

  + AVR port - Replaced the inb() and outb() functions with direct memory
    access.  This allows the port to be built with the 20050414 build of
    WinAVR.
*/

/*
Changes from Christopher Kormanyos 2020-10-07

  + Switch from C to C++ file.
  + Clean up spaces, tabs and alignment of typing.
  + OS tick uses timer1 compare-match-a to generate
    a tick interrupt at 100Hz (every 10ms).
  + Use an undecorated ISR handle named (__vector_11).
  + Use C++ register template access to setup the timer.
*/

#include <FreeRTOS.h>
#include <mcal_reg.h>
#include <task.h>

#include <cstdlib>

/*--------------------------------------------------------------------
 * Implementation of functions defined in portable.h for the AVR port.
 *------------------------------------------------------------------*/

namespace portable_local
{
  // Start tasks with interrupts enables.
  constexpr StackType_t portFLAGS_INT_ENABLED = (StackType_t) 0x80U;

  void prvSetupTimerInterrupt(void);

  void prvSetupTimerInterrupt(void)
  {
    // Setup timer1 compare-match-a to generate
    // a tick interrupt at 100Hz (every 10ms).

    // Set the compare register (16MHz CPU, prescaler 64).
    // OCR1A = 2500U - 1U;
    mcal::reg::reg_access_static<std::uint8_t,
                                 std::uint16_t,
                                 mcal::reg::ocr1a,
                                 static_cast<std::uint16_t>(2500U - 1U)>::reg_set();

    // Set mode 4, CTC on OCR1A.
    // TCCR1B |= (1 << WGM12);
    mcal::reg::reg_access_static<std::uint8_t,
                                 std::uint8_t,
                                 mcal::reg::tccr1b,
                                 static_cast<std::uint8_t>(1ULL << mcal::reg::wgm12)>::reg_or();

    // Enable interrupt on compare match.
    // TIMSK1 |= (1 << OCIE1A);
    mcal::reg::reg_access_static<std::uint8_t,
                                 std::uint8_t,
                                 mcal::reg::timsk1,
                                 static_cast<std::uint8_t>(1ULL << mcal::reg::ocie1a)>::reg_or();

    // Set prescaler to 64 and start the timer.
    // TCCR1B |= (1 << CS11) | (1 << CS10);
    mcal::reg::reg_access_static<std::uint8_t,
                                 std::uint8_t,
                                 mcal::reg::tccr1b,
                                 static_cast<std::uint8_t>(  (1ULL << mcal::reg::cs11)
                                                           | (1ULL << mcal::reg::cs10))>::reg_or();
  }
}

// We require the address of the pxCurrentTCB variable,
// but don't want to know any details of its type.
using TCB_t = void;
extern volatile TCB_t* volatile pxCurrentTCB;

// Macro to save all the general purpose registers, the save the stack pointer
// into the TCB.  

// The first thing we do is save the flags then disable interrupts.  This is to 
// guard our stack against having a context switch interrupt after we have already 
// pushed the registers onto the stack - causing the 32 registers to be on the 
// stack twice. 

// r1 is set to zero as the compiler expects it to be thus, however some
// of the math routines make use of R1. 

// The interrupts will have been disabled during the call to portSAVE_CONTEXT()
// so we need not worry about reading/writing to the stack pointer. 

#define portSAVE_CONTEXT()                         \
  asm volatile("push  r0                    \n\t"  \
               "in    r0, __SREG__          \n\t"  \
               "cli                         \n\t"  \
               "push  r0                    \n\t"  \
               "push  r1                    \n\t"  \
               "clr  r1                     \n\t"  \
               "push  r2                    \n\t"  \
               "push  r3                    \n\t"  \
               "push  r4                    \n\t"  \
               "push  r5                    \n\t"  \
               "push  r6                    \n\t"  \
               "push  r7                    \n\t"  \
               "push  r8                    \n\t"  \
               "push  r9                    \n\t"  \
               "push  r10                   \n\t"  \
               "push  r11                   \n\t"  \
               "push  r12                   \n\t"  \
               "push  r13                   \n\t"  \
               "push  r14                   \n\t"  \
               "push  r15                   \n\t"  \
               "push  r16                   \n\t"  \
               "push  r17                   \n\t"  \
               "push  r18                   \n\t"  \
               "push  r19                   \n\t"  \
               "push  r20                   \n\t"  \
               "push  r21                   \n\t"  \
               "push  r22                   \n\t"  \
               "push  r23                   \n\t"  \
               "push  r24                   \n\t"  \
               "push  r25                   \n\t"  \
               "push  r26                   \n\t"  \
               "push  r27                   \n\t"  \
               "push  r28                   \n\t"  \
               "push  r29                   \n\t"  \
               "push  r30                   \n\t"  \
               "push  r31                   \n\t"  \
               "lds  r26, pxCurrentTCB      \n\t"  \
               "lds  r27, pxCurrentTCB + 1  \n\t"  \
               "in    r0, 0x3d              \n\t"  \
               "st    x+, r0                \n\t"  \
               "in    r0, 0x3e              \n\t"  \
               "st    x+, r0                \n\t"  \
        );

// Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
// the context save so we can write to the stack pointer. 

#define portRESTORE_CONTEXT()                      \
  asm volatile("lds  r26, pxCurrentTCB      \n\t"  \
               "lds  r27, pxCurrentTCB + 1  \n\t"  \
               "ld    r28, x+               \n\t"  \
               "out  __SP_L__, r28          \n\t"  \
               "ld    r29, x+               \n\t"  \
               "out  __SP_H__, r29          \n\t"  \
               "pop  r31                    \n\t"  \
               "pop  r30                    \n\t"  \
               "pop  r29                    \n\t"  \
               "pop  r28                    \n\t"  \
               "pop  r27                    \n\t"  \
               "pop  r26                    \n\t"  \
               "pop  r25                    \n\t"  \
               "pop  r24                    \n\t"  \
               "pop  r23                    \n\t"  \
               "pop  r22                    \n\t"  \
               "pop  r21                    \n\t"  \
               "pop  r20                    \n\t"  \
               "pop  r19                    \n\t"  \
               "pop  r18                    \n\t"  \
               "pop  r17                    \n\t"  \
               "pop  r16                    \n\t"  \
               "pop  r15                    \n\t"  \
               "pop  r14                    \n\t"  \
               "pop  r13                    \n\t"  \
               "pop  r12                    \n\t"  \
               "pop  r11                    \n\t"  \
               "pop  r10                    \n\t"  \
               "pop  r9                     \n\t"  \
               "pop  r8                     \n\t"  \
               "pop  r7                     \n\t"  \
               "pop  r6                     \n\t"  \
               "pop  r5                     \n\t"  \
               "pop  r4                     \n\t"  \
               "pop  r3                     \n\t"  \
               "pop  r2                     \n\t"  \
               "pop  r1                     \n\t"  \
               "pop  r0                     \n\t"  \
               "out  __SREG__, r0           \n\t"  \
               "pop  r0                     \n\t"  \
        );

// See header file for description.
extern "C"
StackType_t* pxPortInitialiseStack(StackType_t* pxTopOfStack,
                                   TaskFunction_t pxCode,
                                   void* pvParameters)
{
  // Place a few bytes of known values on the bottom
  // of the stack. This is just useful for debugging.

  *pxTopOfStack = 0x11U; --pxTopOfStack;
  *pxTopOfStack = 0x22U; --pxTopOfStack;
  *pxTopOfStack = 0x33U; --pxTopOfStack;

  // Simulate how the stack would look after a call to vPortYield()
  // generated by the compiler.

  // lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it.

  // The start of the task code will be popped off the stack last,
  // so place it on first.
  uint16_t usAddress = (uint16_t) pxCode;
  *pxTopOfStack = (StackType_t) (usAddress & (uint16_t) 0x00FFU);
  --pxTopOfStack;

  usAddress >>= 8U;
  *pxTopOfStack = (StackType_t) (usAddress & (uint16_t) 0x00FFU);
  --pxTopOfStack;

  // Next simulate the stack as if after a call to portSAVE_CONTEXT().
  // portSAVE_CONTEXT places the flags on the stack immediately after r0
  // to ensure the interrupts get disabled as soon as possible, and so ensuring
  // the stack use is minimal should a context switch interrupt occur.
  *pxTopOfStack = (StackType_t) 0x00U;  /* R0  */
  --pxTopOfStack;

  *pxTopOfStack = portable_local::portFLAGS_INT_ENABLED;
  --pxTopOfStack;

  // Now the remaining registers.   The compiler expects R1 to be 0.
  *pxTopOfStack = (StackType_t) 0x00U;  /* R1  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x02U;  /* R2  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x03U;  /* R3  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x04U;  /* R4  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x05U;  /* R5  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x06U;  /* R6  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x07U;  /* R7  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x08U;  /* R8  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x09U;  /* R9  */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x10U;  /* R10 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x11U;  /* R11 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x12U;  /* R12 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x13U;  /* R13 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x14U;  /* R14 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x15U;  /* R15 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x16U;  /* R16 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x17U;  /* R17 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x18U;  /* R18 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x19U;  /* R19 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x20U;  /* R20 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x21U;  /* R21 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x22U;  /* R22 */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x23U;  /* R23 */ --pxTopOfStack;

  // Place the parameter on the stack in the expected location.
  usAddress = (uint16_t) pvParameters;
  *pxTopOfStack = (StackType_t) (usAddress & (uint16_t) 0x00FFU); --pxTopOfStack;

  usAddress >>= 8;
  *pxTopOfStack = (StackType_t) (usAddress & (uint16_t) 0x00FFU); --pxTopOfStack;

  *pxTopOfStack = (StackType_t) 0x26;  /* R26 X */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x27;  /* R27   */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x28;  /* R28 Y */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x29;  /* R29   */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x30;  /* R30 Z */ --pxTopOfStack;
  *pxTopOfStack = (StackType_t) 0x31;  /* R31   */ --pxTopOfStack;

  // lint +e950 +e611 +e923

  return pxTopOfStack;
}

extern "C"
BaseType_t xPortStartScheduler(void)
{
  // Setup the hardware to generate the tick.
  portable_local::prvSetupTimerInterrupt();

  // Restore the context of the first task that is going to run.
  portRESTORE_CONTEXT();

  // Simulate a function call end as generated by the compiler.
  // We will now jump to the start of the task the context
  // of which we have just restored.
  asm volatile ("ret");

  // Should not get here.
  return pdTRUE;
}

extern "C"
void vPortEndScheduler(void)
{
  // It is unlikely that the AVR port will get stopped.
  // If required simply disable the tick interrupt here.
}

extern "C"
void vPortYield(void) __attribute__((naked));

extern "C"
void vPortYield(void)
{
  // Manual context switch.  The first thing we do is save
  // the registers so we can use a naked attribute.

  portSAVE_CONTEXT();

  vTaskSwitchContext();

  portRESTORE_CONTEXT();

  asm volatile ("ret");
}

extern "C"
void vPortYieldFromTick(void) __attribute__((naked));

extern "C"
void vPortYieldFromTick(void)
{
  // Context switch function used by the tick.  This must be identical to 
  // vPortYield() from the call to vTaskSwitchContext() onwards.  The only
  // difference from vPortYield() is the tick count is incremented as the
  // call comes from the tick ISR.

  portSAVE_CONTEXT();

  if(xTaskIncrementTick() != pdFALSE)
  {
    vTaskSwitchContext();
  }

  portRESTORE_CONTEXT();

  asm volatile ( "ret" );
}

#if (configUSE_PREEMPTION == 1)

extern "C"
void __vector_11(void) __attribute__((signal, used, externally_visible, naked));

extern "C"
void __vector_11(void)
{
  // Tick ISR for preemptive scheduler.  We can use a naked attribute as
  // the context is saved at the start of vPortYieldFromTick().  The tick
  // count is incremented after the context is saved.

  vPortYieldFromTick();

  asm volatile ("reti");
}

#else

extern "C"
void __vector_11(void) __attribute__((signal, used, externally_visible));

extern "C"
void __vector_11(void)
{
  // Tick ISR for the cooperative scheduler.  All this does is increment the
  // tick count.  We don't need to switch context, this can only be done by
  // manual calls to taskYIELD();

  xTaskIncrementTick();
}

#endif
