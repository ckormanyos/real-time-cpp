///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H
  #define MCAL_REG_2010_04_10_H

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // CLIC (timer) registers.
      constexpr std::uintptr_t clic_ctrl_addr     { UINT32_C(0x02000000) };
      constexpr std::uintptr_t clic_msip          { clic_ctrl_addr + UINT32_C(0x00000000) };
      constexpr std::uintptr_t clic_mtimecmp      { clic_ctrl_addr + UINT32_C(0x00004000) };
      constexpr std::uintptr_t clic_mtime         { clic_ctrl_addr + UINT32_C(0x0000BFF8) };
      constexpr std::uintptr_t clic_clk_gate      { clic_ctrl_addr + UINT32_C(0x007FF000) };

      constexpr std::uintptr_t glb_base           { UINT32_C(0x40000000) };
      constexpr std::uintptr_t gpio_cfgctl0       { glb_base + UINT32_C(0x00000100) };
      constexpr std::uintptr_t gpio_cfgctl1       { glb_base + UINT32_C(0x00000104) };
      constexpr std::uintptr_t gpio_cfgctl2       { glb_base + UINT32_C(0x00000108) };
      constexpr std::uintptr_t gpio_cfgctl3       { glb_base + UINT32_C(0x0000010C) };
      constexpr std::uintptr_t gpio_cfgctl4       { glb_base + UINT32_C(0x00000110) };
      constexpr std::uintptr_t gpio_cfgctl5       { glb_base + UINT32_C(0x00000114) };
      constexpr std::uintptr_t gpio_cfgctl6       { glb_base + UINT32_C(0x00000118) };
      constexpr std::uintptr_t gpio_cfgctl7       { glb_base + UINT32_C(0x0000011C) };
      constexpr std::uintptr_t gpio_cfgctl8       { glb_base + UINT32_C(0x00000120) };
      constexpr std::uintptr_t gpio_cfgctl9       { glb_base + UINT32_C(0x00000124) };
      constexpr std::uintptr_t gpio_cfgctl10      { glb_base + UINT32_C(0x00000128) };
      constexpr std::uintptr_t gpio_cfgctl11      { glb_base + UINT32_C(0x0000012C) };
      constexpr std::uintptr_t gpio_cfgctl12      { glb_base + UINT32_C(0x00000130) };
      constexpr std::uintptr_t gpio_cfgctl13      { glb_base + UINT32_C(0x00000134) };
      constexpr std::uintptr_t gpio_cfgctl14      { glb_base + UINT32_C(0x00000138) };
      constexpr std::uintptr_t gpio_cfgctl30      { glb_base + UINT32_C(0x00000180) };
      constexpr std::uintptr_t gpio_cfgctl31      { glb_base + UINT32_C(0x00000184) };
      constexpr std::uintptr_t gpio_cfgctl32      { glb_base + UINT32_C(0x00000188) };
      constexpr std::uintptr_t gpio_cfgctl33      { glb_base + UINT32_C(0x0000018C) };
      constexpr std::uintptr_t gpio_cfgctl34      { glb_base + UINT32_C(0x00000190) };
      constexpr std::uintptr_t gpio_cfgctl35      { glb_base + UINT32_C(0x00000194) };
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H
