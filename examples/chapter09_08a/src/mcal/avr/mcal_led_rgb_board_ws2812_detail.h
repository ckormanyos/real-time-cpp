///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_BOARD_DETAIL_2017_11_18_H
  #define MCAL_LED_RGB_BOARD_DETAIL_2017_11_18_H

  #include <cstdint>

  #include <mcal_cpu.h>

  namespace mcal { namespace led { namespace detail {

  template<const std::uint_fast8_t nop_count>
  struct nop_maker
  {
    static void nops() __attribute__((always_inline))
    {
      mcal::cpu::nop();

      nop_maker<nop_count - UINT8_C(1)>::nops();
    }
  };

  template<>
  struct nop_maker<UINT8_C(0)>
  {
    static void nops() __attribute__((always_inline)) { }
  };

  } } } // namespace mcal::led::detail

#endif // MCAL_LED_RGB_BOARD_DETAIL_2017_11_18_H
