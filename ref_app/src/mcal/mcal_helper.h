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

  template<const std::uint8_t nop_count>
  struct nop_maker
  {
    static void execute_n() noexcept
    {
      nop_maker<nop_count - 1U>::execute_n();

      mcal::cpu::nop();
    }
  };

  template<>
  struct nop_maker<UINT8_C(1)>
  {
    static void execute_n() noexcept { mcal::cpu::nop(); }
  };

  template<>
  struct nop_maker<UINT8_C(0)>
  {
    static void execute_n() noexcept { }
  };

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
