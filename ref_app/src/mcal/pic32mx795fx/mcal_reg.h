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
      // Timer registers.
      constexpr std::uint32_t t1con    = UINT32_C(0xBF800600);   // 32-bit register.
      constexpr std::uint32_t tmr1     = UINT32_C(0xBF800610);   // 32-bit register.
      constexpr std::uint32_t pr1      = UINT32_C(0xBF800620);   // 32-bit register.

      constexpr std::uint32_t t2con    = UINT32_C(0xBF800800);   // 32-bit register.
      constexpr std::uint32_t tmr2     = UINT32_C(0xBF800810);   // 32-bit register.
      constexpr std::uint32_t pr2      = UINT32_C(0xBF800820);   // 32-bit register.

      constexpr std::uint32_t t3con    = UINT32_C(0xBF800A00);   // 32-bit register.
      constexpr std::uint32_t tmr3     = UINT32_C(0xBF800A10);   // 32-bit register.
      constexpr std::uint32_t pr3      = UINT32_C(0xBF800A20);   // 32-bit register.

      constexpr std::uint32_t t4con    = UINT32_C(0xBF800C00);   // 32-bit register.
      constexpr std::uint32_t tmr4     = UINT32_C(0xBF800C10);   // 32-bit register.
      constexpr std::uint32_t pr4      = UINT32_C(0xBF800C20);   // 32-bit register.

      constexpr std::uint32_t t5con    = UINT32_C(0xBF800E00);   // 32-bit register.
      constexpr std::uint32_t tmr5     = UINT32_C(0xBF800E10);   // 32-bit register.
      constexpr std::uint32_t pr5      = UINT32_C(0xBF800E20);   // 32-bit register.

      // ADC registers.
      constexpr std::uint32_t ad1pcfg  = UINT32_C(0xBF809060);   // 32-bit register.

      // Oscillator registers.
      constexpr std::uint32_t osccon   = UINT32_C(0xBF80F000);   // 32-bit register.

      // System registers.
      constexpr std::uint32_t ddpcon   = UINT32_C(0xBF80F200);   // 32-bit register.

      // Interrupt registers.
      constexpr std::uint32_t intcon   = UINT32_C(0xBF881000);   // 32-bit register.
      constexpr std::uint32_t ifs0     = UINT32_C(0xBF881030);   // 32-bit register.
      constexpr std::uint32_t ifs1     = UINT32_C(0xBF881040);   // 32-bit register.
      constexpr std::uint32_t ifs2     = UINT32_C(0xBF881050);   // 32-bit register.
      constexpr std::uint32_t iec0     = UINT32_C(0xBF881060);   // 32-bit register.
      constexpr std::uint32_t iec1     = UINT32_C(0xBF881070);   // 32-bit register.
      constexpr std::uint32_t iec2     = UINT32_C(0xBF881080);   // 32-bit register.
      constexpr std::uint32_t ipc0     = UINT32_C(0xBF881090);   // 32-bit register.
      constexpr std::uint32_t ipc1     = UINT32_C(0xBF8810A0);   // 32-bit register.
      constexpr std::uint32_t ipc2     = UINT32_C(0xBF8810B0);   // 32-bit register.
      constexpr std::uint32_t ipc3     = UINT32_C(0xBF8810C0);   // 32-bit register.
      constexpr std::uint32_t ipc4     = UINT32_C(0xBF8810D0);   // 32-bit register.
      constexpr std::uint32_t ipc5     = UINT32_C(0xBF8810E0);   // 32-bit register.
      constexpr std::uint32_t ipc6     = UINT32_C(0xBF8810F0);   // 32-bit register.
      constexpr std::uint32_t ipc7     = UINT32_C(0xBF880100);   // 32-bit register.
      constexpr std::uint32_t ipc8     = UINT32_C(0xBF880110);   // 32-bit register.
      constexpr std::uint32_t ipc9     = UINT32_C(0xBF880120);   // 32-bit register.
      constexpr std::uint32_t ipc10    = UINT32_C(0xBF880130);   // 32-bit register.
      constexpr std::uint32_t ipc11    = UINT32_C(0xBF880140);   // 32-bit register.
      constexpr std::uint32_t ipc12    = UINT32_C(0xBF880150);   // 32-bit register.

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
    }
  }
#endif // _MCAL_REG_2010_04_10_H_
