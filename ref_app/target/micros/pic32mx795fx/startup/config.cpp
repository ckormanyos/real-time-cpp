///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

namespace crt
{
  namespace config
  {
    constexpr std::uint32_t config0_bit31_reserved_write_zero                      = UINT32_C(0x7FFFFFFF);
    constexpr std::uint32_t config0_code_protect_on                                = UINT32_C(0xEFFFFFFF);
    constexpr std::uint32_t config0_code_protect_off                               = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t config0_bwp_flash_is_not_writable                      = UINT32_C(0xFEFFFFFF);
    constexpr std::uint32_t config0_bwp_flash_is_writable                          = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t config0_prog_flash_write_protect_off                   = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t config0_icesel_pged_use_pair2                          = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t config0_icesel_pged_use_pair1                          = UINT32_C(0xFFFFFFF7);
    constexpr std::uint32_t config0_debug_is_enabled                               = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t config0_debug_is_disabled                              = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_fwdten_is_disabled_with_sw_enable              = UINT32_C(0xFF7FFFFF);
    constexpr std::uint32_t config1_fwdten_is_enabled_with_no_sw_disable           = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_wdt_prescale_div_1                             = UINT32_C(0xFFE0FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_2                             = UINT32_C(0xFFE1FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_4                             = UINT32_C(0xFFE2FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_8                             = UINT32_C(0xFFE3FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_16                            = UINT32_C(0xFFE4FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_32                            = UINT32_C(0xFFE5FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_64                            = UINT32_C(0xFFE6FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_128                           = UINT32_C(0xFFE7FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_256                           = UINT32_C(0xFFE8FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_512                           = UINT32_C(0xFFE9FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_1024                          = UINT32_C(0xFFEAFFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_2048                          = UINT32_C(0xFFEBFFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_4096                          = UINT32_C(0xFFECFFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_8192                          = UINT32_C(0xFFEDFFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_16384                         = UINT32_C(0xFFEEFFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_32768                         = UINT32_C(0xFFEFFFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_65536                         = UINT32_C(0xFFF0FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_131072                        = UINT32_C(0xFFF1FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_262144                        = UINT32_C(0xFFF2FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_524288                        = UINT32_C(0xFFF3FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_1048576                       = UINT32_C(0xFFF4FFFF);
    constexpr std::uint32_t config1_wdt_prescale_div_when_wdt_is_disabled          = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_poscmod_clock_switch_enable_fail_safe_disable  = UINT32_C(0xFFFF7FFF);
    constexpr std::uint32_t config1_poscmod_clock_switch_enable_fail_safe_enable   = UINT32_C(0xFFFF3FFF);
    constexpr std::uint32_t config1_poscmod_clock_switch_disable_fail_safe_disable = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_pclock_is_sysclock_div_01                      = UINT32_C(0xFFFFCFFF);
    constexpr std::uint32_t config1_pclock_is_sysclock_div_02                      = UINT32_C(0xFFFFDFFF);
    constexpr std::uint32_t config1_pclock_is_sysclock_div_04                      = UINT32_C(0xFFFFEFFF);
    constexpr std::uint32_t config1_pclock_is_sysclock_div_08                      = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_output_clock_is_enabled                        = UINT32_C(0xFFFFFBFF);
    constexpr std::uint32_t config1_output_clock_is_disabled                       = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_ext_clock_mode_is_selected                     = UINT32_C(0xFFFFFCFF);
    constexpr std::uint32_t config1_xt_osc_mode_is_selected                        = UINT32_C(0xFFFFFDFF);
    constexpr std::uint32_t config1_hs_osc_mode_is_selected                        = UINT32_C(0xFFFFFEFF);
    constexpr std::uint32_t config1_primary_osc_is_disabled                        = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_secondary_osc_is_disabled                      = UINT32_C(0xFFFFFFDF);
    constexpr std::uint32_t config1_secondary_osc_is_enabled                       = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_internal_external_mode_switch_is_disabled      = UINT32_C(0xFFFFFF7F);
    constexpr std::uint32_t config1_internal_external_mode_switch_is_enabled       = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_osc_fast_rc_osc                                = UINT32_C(0xFFFFFFF8);
    constexpr std::uint32_t config1_osc_fast_rc_osc_divn_pll                       = UINT32_C(0xFFFFFFF9);
    constexpr std::uint32_t config1_osc_primary_osc_xt_hs_ec                       = UINT32_C(0xFFFFFFFA);
    constexpr std::uint32_t config1_osc_primary_osc_with_pll                       = UINT32_C(0xFFFFFFFB);
    constexpr std::uint32_t config1_osc_secondary_osc                              = UINT32_C(0xFFFFFFFC);
    constexpr std::uint32_t config1_osc_low_power_rc_osc                           = UINT32_C(0xFFFFFFFD);
    constexpr std::uint32_t config1_osc_fast_rc_div16_osc                          = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t config1_osc_fast_rc_divn_osc                           = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config1_ieso_on                                        = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t config1_ieso_off                                       = UINT32_C(0xFFFFFF7F);

    constexpr std::uint32_t config1_foscen_on                                      = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t config1_foscen_off                                     = UINT32_C(0xFFFFFFDF);

    constexpr std::uint32_t config1_fnosc_frc                                      = UINT32_C(0xFFFFFFF8);
    constexpr std::uint32_t config1_fnosc_frcpll                                   = UINT32_C(0xFFFFFFF9);
    constexpr std::uint32_t config1_fnosc_pri                                      = UINT32_C(0xFFFFFFFA);
    constexpr std::uint32_t config1_fnosc_pripll                                   = UINT32_C(0xFFFFFFFB);
    constexpr std::uint32_t config1_fnosc_sosc                                     = UINT32_C(0xFFFFFFFC);
    constexpr std::uint32_t config1_fnosc_lprc                                     = UINT32_C(0xFFFFFFFD);
    constexpr std::uint32_t config1_fnosc_frvdiv16                                 = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t config1_fnosc_frcdiv                                   = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config2_fpllodiv_div_by_1                              = UINT32_C(0xFFF8FFFF);
    constexpr std::uint32_t config2_fpllodiv_div_by_2                              = UINT32_C(0xFFF9FFFF);
    constexpr std::uint32_t config2_fpllodiv_div_by_4                              = UINT32_C(0xFFFAFFFF);
    constexpr std::uint32_t config2_fpllodiv_div_by_8                              = UINT32_C(0xFFFBFFFF);
    constexpr std::uint32_t config2_fpllodiv_div_by_16                             = UINT32_C(0xFFFCFFFF);
    constexpr std::uint32_t config2_fpllodiv_div_by_32                             = UINT32_C(0xFFFDFFFF);
    constexpr std::uint32_t config2_fpllodiv_div_by_64                             = UINT32_C(0xFFFEFFFF);
    constexpr std::uint32_t config2_fpllodiv_div_by_256                            = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config2_upllen_enable_usb_pll                          = UINT32_C(0xFFFF7FFF);
    constexpr std::uint32_t config2_upllen_disable_and_bypass_usb_pll              = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_1                      = UINT32_C(0xFFFFF8FF);
    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_2                      = UINT32_C(0xFFFFF9FF);
    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_3                      = UINT32_C(0xFFFFFAFF);
    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_4                      = UINT32_C(0xFFFFFBFF);
    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_5                      = UINT32_C(0xFFFFFCFF);
    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_6                      = UINT32_C(0xFFFFFDFF);
    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_10                     = UINT32_C(0xFFFFFEFF);
    constexpr std::uint32_t config2_upllidiv_usb_pll_div_by_12                     = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config2_fpllmul_mul_by_15                              = UINT32_C(0xFFFFFF8F);
    constexpr std::uint32_t config2_fpllmul_mul_by_16                              = UINT32_C(0xFFFFFF9F);
    constexpr std::uint32_t config2_fpllmul_mul_by_17                              = UINT32_C(0xFFFFFFAF);
    constexpr std::uint32_t config2_fpllmul_mul_by_18                              = UINT32_C(0xFFFFFFBF);
    constexpr std::uint32_t config2_fpllmul_mul_by_19                              = UINT32_C(0xFFFFFFCF);
    constexpr std::uint32_t config2_fpllmul_mul_by_20                              = UINT32_C(0xFFFFFFDF);
    constexpr std::uint32_t config2_fpllmul_mul_by_21                              = UINT32_C(0xFFFFFFEF);
    constexpr std::uint32_t config2_fpllmul_mul_by_24                              = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config2_fpllidiv_div_by_1                              = UINT32_C(0xFFFFFFF8);
    constexpr std::uint32_t config2_fpllidiv_div_by_2                              = UINT32_C(0xFFFFFFF9);
    constexpr std::uint32_t config2_fpllidiv_div_by_3                              = UINT32_C(0xFFFFFFFA);
    constexpr std::uint32_t config2_fpllidiv_div_by_4                              = UINT32_C(0xFFFFFFFB);
    constexpr std::uint32_t config2_fpllidiv_div_by_5                              = UINT32_C(0xFFFFFFFC);
    constexpr std::uint32_t config2_fpllidiv_div_by_6                              = UINT32_C(0xFFFFFFFD);
    constexpr std::uint32_t config2_fpllidiv_div_by_10                             = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t config2_fpllidiv_div_by_12                             = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config3_fvbusonio_vbuson_controlled_by_port            = UINT32_C(0x7FFFFFFF);
    constexpr std::uint32_t config3_fvbusonio_vbuson_controlled_by_usb             = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config3_fusbidio_usbid_controlled_by_port              = UINT32_C(0xBFFFFFFF);
    constexpr std::uint32_t config3_fusbidio_usbid_controlled_by_usb               = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config3_fcanio_can_io_pins_alternate                   = UINT32_C(0xFBFFFFFF);
    constexpr std::uint32_t config3_fcanio_can_io_pins_default                     = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config3_fethio_ethernet_io_pins_alternate              = UINT32_C(0xFDFFFFFF);
    constexpr std::uint32_t config3_fethio_ethernet_io_pins_default                = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config3_fmiien_ethernet_mii_is_enabled                 = UINT32_C(0xFEFFFFFF);
    constexpr std::uint32_t config3_fmiien_ethernet_mii_is_disabled                = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_01_to_shaddow_regs     = UINT32_C(0xFFF8FFFF);
    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_02_to_shaddow_regs     = UINT32_C(0xFFF9FFFF);
    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_03_to_shaddow_regs     = UINT32_C(0xFFFAFFFF);
    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_04_to_shaddow_regs     = UINT32_C(0xFFFBFFFF);
    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_05_to_shaddow_regs     = UINT32_C(0xFFFCFFFF);
    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_06_to_shaddow_regs     = UINT32_C(0xFFFDFFFF);
    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_07_to_shaddow_regs     = UINT32_C(0xFFFEFFFF);
    constexpr std::uint32_t config3_fsrssel_assign_isr_prio_all_to_shaddow_regs    = UINT32_C(0xFFFFFFFF);

    constexpr std::uint32_t config3_userid_default_id_value                        = UINT32_C(0xFFFFFFFF);

    // Create the value for config-word0.
    constexpr std::uint32_t config0_value =   crt::config::config0_bit31_reserved_write_zero
                                            & crt::config::config0_code_protect_off
                                            & crt::config::config0_bwp_flash_is_writable
                                            & crt::config::config0_prog_flash_write_protect_off
                                            & crt::config::config0_icesel_pged_use_pair1
                                            & crt::config::config0_debug_is_disabled
                                            ;

    // Create the value for config-word1.
    constexpr std::uint32_t config1_value =   crt::config::config1_fwdten_is_disabled_with_sw_enable
                                            & crt::config::config1_wdt_prescale_div_when_wdt_is_disabled
                                            & crt::config::config1_poscmod_clock_switch_disable_fail_safe_disable
                                            & crt::config::config1_pclock_is_sysclock_div_01
                                            & crt::config::config1_output_clock_is_enabled
                                            & crt::config::config1_primary_osc_is_disabled
                                            & crt::config::config1_secondary_osc_is_disabled
                                            & crt::config::config1_internal_external_mode_switch_is_disabled
                                            & crt::config::config1_osc_fast_rc_osc_divn_pll
                                            ;

    // Create the value for config-word2.
    constexpr std::uint32_t config2_value =   crt::config::config2_fpllodiv_div_by_2
                                            & crt::config::config2_upllen_enable_usb_pll
                                            & crt::config::config2_upllidiv_usb_pll_div_by_12
                                            & crt::config::config2_fpllmul_mul_by_20
                                            & crt::config::config2_fpllidiv_div_by_2
                                            ;

    // Create the value for config-word3.
    constexpr std::uint32_t config3_value =   crt::config::config3_fvbusonio_vbuson_controlled_by_usb
                                            & crt::config::config3_fusbidio_usbid_controlled_by_usb
                                            & crt::config::config3_fcanio_can_io_pins_default
                                            & crt::config::config3_fethio_ethernet_io_pins_default
                                            & crt::config::config3_fmiien_ethernet_mii_is_disabled
                                            & crt::config::config3_fsrssel_assign_isr_prio_all_to_shaddow_regs
                                            & crt::config::config3_userid_default_id_value
                                            ;

    bool do_not_optimize_the_config_away();
  }
} // namespace crt::config

extern "C" volatile const std::uint32_t config3_at_0xBFC02FF0 __attribute__((section(".config3"))) = crt::config::config3_value;
extern "C" volatile const std::uint32_t config2_at_0xBFC02FF4 __attribute__((section(".config2"))) = crt::config::config2_value;
extern "C" volatile const std::uint32_t config1_at_0xBFC02FF8 __attribute__((section(".config1"))) = crt::config::config1_value;
extern "C" volatile const std::uint32_t config0_at_0xBFC02FFC __attribute__((section(".config0"))) = crt::config::config0_value;

bool crt::config::do_not_optimize_the_config_away()
{
  // Ensure that the configuration bytes are not optimized away.
  const volatile bool config0_is_ok = (config0_at_0xBFC02FFC != UINT32_C(0));
  const volatile bool config1_is_ok = (config1_at_0xBFC02FF8 != UINT32_C(0));
  const volatile bool config2_is_ok = (config2_at_0xBFC02FF4 != UINT32_C(0));
  const volatile bool config3_is_ok = (config3_at_0xBFC02FF0 != UINT32_C(0));

  return (config0_is_ok && config1_is_ok && config2_is_ok && config3_is_ok);
}
