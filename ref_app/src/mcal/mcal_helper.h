///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_HELPER_2020_05_21_H
  #define MCAL_HELPER_2020_05_21_H

  #include <mcal_cpu.h>
  #include <mcal_irq.h>

  #include <cstdint>
  #include <type_traits>

  namespace mcal { namespace helper {

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> typename std::enable_if<(1U < nop_count) && (nop_count <= 12U), void>::type
  {
    nop_maker<nop_count - 1U>();

    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> typename std::enable_if<(nop_count == 1U), void>::type
  {
    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> typename std::enable_if<(nop_count == 0U), void>::type
  {
  }

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> typename std::enable_if<(12U < nop_count), void>::type
  {
    for(std::uint_fast16_t i = 0U; i < nop_count; ++i)
    {
      mcal::cpu::nop();
    }
  }

  template<const bool has_disable_enable_interrupts>
  auto disable_all_interrupts(const bool = has_disable_enable_interrupts,
                              const typename std::enable_if<has_disable_enable_interrupts>::type* = nullptr) noexcept -> void
  {
    mcal::irq::disable_all();
  }

  template<const bool has_disable_enable_interrupts>
  auto enable_all_interrupts(const bool = has_disable_enable_interrupts,
                             const typename std::enable_if<has_disable_enable_interrupts>::type* = nullptr) noexcept -> void
  {
    mcal::irq::enable_all();
  }

  template<const bool has_disable_enable_interrupts>
  auto disable_all_interrupts(const bool = has_disable_enable_interrupts,
                              const typename std::enable_if<(!has_disable_enable_interrupts)>::type* = nullptr) noexcept -> void { }

  template<const bool has_disable_enable_interrupts>
  auto enable_all_interrupts(const bool = has_disable_enable_interrupts,
                             const typename std::enable_if<(!has_disable_enable_interrupts)>::type* = nullptr) noexcept -> void { }

  } } // namespace mcal::helper

#endif // MCAL_HELPER_2020_05_21_H
