///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H_
  #define MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Port- and Portmode adresses.
      constexpr std::uint32_t p0    = static_cast<std::uint32_t>(0xFFF00U);
      constexpr std::uint32_t pm0   = static_cast<std::uint32_t>(0xFFF20U);
      constexpr std::uint32_t pu0   = static_cast<std::uint32_t>(0xFFF30U);

      constexpr std::uint32_t p1    = static_cast<std::uint32_t>(0xFFF01U);
      constexpr std::uint32_t pm1   = static_cast<std::uint32_t>(0xFFF21U);
      constexpr std::uint32_t pu1   = static_cast<std::uint32_t>(0xFFF31U);

      constexpr std::uint32_t p2    = static_cast<std::uint32_t>(0xFFF02U);
      constexpr std::uint32_t pm2   = static_cast<std::uint32_t>(0xFFF22U);

      constexpr std::uint32_t p3    = static_cast<std::uint32_t>(0xFFF03U);
      constexpr std::uint32_t pm3   = static_cast<std::uint32_t>(0xFFF23U);
      constexpr std::uint32_t pu3   = static_cast<std::uint32_t>(0xFFF33U);

      constexpr std::uint32_t p4    = static_cast<std::uint32_t>(0xFFF04U);
      constexpr std::uint32_t pm4   = static_cast<std::uint32_t>(0xFFF24U);
      constexpr std::uint32_t pu4   = static_cast<std::uint32_t>(0xFFF34U);

      constexpr std::uint32_t p5    = static_cast<std::uint32_t>(0xFFF05U);
      constexpr std::uint32_t pm5   = static_cast<std::uint32_t>(0xFFF25U);
      constexpr std::uint32_t pu5   = static_cast<std::uint32_t>(0xFFF35U);

      constexpr std::uint32_t p6    = static_cast<std::uint32_t>(0xFFF06U);
      constexpr std::uint32_t pm6   = static_cast<std::uint32_t>(0xFFF26U);

      constexpr std::uint32_t p7    = static_cast<std::uint32_t>(0xFFF07U);
      constexpr std::uint32_t pm7   = static_cast<std::uint32_t>(0xFFF27U);
      constexpr std::uint32_t pu7   = static_cast<std::uint32_t>(0xFFF37U);

      constexpr std::uint32_t p12   = static_cast<std::uint32_t>(0xFFF0CU);
      constexpr std::uint32_t pm12  = static_cast<std::uint32_t>(0xFFF2CU);
      constexpr std::uint32_t pu12  = static_cast<std::uint32_t>(0xFFF3CU);

      // no pm13 register.
      constexpr std::uint32_t p13   = static_cast<std::uint32_t>(0xFFF0DU);

      constexpr std::uint32_t p14   = static_cast<std::uint32_t>(0xFFF0EU);
      constexpr std::uint32_t pm14  = static_cast<std::uint32_t>(0xFFF2EU);
      constexpr std::uint32_t pu14  = static_cast<std::uint32_t>(0xFFF3EU);

      // timer register
      constexpr std::uint32_t tdr00 = static_cast<std::uint32_t>(0xFFF18U);
      constexpr std::uint32_t tcr00 = static_cast<std::uint32_t>(0xF0180U);
      constexpr std::uint32_t tmr00 = static_cast<std::uint32_t>(0xF0190U);

      constexpr std::uint32_t tdr01 = static_cast<std::uint32_t>(0xFFF1AU);
      constexpr std::uint32_t tcr01 = static_cast<std::uint32_t>(0xF0182U);
      constexpr std::uint32_t tmr01 = static_cast<std::uint32_t>(0xF0192U);

      constexpr std::uint32_t tdr02 = static_cast<std::uint32_t>(0xFFF64U);
      constexpr std::uint32_t tcr02 = static_cast<std::uint32_t>(0xF0184U);
      constexpr std::uint32_t tmr02 = static_cast<std::uint32_t>(0xF0194U);

      constexpr std::uint32_t tdr03 = static_cast<std::uint32_t>(0xFFF66U);
      constexpr std::uint32_t tcr03 = static_cast<std::uint32_t>(0xF0186U);
      constexpr std::uint32_t tmr03 = static_cast<std::uint32_t>(0xF0196U);

      constexpr std::uint32_t tdr04 = static_cast<std::uint32_t>(0xFFF68U);
      constexpr std::uint32_t tcr04 = static_cast<std::uint32_t>(0xF0188U);
      constexpr std::uint32_t tmr04 = static_cast<std::uint32_t>(0xF0198U);

      constexpr std::uint32_t tdr05 = static_cast<std::uint32_t>(0xFFF6AU);
      constexpr std::uint32_t tcr05 = static_cast<std::uint32_t>(0xF018AU);
      constexpr std::uint32_t tmr05 = static_cast<std::uint32_t>(0xF019AU);

      constexpr std::uint32_t tdr06 = static_cast<std::uint32_t>(0xFFF6CU);
      constexpr std::uint32_t tcr06 = static_cast<std::uint32_t>(0xF018CU);
      constexpr std::uint32_t tmr06 = static_cast<std::uint32_t>(0xF019CU);

      constexpr std::uint32_t tdr07 = static_cast<std::uint32_t>(0xFFF6EU);
      constexpr std::uint32_t tcr07 = static_cast<std::uint32_t>(0xF018EU);
      constexpr std::uint32_t tmr07 = static_cast<std::uint32_t>(0xF019EU);

      constexpr std::uint32_t to0   = static_cast<std::uint32_t>(0xF01B8U);
      constexpr std::uint32_t to0l  = static_cast<std::uint32_t>(0xF01B8U);
      constexpr std::uint32_t toe0  = static_cast<std::uint32_t>(0xF01BAU);
      constexpr std::uint32_t toe0l = static_cast<std::uint32_t>(0xF01BAU);
      constexpr std::uint32_t tol0  = static_cast<std::uint32_t>(0xF01BCU);
      constexpr std::uint32_t tol0l = static_cast<std::uint32_t>(0xF01BCU);
      constexpr std::uint32_t ts0   = static_cast<std::uint32_t>(0xF01B2U);
      constexpr std::uint32_t ts0l  = static_cast<std::uint32_t>(0xF01B2U);
      constexpr std::uint32_t tps0  = static_cast<std::uint32_t>(0xF01B6U);

      // register for priority of timer channel n.
      constexpr std::uint32_t pr01l = static_cast<std::uint32_t>(0xFFFEAU);
      constexpr std::uint32_t pr11l = static_cast<std::uint32_t>(0xFFFEEU);

      // interrupt mask flag register.
      constexpr std::uint32_t mk2l  = static_cast<std::uint32_t>(0xFFFD4U);
      constexpr std::uint32_t mk2h  = static_cast<std::uint32_t>(0xFFFE5U);
      constexpr std::uint32_t mk0l  = static_cast<std::uint32_t>(0xFFFE4U);
      constexpr std::uint32_t mk1l  = static_cast<std::uint32_t>(0xFFFE6U);
      constexpr std::uint32_t mk1h  = static_cast<std::uint32_t>(0xFFFE7U);

      constexpr std::uint32_t per0  = static_cast<std::uint32_t>(0xF00F0U);
      constexpr std::uint32_t if1l  = static_cast<std::uint32_t>(0xFFFE2U);
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
