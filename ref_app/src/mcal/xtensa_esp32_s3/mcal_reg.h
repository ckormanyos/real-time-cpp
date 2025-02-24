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
      namespace system
      {
        constexpr std::uint32_t system_base                                    { UINT32_C(0x600C0000) };

        constexpr std::uint32_t core_1_control_0                               { system_base + UINT32_C(0x00000000) };
        constexpr std::uint32_t core_1_control_1                               { system_base + UINT32_C(0x00000004) };
        constexpr std::uint32_t cpu_peri_clk_en                                { system_base + UINT32_C(0x00000008) };
        constexpr std::uint32_t cpu_peri_rst_en                                { system_base + UINT32_C(0x0000000C) };
        constexpr std::uint32_t cpu_per_conf                                   { system_base + UINT32_C(0x00000010) };
        constexpr std::uint32_t mem_pd_mask                                    { system_base + UINT32_C(0x00000014) };
        constexpr std::uint32_t perip_clk_en0                                  { system_base + UINT32_C(0x00000018) };
        constexpr std::uint32_t perip_clk_en1                                  { system_base + UINT32_C(0x0000001C) };
        constexpr std::uint32_t perip_rst_en0                                  { system_base + UINT32_C(0x00000020) };
        constexpr std::uint32_t perip_rst_en1                                  { system_base + UINT32_C(0x00000024) };
        constexpr std::uint32_t bt_lpck_div_int                                { system_base + UINT32_C(0x00000028) };
        constexpr std::uint32_t bt_lpck_div_frac                               { system_base + UINT32_C(0x0000002C) };
        constexpr std::uint32_t cpu_intr_from_cpu_0                            { system_base + UINT32_C(0x00000030) };
        constexpr std::uint32_t cpu_intr_from_cpu_1                            { system_base + UINT32_C(0x00000034) };
        constexpr std::uint32_t cpu_intr_from_cpu_2                            { system_base + UINT32_C(0x00000038) };
        constexpr std::uint32_t cpu_intr_from_cpu_3                            { system_base + UINT32_C(0x0000003C) };
        constexpr std::uint32_t rsa_pd_ctrl                                    { system_base + UINT32_C(0x00000040) };
        constexpr std::uint32_t edma_ctrl                                      { system_base + UINT32_C(0x00000044) };
        constexpr std::uint32_t cache_control                                  { system_base + UINT32_C(0x00000048) };
        constexpr std::uint32_t external_device_encrypt_decrypt_control        { system_base + UINT32_C(0x0000004C) };
        constexpr std::uint32_t rtc_fastmem_config                             { system_base + UINT32_C(0x00000050) };
        constexpr std::uint32_t rtc_fastmem_crc                                { system_base + UINT32_C(0x00000054) };
        constexpr std::uint32_t redundant_eco_ctrl                             { system_base + UINT32_C(0x00000058) };
        constexpr std::uint32_t clock_gate                                     { system_base + UINT32_C(0x0000005C) };
        constexpr std::uint32_t sysclk_conf                                    { system_base + UINT32_C(0x00000060) };



      } // namespace system
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2025_02_22_H
