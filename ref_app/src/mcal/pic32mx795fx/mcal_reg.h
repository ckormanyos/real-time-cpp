///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_REG_2010_04_10_H_
  #define _MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // System registers.
      constexpr std::uint32_t ddpcon   = UINT32_C(0xBF80F200);   // 32-bit register.

      // ADC registers.
      constexpr std::uint32_t ad1pcfg  = UINT32_C(0xBF809060);   // 32-bit register.

      // Port registers.
      constexpr std::uint32_t trisa    = UINT32_C(0xBF886000);   // 32-bit register.
      constexpr std::uint32_t porta    = UINT32_C(0xBF886010);   // 32-bit register.
      constexpr std::uint32_t lata     = UINT32_C(0xBF886020);   // 32-bit register.
      constexpr std::uint32_t odca     = UINT32_C(0xBF886030);   // 32-bit register.

      constexpr std::uint32_t trisb    = UINT32_C(0xBF886040);   // 32-bit register.
      constexpr std::uint32_t portb    = UINT32_C(0xBF886050);   // 32-bit register.
      constexpr std::uint32_t latb     = UINT32_C(0xBF886060);   // 32-bit register.
      constexpr std::uint32_t odcb     = UINT32_C(0xBF886070);   // 32-bit register.

      constexpr std::uint32_t trisc    = UINT32_C(0xBF886080);   // 32-bit register.
      constexpr std::uint32_t portc    = UINT32_C(0xBF886090);   // 32-bit register.
      constexpr std::uint32_t latc     = UINT32_C(0xBF8860A0);   // 32-bit register.
      constexpr std::uint32_t odcc     = UINT32_C(0xBF8860B0);   // 32-bit register.

      constexpr std::uint32_t trisd    = UINT32_C(0xBF8860C0);   // 32-bit register.
      constexpr std::uint32_t portd    = UINT32_C(0xBF8860D0);   // 32-bit register.
      constexpr std::uint32_t latd     = UINT32_C(0xBF8860E0);   // 32-bit register.
      constexpr std::uint32_t odcd     = UINT32_C(0xBF8860F0);   // 32-bit register.

      constexpr std::uint32_t trise    = UINT32_C(0xBF886100);   // 32-bit register.
      constexpr std::uint32_t porte    = UINT32_C(0xBF886110);   // 32-bit register.
      constexpr std::uint32_t late     = UINT32_C(0xBF886120);   // 32-bit register.
      constexpr std::uint32_t odce     = UINT32_C(0xBF886130);   // 32-bit register.

      constexpr std::uint32_t trisf    = UINT32_C(0xBF886140);   // 32-bit register.
      constexpr std::uint32_t portf    = UINT32_C(0xBF886150);   // 32-bit register.
      constexpr std::uint32_t latf     = UINT32_C(0xBF886160);   // 32-bit register.
      constexpr std::uint32_t odcf     = UINT32_C(0xBF886170);   // 32-bit register.

      constexpr std::uint32_t trisg    = UINT32_C(0xBF886180);   // 32-bit register.
      constexpr std::uint32_t portg    = UINT32_C(0xBF886190);   // 32-bit register.
      constexpr std::uint32_t latg     = UINT32_C(0xBF8861A0);   // 32-bit register.
      constexpr std::uint32_t odcg     = UINT32_C(0xBF8861B0);   // 32-bit register.

      // Interrupt register.
      constexpr std::uint32_t intcon   = UINT32_C(0xBF881000);   // 32-bit register.
    }
  }
#endif // _MCAL_REG_2010_04_10_H_
