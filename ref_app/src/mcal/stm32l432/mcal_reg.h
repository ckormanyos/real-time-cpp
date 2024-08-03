///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
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
      // Global base addresses.
      constexpr std::uint32_t periph_base        { UINT32_C(0x40000000) };
      constexpr std::uint32_t scs_base           { UINT32_C(0xE000E000) };

      // Individual unit base addresses.
      // TBD: Implement needed regs.
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
