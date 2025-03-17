///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2025_03_15_H
  #define MCAL_REG_2025_03_15_H

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

      namespace rtc_cntl
      {
        constexpr std::uint32_t rtc_cntl_base                                  { UINT32_C(0x60008000) };
        constexpr std::uint32_t options0                                       { rtc_cntl_base + UINT32_C(0x00000000) };
        constexpr std::uint32_t slp_timer0                                     { rtc_cntl_base + UINT32_C(0x00000004) };
        constexpr std::uint32_t slp_timer1                                     { rtc_cntl_base + UINT32_C(0x00000008) };
        constexpr std::uint32_t time_update                                    { rtc_cntl_base + UINT32_C(0x0000000C) };
        constexpr std::uint32_t time_low0                                      { rtc_cntl_base + UINT32_C(0x00000010) };
        constexpr std::uint32_t time_high0                                     { rtc_cntl_base + UINT32_C(0x00000014) };
        constexpr std::uint32_t state0                                         { rtc_cntl_base + UINT32_C(0x00000018) };
        constexpr std::uint32_t timer1                                         { rtc_cntl_base + UINT32_C(0x0000001C) };
        constexpr std::uint32_t timer2                                         { rtc_cntl_base + UINT32_C(0x00000020) };
        constexpr std::uint32_t timer3                                         { rtc_cntl_base + UINT32_C(0x00000024) };
        constexpr std::uint32_t timer4                                         { rtc_cntl_base + UINT32_C(0x00000028) };
        constexpr std::uint32_t timer5                                         { rtc_cntl_base + UINT32_C(0x0000002C) };
        constexpr std::uint32_t timer6                                         { rtc_cntl_base + UINT32_C(0x00000030) };
        constexpr std::uint32_t ana_conf                                       { rtc_cntl_base + UINT32_C(0x00000034) };
        constexpr std::uint32_t reset_state                                    { rtc_cntl_base + UINT32_C(0x00000038) };
        constexpr std::uint32_t wakeup_state                                   { rtc_cntl_base + UINT32_C(0x0000003C) };
        constexpr std::uint32_t int_ena_rtc                                    { rtc_cntl_base + UINT32_C(0x00000040) };
        constexpr std::uint32_t int_raw_rtc                                    { rtc_cntl_base + UINT32_C(0x00000044) };
        constexpr std::uint32_t int_st_rtc                                     { rtc_cntl_base + UINT32_C(0x00000048) };
        constexpr std::uint32_t int_clr_rtc                                    { rtc_cntl_base + UINT32_C(0x0000004C) };
        constexpr std::uint32_t store0                                         { rtc_cntl_base + UINT32_C(0x00000050) };
        constexpr std::uint32_t store1                                         { rtc_cntl_base + UINT32_C(0x00000054) };
        constexpr std::uint32_t store2                                         { rtc_cntl_base + UINT32_C(0x00000058) };
        constexpr std::uint32_t store3                                         { rtc_cntl_base + UINT32_C(0x0000005C) };
        constexpr std::uint32_t ext_xtl_conf                                   { rtc_cntl_base + UINT32_C(0x00000060) };
        constexpr std::uint32_t ext_wakeup_conf                                { rtc_cntl_base + UINT32_C(0x00000064) };
        constexpr std::uint32_t slp_reject_conf                                { rtc_cntl_base + UINT32_C(0x00000068) };
        constexpr std::uint32_t cpu_period_conf                                { rtc_cntl_base + UINT32_C(0x0000006C) };
        constexpr std::uint32_t sdio_act_conf                                  { rtc_cntl_base + UINT32_C(0x00000070) };
        constexpr std::uint32_t clk_conf                                       { rtc_cntl_base + UINT32_C(0x00000074) };
        constexpr std::uint32_t slow_clk_conf                                  { rtc_cntl_base + UINT32_C(0x00000078) };
        constexpr std::uint32_t sdio_conf                                      { rtc_cntl_base + UINT32_C(0x0000007C) };
        constexpr std::uint32_t bias_conf                                      { rtc_cntl_base + UINT32_C(0x00000080) };
        constexpr std::uint32_t rtc                                            { rtc_cntl_base + UINT32_C(0x00000084) };
        constexpr std::uint32_t pwc                                            { rtc_cntl_base + UINT32_C(0x00000088) };
        constexpr std::uint32_t regulator_drv_ctrl                             { rtc_cntl_base + UINT32_C(0x0000008C) };
        constexpr std::uint32_t dig_pwc                                        { rtc_cntl_base + UINT32_C(0x00000090) };
        constexpr std::uint32_t dig_iso                                        { rtc_cntl_base + UINT32_C(0x00000094) };
        constexpr std::uint32_t wdtconfig0                                     { rtc_cntl_base + UINT32_C(0x00000098) };
        constexpr std::uint32_t wdtconfig1                                     { rtc_cntl_base + UINT32_C(0x0000009C) };
        constexpr std::uint32_t wdtconfig2                                     { rtc_cntl_base + UINT32_C(0x000000A0) };
        constexpr std::uint32_t wdtconfig3                                     { rtc_cntl_base + UINT32_C(0x000000A4) };
        constexpr std::uint32_t wdtconfig4                                     { rtc_cntl_base + UINT32_C(0x000000A8) };
        constexpr std::uint32_t wdtfeed                                        { rtc_cntl_base + UINT32_C(0x000000AC) };
        constexpr std::uint32_t wdtwprotect                                    { rtc_cntl_base + UINT32_C(0x000000B0) };
        constexpr std::uint32_t swd_conf                                       { rtc_cntl_base + UINT32_C(0x000000B4) };
        constexpr std::uint32_t swd_wprotect                                   { rtc_cntl_base + UINT32_C(0x000000B8) };
        constexpr std::uint32_t sw_cpu_stall                                   { rtc_cntl_base + UINT32_C(0x000000BC) };
        constexpr std::uint32_t store4                                         { rtc_cntl_base + UINT32_C(0x000000C0) };
        constexpr std::uint32_t store5                                         { rtc_cntl_base + UINT32_C(0x000000C4) };
        constexpr std::uint32_t store6                                         { rtc_cntl_base + UINT32_C(0x000000C8) };
        constexpr std::uint32_t store7                                         { rtc_cntl_base + UINT32_C(0x000000CC) };
        constexpr std::uint32_t low_power_st                                   { rtc_cntl_base + UINT32_C(0x000000D0) };
        constexpr std::uint32_t diag0                                          { rtc_cntl_base + UINT32_C(0x000000D4) };
        constexpr std::uint32_t pad_hold                                       { rtc_cntl_base + UINT32_C(0x000000D8) };
        constexpr std::uint32_t dig_pad_hold                                   { rtc_cntl_base + UINT32_C(0x000000DC) };
        constexpr std::uint32_t ext_wakeup1                                    { rtc_cntl_base + UINT32_C(0x000000E0) };
        constexpr std::uint32_t ext_wakeup1_status                             { rtc_cntl_base + UINT32_C(0x000000E4) };
        constexpr std::uint32_t brown_out                                      { rtc_cntl_base + UINT32_C(0x000000E8) };
        constexpr std::uint32_t time_low1                                      { rtc_cntl_base + UINT32_C(0x000000EC) };
        constexpr std::uint32_t time_high1                                     { rtc_cntl_base + UINT32_C(0x000000F0) };
        constexpr std::uint32_t xtal32k_clk_factor                             { rtc_cntl_base + UINT32_C(0x000000F4) };
        constexpr std::uint32_t xtal32k_conf                                   { rtc_cntl_base + UINT32_C(0x000000F8) };
        constexpr std::uint32_t ulp_cp_timer                                   { rtc_cntl_base + UINT32_C(0x000000FC) };
        constexpr std::uint32_t ulp_cp_ctrl                                    { rtc_cntl_base + UINT32_C(0x00000100) };
        constexpr std::uint32_t cocpu_ctrl                                     { rtc_cntl_base + UINT32_C(0x00000104) };
      } // namespace rtc_cntl

      namespace timg0
      {
        constexpr std::uint32_t timg0_base                                     { UINT32_C(0x6001F000) };
        constexpr std::uint32_t t0config                                       { timg0_base + UINT32_C(0x00000000) };
        constexpr std::uint32_t t0lo                                           { timg0_base + UINT32_C(0x00000004) };
        constexpr std::uint32_t t0hi                                           { timg0_base + UINT32_C(0x00000008) };
        constexpr std::uint32_t t0update                                       { timg0_base + UINT32_C(0x0000000C) };
        constexpr std::uint32_t t0alarmlo                                      { timg0_base + UINT32_C(0x00000010) };
        constexpr std::uint32_t t0alarmhi                                      { timg0_base + UINT32_C(0x00000014) };
        constexpr std::uint32_t t0loadlo                                       { timg0_base + UINT32_C(0x00000018) };
        constexpr std::uint32_t t0loadhi                                       { timg0_base + UINT32_C(0x0000001C) };
        constexpr std::uint32_t t0load                                         { timg0_base + UINT32_C(0x00000020) };
        constexpr std::uint32_t reserved0_00                                   { timg0_base + UINT32_C(0x00000024) };
        constexpr std::uint32_t reserved0_01                                   { timg0_base + UINT32_C(0x00000028) };
        constexpr std::uint32_t reserved0_02                                   { timg0_base + UINT32_C(0x0000002C) };
        constexpr std::uint32_t reserved0_03                                   { timg0_base + UINT32_C(0x00000030) };
        constexpr std::uint32_t reserved0_04                                   { timg0_base + UINT32_C(0x00000034) };
        constexpr std::uint32_t reserved0_05                                   { timg0_base + UINT32_C(0x00000038) };
        constexpr std::uint32_t reserved0_06                                   { timg0_base + UINT32_C(0x0000003C) };
        constexpr std::uint32_t reserved0_07                                   { timg0_base + UINT32_C(0x00000040) };
        constexpr std::uint32_t reserved0_08                                   { timg0_base + UINT32_C(0x00000044) };
        constexpr std::uint32_t wdtconfig0                                     { timg0_base + UINT32_C(0x00000048) };
        constexpr std::uint32_t wdtconfig1                                     { timg0_base + UINT32_C(0x0000004C) };
        constexpr std::uint32_t wdtconfig2                                     { timg0_base + UINT32_C(0x00000050) };
        constexpr std::uint32_t wdtconfig3                                     { timg0_base + UINT32_C(0x00000054) };
        constexpr std::uint32_t wdtconfig4                                     { timg0_base + UINT32_C(0x00000058) };
        constexpr std::uint32_t wdtconfig5                                     { timg0_base + UINT32_C(0x0000005C) };
        constexpr std::uint32_t wdtfeed                                        { timg0_base + UINT32_C(0x00000060) };
        constexpr std::uint32_t wdtwprotect                                    { timg0_base + UINT32_C(0x00000064) };
        constexpr std::uint32_t rtccalicfg                                     { timg0_base + UINT32_C(0x00000068) };
        constexpr std::uint32_t rtccalicfg1                                    { timg0_base + UINT32_C(0x0000006C) };
        constexpr std::uint32_t int_ena_timers                                 { timg0_base + UINT32_C(0x00000070) };
        constexpr std::uint32_t int_raw_timers                                 { timg0_base + UINT32_C(0x00000074) };
        constexpr std::uint32_t int_st_timers                                  { timg0_base + UINT32_C(0x00000078) };
        constexpr std::uint32_t int_clr_timers                                 { timg0_base + UINT32_C(0x0000007C) };
        constexpr std::uint32_t rtccalicfg2                                    { timg0_base + UINT32_C(0x00000080) };
        constexpr std::uint32_t reserved1_00                                   { timg0_base + UINT32_C(0x00000084) };
        constexpr std::uint32_t reserved1_01                                   { timg0_base + UINT32_C(0x00000088) };
        constexpr std::uint32_t reserved1_02                                   { timg0_base + UINT32_C(0x0000008C) };
        constexpr std::uint32_t t1config                                       { timg0_base + UINT32_C(0x00000090) };
        constexpr std::uint32_t t1lo                                           { timg0_base + UINT32_C(0x00000094) };
        constexpr std::uint32_t t1hi                                           { timg0_base + UINT32_C(0x00000098) };
        constexpr std::uint32_t t1update                                       { timg0_base + UINT32_C(0x0000009C) };
        constexpr std::uint32_t t1alarmlo                                      { timg0_base + UINT32_C(0x000000A0) };
        constexpr std::uint32_t t1alarmhi                                      { timg0_base + UINT32_C(0x000000A4) };
        constexpr std::uint32_t t1loadlo                                       { timg0_base + UINT32_C(0x000000A8) };
        constexpr std::uint32_t t1loadhi                                       { timg0_base + UINT32_C(0x000000AC) };
        constexpr std::uint32_t t1load                                         { timg0_base + UINT32_C(0x000000B0) };
        constexpr std::uint32_t reserved2_00                                   { timg0_base + UINT32_C(0x000000B4) };
        constexpr std::uint32_t reserved2_01                                   { timg0_base + UINT32_C(0x000000B8) };
        constexpr std::uint32_t reserved2_02                                   { timg0_base + UINT32_C(0x000000BC) };
        constexpr std::uint32_t reserved2_03                                   { timg0_base + UINT32_C(0x000000C0) };
        constexpr std::uint32_t reserved2_04                                   { timg0_base + UINT32_C(0x000000C4) };
        constexpr std::uint32_t reserved2_05                                   { timg0_base + UINT32_C(0x000000C8) };
        constexpr std::uint32_t reserved2_06                                   { timg0_base + UINT32_C(0x000000CC) };
        constexpr std::uint32_t reserved2_07                                   { timg0_base + UINT32_C(0x000000D0) };
        constexpr std::uint32_t reserved2_08                                   { timg0_base + UINT32_C(0x000000D4) };
        constexpr std::uint32_t reserved2_09                                   { timg0_base + UINT32_C(0x000000D8) };
        constexpr std::uint32_t reserved2_10                                   { timg0_base + UINT32_C(0x000000DC) };
        constexpr std::uint32_t reserved2_11                                   { timg0_base + UINT32_C(0x000000E0) };
        constexpr std::uint32_t reserved2_12                                   { timg0_base + UINT32_C(0x000000E4) };
        constexpr std::uint32_t reserved2_13                                   { timg0_base + UINT32_C(0x000000E8) };
        constexpr std::uint32_t reserved2_14                                   { timg0_base + UINT32_C(0x000000EC) };
        constexpr std::uint32_t reserved2_15                                   { timg0_base + UINT32_C(0x000000F0) };
        constexpr std::uint32_t reserved2_16                                   { timg0_base + UINT32_C(0x000000F4) };
        constexpr std::uint32_t ntimers_date                                   { timg0_base + UINT32_C(0x000000F8) };
        constexpr std::uint32_t regclk                                         { timg0_base + UINT32_C(0x000000FC) };
      } // namespace timg0

      namespace gpio
      {
        constexpr std::uint32_t rtc_gpio_base                                  { UINT32_C(0x0000A400) };
        constexpr std::uint32_t rtc_gpio_out_reg                               { rtc_gpio_base + UINT32_C(0x00000000) };
        constexpr std::uint32_t rtc_gpio_enable_reg                            { rtc_gpio_base + UINT32_C(0x0000000C) };
      } // namespace gpio
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2025_03_15_H
