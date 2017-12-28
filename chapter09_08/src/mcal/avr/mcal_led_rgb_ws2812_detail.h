///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_WS2812_DETAIL_2017_11_18_H_
  #define MCAL_LED_RGB_WS2812_DETAIL_2017_11_18_H_

  #include <cstdint>

  #include <mcal_cpu.h>

  namespace mcal { namespace led { namespace detail {

  template<const std::uint_fast8_t nop_count>
  struct nop_maker
  {
    static void nops()
    {
      mcal::cpu::nop();

      nop_maker<nop_count - UINT8_C(1)>::nops();
    }
  };

  template<>
  struct nop_maker<UINT8_C(0)>
  {
    static void nops() { }
  };

  } } } // namespace mcal::led::detail

#endif // MCAL_LED_RGB_WS2812_DETAIL_2017_11_18_H_
