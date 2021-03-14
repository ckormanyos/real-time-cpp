///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_HELPER_2020_05_21_H_
  #define MCAL_HELPER_2020_05_21_H_

  #include <cstdint>
  #include <type_traits>

  #include <mcal_cpu.h>
  #include <mcal_irq.h>

  namespace mcal { namespace helper {

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(1U < nop_count) && (nop_count <= 12U), void>::type nop_maker()
  {
    nop_maker<nop_count - 1U>();

    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 1U), void>::type nop_maker() { mcal::cpu::nop(); }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 0U), void>::type nop_maker() { }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(12U < nop_count), void>::type nop_maker()
  {
    for(std::uint_fast16_t i = 0U; i < nop_count; ++i)
    {
      mcal::cpu::nop();
    }
  }

  template<const bool has_disable_enable_interrupts>
  void disable_all_interrupts(const bool = has_disable_enable_interrupts,
                              const typename std::enable_if<(has_disable_enable_interrupts == true)>::type* = nullptr) noexcept
  {
    mcal::irq::disable_all();
  }

  template<const bool has_disable_enable_interrupts>
  void enable_all_interrupts(const bool = has_disable_enable_interrupts,
                             const typename std::enable_if<(has_disable_enable_interrupts == true)>::type* = nullptr) noexcept
  {
    mcal::irq::enable_all();
  }

  template<const bool has_disable_enable_interrupts>
  void disable_all_interrupts(const bool = has_disable_enable_interrupts,
                              const typename std::enable_if<(has_disable_enable_interrupts == false)>::type* = nullptr) noexcept { }

  template<const bool has_disable_enable_interrupts>
  void enable_all_interrupts(const bool = has_disable_enable_interrupts,
                             const typename std::enable_if<(has_disable_enable_interrupts == false)>::type* = nullptr) noexcept { }

  } } // namespace mcal::helper

#endif // MCAL_HELPER_2020_05_21_H_
