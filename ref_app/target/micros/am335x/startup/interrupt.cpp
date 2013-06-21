/**
 *  \file   interrupt.c
 *
 *  \brief  Interrupt related APIs.
 *
 *   This file contains the APIs for configuring AINTC
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include "hw_intc.h"
#include "interrupt.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "cpu.h"

/******************************************************************************
**                INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define REG_IDX_SHIFT                  (0x05)
#define REG_BIT_MASK                   (0x1F)
#define NUM_INTERRUPTS                 (128u)

/**************** *************************************************************
**                 STATIC VARIABLE DEFINITIONS
******************************************************************************/
void (*fnRAMVectors[NUM_INTERRUPTS])(void);

/******************************************************************************
**                STATIC FUNCTION DECLARATIONS
******************************************************************************/
extern "C" void IntDefaultHandler(void);

/******************************************************************************
**                     API FUNCTION DEFINITIONS
******************************************************************************/

/**
 *
 * The Default Interrupt Handler. 
 *
 * This is the default interrupt handler for all interrupts.  It simply loops
 * forever so that the system state is preserved for observation by a
 * debugger.  Since interrupts should be disabled before unregistering the
 * corresponding handler, this should never be called.
 *
 *
 **/
extern "C" void IntDefaultHandler(void)
{
  /* Go into an infinite loop.*/
  while(1)
  {
    ;
  }
}

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts. 
 * 
 * \param    intrNum - Interrupt Number
 * \param    fnHandler - Function pointer to the ISR
 * 
 * Note: When the interrupt occurs for the sytem interrupt number indicated,
 * the control goes to the ISR given as the parameter.
 * 
 * \return      None.
 **/
extern "C" void IntRegister(std::uint32_t intrNum, void (*fnHandler)(void))
{
  /* Assign ISR */
  fnRAMVectors[intrNum] = fnHandler;
}

/**
 * \brief   Unregisters an interrupt
 * 
 * \param   intrNum - Interrupt Number
 * 
 * Note: Once an interrupt is unregistered it will enter infinite loop once
 * an interrupt occurs
 * 
 * \return      None.
 **/
extern "C" void IntUnRegister(std::uint32_t intrNum)
{
  /* Assign default ISR */
  fnRAMVectors[intrNum] = IntDefaultHandler;
}

/**
 * \brief   This API is used to initialize the interrupt controller. This API  
 *          shall be called before using the interrupt controller. 
 *
 * \param   None
 * 
 * \return  None.
 *
 **/
extern "C" void IntAINTCInit(void)
{
  /* Reset the ARM interrupt controller */
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;

  /* Wait for the reset to complete */
  while((*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SYSSTATUS) 
        & INTC_SYSSTATUS_RESETDONE) != INTC_SYSSTATUS_RESETDONE);    

  /* Enable any interrupt generation by setting priority threshold */ 
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_THRESHOLD) = INTC_THRESHOLD_PRIORITYTHRESHOLD;
}

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   hostIntRoute - The host interrupt IRQ/FIQ to which the interrupt
 *                         is to be routed.
 *     'priority' can take any value from 0 to 127, 0 being the highest and
 *     127 being the lowest priority.              
 *
 *     'hostIntRoute' can take one of the following values \n
 *             AINTC_HOSTINT_ROUTE_IRQ - To route the interrupt to IRQ \n
 *             AINTC_HOSTINT_ROUTE_FIQ - To route the interrupt to FIQ
 *
 * \return  None.
 *
 **/
extern "C" void IntPrioritySet(std::uint32_t intrNum, std::uint32_t priority,
                    std::uint32_t hostIntRoute)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_ILR(intrNum)) =
                               ((priority << INTC_ILR_PRIORITY_SHIFT)
                                 & INTC_ILR_PRIORITY)
                               | hostIntRoute ;
}

/**
 * \brief   This API enables the system interrupt in AINTC. However, for 
 *          the interrupt generation, make sure that the interrupt is 
 *          enabled at the peripheral level also. 
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
extern "C" void IntSystemEnable(std::uint32_t intrNum)
{
  /* Disable the system interrupt in the corresponding MIR_CLEAR register */
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_MIR_CLEAR(intrNum >> REG_IDX_SHIFT)) = (0x01UL << (intrNum & REG_BIT_MASK));
}

/**
 * \brief   This API disables the system interrupt in AINTC. 
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
extern "C" void IntSystemDisable(std::uint32_t intrNum)
{
  /* Enable the system interrupt in the corresponding MIR_SET register */
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_MIR_SET(intrNum >> REG_IDX_SHIFT)) = (0x01UL << (intrNum & REG_BIT_MASK));
}

/**
 * \brief   Sets the interface clock to be free running
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
extern "C" void IntIfClkFreeRunSet(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SYSCONFIG)&= ~INTC_SYSCONFIG_AUTOIDLE; 
}

/**
 * \brief   When this API is called,  automatic clock gating strategy is applied
 *          based on the interface bus activity. 
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
extern "C" void IntIfClkAutoGateSet(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SYSCONFIG) |= INTC_SYSCONFIG_AUTOIDLE; 
}

/**
 * \brief   Reads the active IRQ number.
 *
 * \param   None
 *
 * \return  Active IRQ number.
 *
 **/
extern "C" std::uint32_t IntActiveIrqNumGet(void)
{
  return (*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SIR_IRQ) &  INTC_SIR_IRQ_ACTIVEIRQ);
}

/**
 * \brief   Reads the active FIQ number.
 *
 * \param   None
 *
 * \return  Active FIQ number.
 *
 **/
extern "C" std::uint32_t IntActiveFiqNumGet(void)
{
  return (*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SIR_FIQ) &  INTC_SIR_FIQ_ACTIVEFIQ);
}

/**
 * \brief   Reads the spurious IRQ Flag. Spurious IRQ flag is reflected in both
 *          SIR_IRQ and IRQ_PRIORITY registers of the interrupt controller.
 *
 * \param   None
 *
 * \return  Spurious IRQ Flag.
 *
 **/
extern "C" std::uint32_t IntSpurIrqFlagGet(void)
{
  return ((*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SIR_IRQ) 
           & INTC_SIR_IRQ_SPURIOUSIRQ) 
          >> INTC_SIR_IRQ_SPURIOUSIRQ_SHIFT);
}

/**
 * \brief   Reads the spurious FIQ Flag. Spurious FIQ flag is reflected in both
 *          SIR_FIQ and FIQ_PRIORITY registers of the interrupt controller.
 *
 * \param   None
 *
 * \return  Spurious IRQ Flag.
 *
 **/
extern "C" std::uint32_t IntSpurFiqFlagGet(void)
{
  return ((*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_SIR_FIQ) 
           & INTC_SIR_FIQ_SPURIOUSFIQ) 
          >> INTC_SIR_FIQ_SPURIOUSFIQ_SHIFT);
}

/**
 * \brief   Enables protection mode for the interrupt controller register access.
 *          When the protection is enabled, the registers will be accessible only
 *          in privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
extern "C" void IntProtectionEnable(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_PROTECTION) = INTC_PROTECTION_PROTECTION;
}

/**
 * \brief   Disables protection mode for the interrupt controller register access.
 *          When the protection is disabled, the registers will be accessible 
 *          in both unprivileged and privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
extern "C" void IntProtectionDisable(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_PROTECTION) &= ~INTC_PROTECTION_PROTECTION;
}

/**
 * \brief   Enables the free running of input synchronizer clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
extern "C" void IntSyncClkFreeRunSet(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_IDLE) &= ~INTC_IDLE_TURBO;
}

/**
 * \brief   When this API is called, Input synchronizer clock is auto-gated 
 *          based on interrupt input activity
 *
 * \param   None
 *
 * \return  None
 *
 **/
extern "C" void IntSyncClkAutoGateSet(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_IDLE) |= INTC_IDLE_TURBO;
}

/**
 * \brief   Enables the free running of functional clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
extern "C" void IntFuncClkFreeRunSet(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_IDLE) |= INTC_IDLE_FUNCIDLE;
}

/**
 * \brief   When this API is called, functional clock gating strategy
 *          is applied.
 *
 * \param   None
 *
 * \return  None
 *
 **/
extern "C" void IntFuncClkAutoGateSet(void)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_IDLE) &= ~INTC_IDLE_FUNCIDLE;
}

/**
 * \brief   Returns the currently active IRQ priority level.
 *
 * \param   None
 *
 * \return  Current IRQ priority 
 *
 **/
extern "C" std::uint32_t IntCurrIrqPriorityGet(void)
{
  return (*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_IRQ_PRIORITY) & INTC_IRQ_PRIORITY_IRQPRIORITY);
}

/**
 * \brief   Returns the currently active FIQ priority level.
 *
 * \param   None
 *
 * \return  Current FIQ priority
 *
 **/
extern "C" std::uint32_t IntCurrFiqPriorityGet(void)
{
  return (*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_FIQ_PRIORITY) & INTC_FIQ_PRIORITY_FIQPRIORITY);
}

/**
 * \brief   Returns the priority threshold.
 *
 * \param   None
 *
 * \return  Priority threshold value.
 *
 **/
extern "C" std::uint32_t IntPriorityThresholdGet(void)
{
  return (*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_THRESHOLD) & INTC_THRESHOLD_PRIORITYTHRESHOLD);
}

/**
 * \brief   Sets the given priority threshold value. 
 *
 * \param   threshold - Priority threshold value
 *
 *      'threshold' can take any value from 0x00 to 0x7F. To disable
 *      priority threshold, write 0xFF.
 *             
 * \return  None.
 *
 **/
extern "C" void IntPriorityThresholdSet(std::uint32_t threshold)
{
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_THRESHOLD) = threshold & INTC_THRESHOLD_PRIORITYTHRESHOLD;
}

/**
 * \brief   Returns the raw interrupt status before masking.
 *
 * \param   intrNum - the system interrupt number.
 *
 * \return  TRUE - if the raw status is set \n
 *          FALSE - if the raw status is not set.   
 *
 **/
extern "C" std::uint32_t IntRawStatusGet(std::uint32_t intrNum)
{
  return ((0 == ((*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_ITR(intrNum >> REG_IDX_SHIFT))
                  >> (intrNum & REG_BIT_MASK))& 0x01)) ? FALSE : TRUE);
}

/**
 * \brief   Sets software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be generated
 *
 * \return  None
 *
 **/
extern "C" void IntSoftwareIntSet(std::uint32_t intrNum)
{
  /* Enable the software interrupt in the corresponding ISR_SET register */
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_ISR_SET(intrNum >> REG_IDX_SHIFT)) = (0x01UL << (intrNum & REG_BIT_MASK));
}

/**
 * \brief   Clears the software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be cleared.
 *
 * \return  None
 *
 **/
extern "C" void IntSoftwareIntClear(std::uint32_t intrNum)
{
  /* Disable the software interrupt in the corresponding ISR_CLEAR register */
  *reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_ISR_CLEAR(intrNum >> REG_IDX_SHIFT)) = (0x01UL << (intrNum & REG_BIT_MASK));
}

/**
 * \brief   Returns the IRQ status after masking.
 *
 * \param   intrNum - the system interrupt number
 *
 * \return  TRUE - if interrupt is pending \n
 *          FALSE - in no interrupt is pending
 *
 **/
extern "C" std::uint32_t IntPendingIrqMaskedStatusGet(std::uint32_t intrNum)
{
  return ((0 ==(*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_PENDING_IRQ(intrNum >> REG_IDX_SHIFT))
                >> (((intrNum & REG_BIT_MASK)) & 0x01))) ? FALSE : TRUE);
}

/**
 * \brief   Returns the FIQ status after masking.
 *
 * \param   intrNum - the system interrupt number
 *
 * \return  TRUE - if interrupt is pending \n
 *          FALSE - in no interrupt is pending
 *
 **/
extern "C" std::uint32_t IntPendingFiqMaskedStatusGet(std::uint32_t intrNum)
{
  return ((0 ==(*reinterpret_cast<volatile std::uint32_t*>(SOC_AINTC_REGS + INTC_PENDING_FIQ(intrNum >> REG_IDX_SHIFT))
                >> (((intrNum & REG_BIT_MASK)) & 0x01))) ? FALSE : TRUE);
}

/**
 * \brief  Enables the processor IRQ only in CPSR. Makes the processor to 
 *         respond to IRQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
extern "C" void IntMasterIRQEnable(void)
{
  /* Enable IRQ in CPSR.*/
  CPUirqe();
}

/**
 * \brief  Disables the processor IRQ only in CPSR.Prevents the processor to 
 *         respond to IRQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
extern "C" void IntMasterIRQDisable(void)
{
  /* Disable IRQ in CPSR.*/
  CPUirqd();
}

/**
 * \brief  Enables the processor FIQ only in CPSR. Makes the processor to 
 *         respond to FIQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
extern "C" void IntMasterFIQEnable(void)
{
  /* Enable FIQ in CPSR.*/
  CPUfiqe();
}

/**
 * \brief  Disables the processor FIQ only in CPSR.Prevents the processor to 
 *         respond to FIQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
extern "C" void IntMasterFIQDisable(void)
{
  /* Disable FIQ in CPSR.*/
  CPUfiqd();
}

/**
 * \brief   Returns the status of the interrupts FIQ and IRQ.
 *
 * \param    None
 *
 * \return   Status of interrupt as in CPSR.
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
extern "C" std::uint32_t IntMasterStatusGet(void)
{
  return CPUIntStatus();
}

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.  
 *
 * \param    None
 *
 * \return   Current status of IRQ
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
extern "C" unsigned char IntDisable(void)
{
  unsigned char status;

  /* Reads the current status.*/
  status = (IntMasterStatusGet() & 0xFF);

  /* Disable the Interrupts.*/
  IntMasterIRQDisable();

  return status;
}

/**
 * \brief  Restore the processor IRQ only status. This does not affect 
 *          the set of interrupts enabled/disabled in the AINTC.
 *
 * \param    The status returned by the IntDisable fundtion.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
extern "C" void IntEnable(unsigned char status)
{
  if((status & 0x80) == 0) 
  {
    IntMasterIRQEnable();
  }
}
