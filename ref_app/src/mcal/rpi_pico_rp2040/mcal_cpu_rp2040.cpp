///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_cpu_rp2040.h>
#include <mcal_reg.h>

extern "C"
{
  extern const std::uint32_t __INTVECT_Core1[static_cast<std::size_t>(UINT8_C(2))];
}

namespace local {

auto sio_fifo_write_verify(const std::uint32_t value) -> bool;

auto sio_fifo_write_verify(const std::uint32_t value) -> bool
{
  // SIO->FIFO_WR = value;
  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set
  (
    mcal::reg::sio_fifo_wr,
    value
  );

  asm volatile("sev");

  // while(SIO->FIFO_ST.bit.VLD != 1UL);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::sio_fifo_st,
                                      UINT32_C(0)>::bit_get()) { mcal::cpu::nop(); }

  // return (SIO->FIFO_RD == value);

  return
  (
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::sio_fifo_rd>::reg_get() == value
  );
}

} // namespace local

auto mcal::cpu::rp2040::multicore_sync(const std::uint32_t CpuId) -> void
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

  static volatile std::uint32_t u32MulticoreSync;

  u32MulticoreSync |= std::uint32_t { 1UL << CpuId };

  while(u32MulticoreSync != MULTICORE_SYNC_MASK)
  {
    mcal::cpu::nop();
  }
}

auto mcal::cpu::rp2040::start_core1() -> bool
{
  // Flush the mailbox.

  // while(SIO->FIFO_ST.bit.VLD == 1UL) { static_cast<void>(SIO->FIFO_RD); }
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::sio_fifo_st,
                                     UINT32_C(0)>::bit_get())
  {
    static_cast<void>
    (
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::sio_fifo_rd>::reg_get()
    );
  }

  // Send 0 to wake up core 1.
  local::sio_fifo_write_verify(std::uint32_t { UINT32_C(0) });

  // Send 1 to synchronize with core 1.
  local::sio_fifo_write_verify(std::uint32_t { UINT32_C(1) });

  // Send the VTOR address for core 1.
  local::sio_fifo_write_verify(reinterpret_cast<std::uint32_t>(reinterpret_cast<std::uint32_t>(&__INTVECT_Core1[0U])));

  // Send the stack pointer value for core 1.
  local::sio_fifo_write_verify(__INTVECT_Core1[0U]);

  // Send the reset handler address for core 1.
  local::sio_fifo_write_verify(__INTVECT_Core1[1U]);

  // Clear the sticky bits of the FIFO_ST on core 0.
  // Note: Core 0 has called us to get here so these are,
  // in fact, the FIFO_ST sticky bits on core 0.

  // SIO->FIFO_ST.reg = 0xFFU;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::sio_fifo_st,
                               std::uint32_t { UINT32_C(0xFF) }>::reg_set();

  return true;
}
