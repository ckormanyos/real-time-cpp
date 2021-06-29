///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
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
  typename std::enable_if<(nop_count == 0U), void>::type nop_maker() noexcept
  {
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 1U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 2U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop();
    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 3U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop();
    mcal::cpu::nop();
    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 4U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop(); mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 5U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 6U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop(); mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 7U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(nop_count == 8U), void>::type nop_maker() noexcept
  {
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
    mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop(); mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(8U < nop_count) && (nop_count <= 16U), void>::type nop_maker() noexcept
  {
    nop_maker<nop_count - 1U>();

    mcal::cpu::nop();
  }

  template<const std::uint_fast16_t nop_count>
  typename std::enable_if<(16U < nop_count), void>::type nop_maker() noexcept
  {
    for(std::uint_fast16_t i = 0U; i < nop_count / 8U; ++i)
    {
      nop_maker<8U>();
    }

    nop_maker<nop_count % 8U>();
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
                              const typename std::enable_if<(has_disable_enable_interrupts == false)>::type* = nullptr) noexcept
  {
  }

  template<const bool has_disable_enable_interrupts>
  void enable_all_interrupts(const bool = has_disable_enable_interrupts,
                             const typename std::enable_if<(has_disable_enable_interrupts == false)>::type* = nullptr) noexcept
  {
  }

  } } // namespace mcal::helper

#endif // MCAL_HELPER_2020_05_21_H_
