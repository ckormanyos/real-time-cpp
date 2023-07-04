///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2022_08_03_H_
  #define MCAL_REG_2022_08_03_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      constexpr auto ccm_analog_pll_arm     = static_cast<std::uint32_t>(UINT32_C(0x400D8000)); // BootROM forced to 0x80002042
      constexpr auto ccm_analog_pll_arm_set = static_cast<std::uint32_t>(UINT32_C(0x400D8004));
      constexpr auto ccm_analog_pll_arm_clr = static_cast<std::uint32_t>(UINT32_C(0x400D8008));
      constexpr auto ccm_analog_pll_arm_tog = static_cast<std::uint32_t>(UINT32_C(0x400D800C));

      constexpr auto ccm_cbcdr              = static_cast<std::uint32_t>(UINT32_C(0x400FC014)); // BootROM forced to 0x000A8200
      constexpr auto ccm_cacrr              = static_cast<std::uint32_t>(UINT32_C(0x400FC010)); // BootROM forced to 0x00000001
      constexpr auto ccm_cbcmr              = static_cast<std::uint32_t>(UINT32_C(0x400FC018)); // BootROM forced to 0x75AE8104

      constexpr auto dcdc_reg0              = static_cast<std::uint32_t>(UINT32_C(0x40080000));
      constexpr auto dcdc_reg3              = static_cast<std::uint32_t>(UINT32_C(0x4008000C));
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2022_08_03_H_
