///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_cpu_rp2350.h>
#include <mcal_reg.h>

#include <cstddef>
#include <cstdint>

extern "C"
{
  auto arch_spin_lock  (std::uint32_t* lock)-> void;
  auto arch_spin_unlock(std::uint32_t* lock)-> void;
}

namespace
{
           std::uint32_t u32MulticoreLock;
  volatile std::uint32_t u32MulticoreSync;

  inline auto core_arch_send_event_inst() noexcept -> void { asm volatile ("sev"); }
}

void mcal::cpu::rp2350::multicore_sync(std::uint32_t CpuId)
{
  /* aquire the multicore lock */
  arch_spin_lock(&u32MulticoreLock);

  u32MulticoreSync |= std::uint32_t { 1UL << CpuId };

  /* release the multicore lock */
  arch_spin_unlock(&u32MulticoreLock);

  while(u32MulticoreSync != MULTICORE_SYNC_MASK) { mcal::cpu::nop(); }
}

extern "C"
{
  extern const std::uint32_t __INTVECT_Core1[static_cast<std::size_t>(UINT8_C(2))];
}

namespace local {

auto sio_fifo_write_verify(const std::uint32_t value) -> bool;

auto sio_fifo_write_verify(const std::uint32_t value) -> bool
{
  // HW_PER_SIO->FIFO_WR.reg = value;
  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set
  (
    mcal::reg::sio_fifo_wr,
    value
  );

  core_arch_send_event_inst();

  // while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::sio_fifo_st,
                                      UINT32_C(0)>::bit_get()) { mcal::cpu::nop(); }

  // return (HW_PER_SIO->FIFO_RD.reg != 1U);

  return
  (
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::sio_fifo_rd>::reg_get() == value
  );
}

} // namespace local

auto mcal::cpu::rp2350::start_core1() -> bool
{
  // Flush the mailbox.

  // while(HW_PER_SIO->FIFO_ST.bit.VLD == 1UL) { static_cast<void>(HW_PER_SIO->FIFO_RD.reg); }
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

  // Send the VTOR address.
  local::sio_fifo_write_verify(reinterpret_cast<std::uint32_t>(&__INTVECT_Core1[0U]));

  // Send the stack pointer value.
  local::sio_fifo_write_verify(reinterpret_cast<std::uint32_t>(__INTVECT_Core1[0U]));

  // Send the reset handler address.
  local::sio_fifo_write_verify(reinterpret_cast<std::uint32_t>(__INTVECT_Core1[1U]));

  // Clear the stiky bits FIFO_ST on core 0.

  // HW_PER_SIO->FIFO_ST.reg = 0xFFu;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::sio_fifo_st,
                               std::uint32_t { UINT32_C(0xFF) }>::reg_set();

  return true;
}
