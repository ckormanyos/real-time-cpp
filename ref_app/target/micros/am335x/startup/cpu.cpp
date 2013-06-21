
#include <am335x_hw_regs.h>
#include <Bfx.h>
#include "cpu.h"

extern "C" void          CPUSwitchToPrivilegedMode();
extern "C" void          CPUSwitchToUserMode      ();
extern "C" std::uint32_t CPUReadDFSR              ();
extern "C" std::uint32_t CPUReadDFAR              ();
extern "C" void          CPUAbortHandler          ();
extern "C" std::uint32_t CPUIntStatus             ();
extern "C" void          CPUirqd                  ();
extern "C" void          CPUirqe                  ();
extern "C" void          CPUfiqd                  ();
extern "C" void          CPUfiqe                  ();

/**
 * \brief     This API can be used to switch from user mode to privileged mode
 *            The priviledge mode will be system mode. System mode will share 
 *            the same resources as user mode, but with privileges.
 *
 * \param     None.
 *
 * \return    None.
 *
 * Note : All the access to system configuration which needs privileged access
 *        can be done after calling this API.
 **/
extern "C" void CPUSwitchToPrivilegedMode(void)
{
  asm volatile("SWI 458752");
}

/**
 * \brief     This API can be used to switch from any previleged mode of ARM to 
 *            user mode. After this API is called, the program will continue
 *            to operate in non-privileged mode, until any exception occurs.
 *            After the exception is serviced, execution will continue in user
 *            mode.
 *
 * \param     None.
 *
 * \return    None.
 *
 * Note : All the access to system configuration which needs privileged access
 *        shall be done before this API is called.
 **/
extern "C" void CPUSwitchToUserMode(void)
{
  asm volatile("    mrs     r0, CPSR\n\t"
               "    bic     r0, #0x0F\n\t"
               "    orr     r0, #0x10\n\t "
               "    msr     CPSR, r0");
}

extern "C" std::uint32_t CPUReadDFSR(void)
{
  std::uint32_t stat;

  /* IRQ and FIQ in CPSR */
  asm volatile("    mrc p15, #0, %[result], c5, c0, #0\n\t" : [result] "=r" (stat));

  return stat;
}

extern "C" std::uint32_t CPUReadDFAR(void)
{
    std::uint32_t stat;

    /* IRQ and FIQ in CPSR */
    asm volatile("    mrc p15, #0, %[result], c6, c0, #0\n\t" : [result] "=r" (stat));

    return stat;
}

/**
 * \brief     This API is called when the CPU is aborted or during execution
 *            of any undefined instruction. Both IRQ and FIQ will be disabled
 *            when the CPU gets an abort and calls this API. 
 *
 * \param     None.
 *
 * \return    None.
 *
 * Note : The user can perform error handling such as an immediate reset 
 *        inside this API if required.
 **/
extern "C" void CPUAbortHandler(void)
{
  const std::uint32_t faulttype = CPUReadDFSR();

  GPIO1->CLEARDATAOUT = 0x01E00000u;
  GPIO1->SETDATAOUT   = (faulttype & 0x0Fu) << 21u;
}

/*
**
** Wrapper function for the IRQ status
**
*/
extern "C" std::uint32_t CPUIntStatus(void)
{
  volatile std::uint32_t stat;

  /* IRQ and FIQ in CPSR */
  asm volatile("    mrs     r0, CPSR\n\t"
               "    and     %[result], r0, #0xC0" : [result] "=r" (stat));

  return stat;
}

/*
**
** Wrapper function for the IRQ disable function
**
*/
extern "C" void CPUirqd(void)
{
  /* Disable IRQ in CPSR */
  asm volatile("    mrs     r0, CPSR\n\t"
               "    orr     r0, #0x80\n\t"
               "    msr     CPSR, r0");
}

/*
**
** Wrapper function for the IRQ enable function
**
*/
extern "C" void CPUirqe(void)
{
  /* Enable IRQ in CPSR */
  asm volatile("    mrs     r0, CPSR\n\t"
               "    bic     r0, #0x80\n\t"
               "    msr     CPSR, r0");
}

/*
**
** Wrapper function for the FIQ disable function
**
*/
extern "C" void CPUfiqd(void)
{
  /* Disable FIQ in CPSR */
  asm volatile("    mrs     r0, CPSR\n\t"
               "    orr     r0, #0x40\n\t"
               "    msr     CPSR, r0");
}

/*
**
** Wrapper function for the FIQ enable function
**
*/
extern "C" void CPUfiqe(void)
{
  /* Enable FIQ in CPSR */
  asm volatile("    mrs     r0, CPSR\n\t"
               "    bic     r0, #0x40\n\t"
               "    msr     CPSR, r0");
}
