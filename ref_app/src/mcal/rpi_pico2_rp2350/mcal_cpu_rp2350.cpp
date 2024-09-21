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

extern "C"
{
  auto arch_spin_lock  (std::uint32_t* lock) noexcept -> void;
  auto arch_spin_unlock(std::uint32_t* lock) noexcept -> void;

  extern const std::uint32_t __INTVECT_Core1[static_cast<std::size_t>(UINT8_C(2))];
}

namespace local {

inline auto core_arch_send_event_inst() noexcept -> void { asm volatile ("sev"); }

auto sio_fifo_write_verify(const std::uint32_t value) -> bool;

auto sio_fifo_write_verify(const std::uint32_t value) -> bool
{
  // HW_PER_SIO->FIFO_WR.reg = value;
  mcal::reg::reg_access_dynamic<std::uint32_t, std::uint32_t>::reg_set
  (
    mcal::reg::sio_fifo_wr,
    value
  );

  local::core_arch_send_event_inst();

  // while(HW_PER_SIO->FIFO_ST.bit.VLD != 1UL);
  while(!mcal::reg::reg_access_static<std::uint32_t,
                                      std::uint32_t,
                                      mcal::reg::sio_fifo_st,
                                      UINT32_C(0)>::bit_get()) { mcal::cpu::nop(); }

  // return (HW_PER_SIO->FIFO_RD.reg != value);

  return
  (
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::sio_fifo_rd>::reg_get() == value
  );
}

} // namespace local

auto mcal::cpu::rp2350::multicore_sync(const std::uint32_t cpuid) -> void
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

  static          std::uint32_t u32MulticoreLock { };
  static volatile std::uint32_t u32MulticoreSync { };

  // Acquire the multicore spin-lock.
  arch_spin_lock(&u32MulticoreLock);

  u32MulticoreSync |= std::uint32_t { 1UL << cpuid };

  // Release the multicore spin-lock.
  arch_spin_unlock(&u32MulticoreLock);

  while(u32MulticoreSync != MULTICORE_SYNC_MASK)
  {
    mcal::cpu::nop();
  }
}

auto mcal::cpu::rp2350::start_core1() -> bool
{
  // Flush the mailbox.

  // while(HW_PER_SIO->FIFO_ST.bit.VLD == 1UL) { static_cast<void>(HW_PER_SIO->FIFO_RD.reg); }
  do
  {
    // Perform dummy read(s) of the FIFO-read register.
    static_cast<void>
    (
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::sio_fifo_rd>::reg_get()
    );
  }
  while(mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::sio_fifo_st,
                                     UINT32_C(0)>::bit_get());

  // Send 0 to wake up core 1.
  local::sio_fifo_write_verify(std::uint32_t { UINT32_C(0) });

  // Send 1 to synchronize with core 1.
  local::sio_fifo_write_verify(std::uint32_t { UINT32_C(1) });

  static_assert(sizeof(std::uint32_t) == sizeof(std::uintptr_t), "Error: Pointer/address size mismatch");

  // Send the VTOR address for core 1.
  local::sio_fifo_write_verify(reinterpret_cast<std::uint32_t>(&__INTVECT_Core1[0U]));

  // Send the stack pointer value for core 1.
  local::sio_fifo_write_verify(__INTVECT_Core1[0U]);

  // Send the reset handler address for core 1.
  local::sio_fifo_write_verify(__INTVECT_Core1[1U]);

  // Clear the sticky bits of the FIFO_ST on core 0.
  // Note: Core 0 has called us to get here so these are,
  // in fact, the FIFO_ST sticky bits on core 0.

  // HW_PER_SIO->FIFO_ST.reg = 0xFFu;
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::sio_fifo_st,
                               std::uint32_t { UINT32_C(0xFF) }>::reg_set();

  return true;
}
