///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <Cpu/Cpu.h>

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

//-----------------------------------------------------------------------------------------
/// \brief  RP2040_MulticoreSync function
///
/// \param  CpuId : The cpu core identifier
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void RP2040_MulticoreSync(uint32_t CpuId)
{
  constexpr std::uint32_t CPU_CORE0_ID { UINT32_C(0) };
  constexpr std::uint32_t CPU_CORE1_ID { UINT32_C(1) };

  constexpr std::uint32_t
    MULTICORE_SYNC_MASK
    {
      std::uint32_t
      {
          std::uint32_t { (1UL << CPU_CORE0_ID) }
        | std::uint32_t { (1UL << CPU_CORE1_ID) }
      }
    };

  static volatile std::uint32_t Cpu_u32MulticoreSync { };

  Cpu_u32MulticoreSync |= (1UL << CpuId);

  while(Cpu_u32MulticoreSync != MULTICORE_SYNC_MASK);
}

//-----------------------------------------------------------------------------------------
/// \brief  RP2040_InitCore function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
void RP2040_InitCore(void)
{
  // We came here from the RP2040 BootRom and SBL.
  // Reset core1 to start from a known state.

  PSM->FRCE_OFF.bit.proc1 = 1U;

  while((PSM->DONE.bit.proc1 == 1U));

  PSM->FRCE_OFF.bit.proc1 = 0U;

  while((PSM->DONE.bit.proc1 != 1U));

  // Reset peripheral to start from a known state.
  RESETS->RESET.bit.io_bank0   = 1U;
  RESETS->RESET.bit.pads_bank0 = 1U;

  while((RESETS->RESET_DONE.bit.io_bank0 == 1U) || (RESETS->RESET_DONE.bit.pads_bank0 == 1U));

  RESETS->RESET.bit.io_bank0   = 0U;
  RESETS->RESET.bit.pads_bank0 = 0U;

  while((RESETS->RESET_DONE.bit.io_bank0 == 0U) || (RESETS->RESET_DONE.bit.pads_bank0 == 0U));
}

//-----------------------------------------------------------------------------------------
/// \brief  RP2040_StartCore1 function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
extern "C"
bool RP2040_StartCore1(void)
{
  extern std::uint32_t __INTVECT_Core1[2];

  // Flush the mailbox.
  while(SIO->FIFO_ST.bit.VLD == 1UL)
  {
    static_cast<void>(SIO->FIFO_RD);
  }

  // Send 0 to wake up core 1.
  SIO->FIFO_WR = 0;
  asm volatile("sev");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != 0U)
  {
    return false;
  }

  // Send 1 to synchronize with core 1.
  SIO->FIFO_WR = 1;
  asm volatile("sev");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != 1U)
  {
    return false;
  }

  // Send the VTOR address for core 1.
  SIO->FIFO_WR = reinterpret_cast<std::uint32_t>(&__INTVECT_Core1[0U]);
  asm volatile("sev");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != reinterpret_cast<std::uint32_t>(&__INTVECT_Core1[0U]))
  {
    return false;
  }

  // Send the stack pointer value for core 1.
  SIO->FIFO_WR = reinterpret_cast<std::uint32_t>(__INTVECT_Core1[0U]);
  asm volatile("sev");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != reinterpret_cast<std::uint32_t>(__INTVECT_Core1[0U]))
  {
    return false;
  }

  // Send the reset handler for core 1.
  SIO->FIFO_WR = reinterpret_cast<std::uint32_t>(__INTVECT_Core1[1U]);
  asm volatile("sev");

  while(SIO->FIFO_ST.bit.VLD != 1UL);

  if(SIO->FIFO_RD != reinterpret_cast<std::uint32_t>(__INTVECT_Core1[1U]))
  {
    return false;
  }

  // Clear the sticky bits of the FIFO_ST on core 0.
  // Note: Core 0 has called us to get here so these are,
  // in fact, the FIFO_ST sticky bits on core 0.
  SIO->FIFO_ST.reg = 0xFFU;

  return true;
}

void mcal::cpu::init()
{
  ::RP2040_InitCore();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
