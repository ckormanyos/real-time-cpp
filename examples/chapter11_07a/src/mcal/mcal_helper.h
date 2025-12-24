///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
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

  constexpr auto nop_maker_switchover_to_loop = static_cast<std::uint_fast16_t>(UINT8_C(16));

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> std::enable_if_t<(nop_count == static_cast<std::uint_fast16_t>(UINT8_C(0))), void> { }

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> std::enable_if_t<(nop_count == static_cast<std::uint_fast16_t>(UINT8_C(1))), void>
  {
    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> std::enable_if_t<(   (nop_count >  static_cast<std::uint_fast16_t>(UINT8_C(1)))
                                        && (nop_count <= nop_maker_switchover_to_loop)), void>
  {
    nop_maker<static_cast<std::uint_fast16_t>(nop_count - static_cast<std::uint_fast16_t>(UINT8_C(1)))>();

    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  auto nop_maker() -> std::enable_if_t<(nop_count > nop_maker_switchover_to_loop), void>
  {
    for(auto i = static_cast<std::uint_fast16_t>(UINT8_C(0)); i < nop_count; ++i)
    {
      mcal::cpu::nop();
    }
  }

  template<const bool has_disable_enable_interrupts>
  auto disable_all_interrupts(const bool = has_disable_enable_interrupts,
                              const typename std::enable_if<(has_disable_enable_interrupts == true)>::type* = nullptr)
    -> void
  {
    mcal::irq::disable_all();
  }

  template<const bool has_disable_enable_interrupts>
  auto enable_all_interrupts(const bool = has_disable_enable_interrupts,
                             const typename std::enable_if<(has_disable_enable_interrupts == true)>::type* = nullptr)
    -> void
  {
    mcal::irq::enable_all();
  }

  template<const bool has_disable_enable_interrupts>
  auto disable_all_interrupts(const bool = has_disable_enable_interrupts,
                              const typename std::enable_if<(has_disable_enable_interrupts == false)>::type* = nullptr) -> void { }

  template<const bool has_disable_enable_interrupts>
  auto enable_all_interrupts(const bool = has_disable_enable_interrupts,
                             const typename std::enable_if<(has_disable_enable_interrupts == false)>::type* = nullptr) -> void { }

  } } // namespace mcal::helper

#endif // MCAL_HELPER_2020_05_21_H
