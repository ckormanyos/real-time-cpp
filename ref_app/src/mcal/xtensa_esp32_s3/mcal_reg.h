///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2025_02_22_H
  #define MCAL_REG_2025_02_22_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      constexpr std::uint32_t dummy_reg { UINT32_C(0xF0000000) };
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2025_02_22_H
