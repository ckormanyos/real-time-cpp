///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

namespace crt { namespace config {

  namespace config0
  {
    constexpr std::uint32_t bit31_reserved_write_zero                              = UINT32_C(0x7FFFFFFF);
    constexpr std::uint32_t code_protect_is_on                                     = UINT32_C(0xEFFFFFFF);
    constexpr std::uint32_t code_protect_is_off                                    = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t bwp_flash_is_not_writable                              = UINT32_C(0xFEFFFFFF);
    constexpr std::uint32_t bwp_flash_is_writable                                  = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t prog_flash_write_protect_is_off                        = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t icesel_pged_uses_pair2                                 = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t icesel_pged_uses_pair1                                 = UINT32_C(0xFFFFFFF7);
    constexpr std::uint32_t debug_is_enabled                                       = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t debug_is_disabled                                      = UINT32_C(0xFFFFFFFF);
  }

  namespace config1
  {
    constexpr std::uint32_t fwdten_is_disabled_with_sw_enabled                     = UINT32_C(0xFF7FFFFF);
    constexpr std::uint32_t fwdten_is_enabled_with_no_sw_disabled                  = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t wdt_prescale_div_by_1                                  = UINT32_C(0xFFE0FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_2                                  = UINT32_C(0xFFE1FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_4                                  = UINT32_C(0xFFE2FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_8                                  = UINT32_C(0xFFE3FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_16                                 = UINT32_C(0xFFE4FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_32                                 = UINT32_C(0xFFE5FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_64                                 = UINT32_C(0xFFE6FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_128                                = UINT32_C(0xFFE7FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_256                                = UINT32_C(0xFFE8FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_512                                = UINT32_C(0xFFE9FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_1024                               = UINT32_C(0xFFEAFFFF);
    constexpr std::uint32_t wdt_prescale_div_by_2048                               = UINT32_C(0xFFEBFFFF);
    constexpr std::uint32_t wdt_prescale_div_by_4096                               = UINT32_C(0xFFECFFFF);
    constexpr std::uint32_t wdt_prescale_div_by_8192                               = UINT32_C(0xFFEDFFFF);
    constexpr std::uint32_t wdt_prescale_div_by_16384                              = UINT32_C(0xFFEEFFFF);
    constexpr std::uint32_t wdt_prescale_div_by_32768                              = UINT32_C(0xFFEFFFFF);
    constexpr std::uint32_t wdt_prescale_div_by_65536                              = UINT32_C(0xFFF0FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_131072                             = UINT32_C(0xFFF1FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_262144                             = UINT32_C(0xFFF2FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_524288                             = UINT32_C(0xFFF3FFFF);
    constexpr std::uint32_t wdt_prescale_div_by_1048576                            = UINT32_C(0xFFF4FFFF);
    constexpr std::uint32_t wdt_prescale_div_when_wdt_is_disabled                  = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t poscmod_clock_switch_is_enabled_fail_safe_is_disabled  = UINT32_C(0xFFFF7FFF);
    constexpr std::uint32_t poscmod_clock_switch_and_fail_safe_are_enabled         = UINT32_C(0xFFFF3FFF);
    constexpr std::uint32_t poscmod_clock_switch_and_fail_safe_are_disabled        = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t pclock_is_sysclock_div_by_1                            = UINT32_C(0xFFFFCFFF);
    constexpr std::uint32_t pclock_is_sysclock_div_by_2                            = UINT32_C(0xFFFFDFFF);
    constexpr std::uint32_t pclock_is_sysclock_div_by_4                            = UINT32_C(0xFFFFEFFF);
    constexpr std::uint32_t pclock_is_sysclock_div_by_8                            = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t output_clock_is_enabled                                = UINT32_C(0xFFFFFBFF);
    constexpr std::uint32_t output_clock_is_disabled                               = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t ext_clock_mode_is_selected                             = UINT32_C(0xFFFFFCFF);
    constexpr std::uint32_t xt_osc_mode_is_selected                                = UINT32_C(0xFFFFFDFF);
    constexpr std::uint32_t hs_osc_mode_is_selected                                = UINT32_C(0xFFFFFEFF);
    constexpr std::uint32_t primary_osc_is_disabled                                = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t secondary_osc_is_disabled                              = UINT32_C(0xFFFFFFDF);
    constexpr std::uint32_t secondary_osc_is_enabled                               = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t internal_external_mode_switch_is_disabled              = UINT32_C(0xFFFFFF7F);
    constexpr std::uint32_t internal_external_mode_switch_is_enabled               = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t osc_fast_rc_osc                                        = UINT32_C(0xFFFFFFF8);
    constexpr std::uint32_t osc_fast_rc_osc_divn_pll                               = UINT32_C(0xFFFFFFF9);
    constexpr std::uint32_t osc_primary_osc_xt_hs_ec                               = UINT32_C(0xFFFFFFFA);
    constexpr std::uint32_t osc_primary_osc_with_pll                               = UINT32_C(0xFFFFFFFB);
    constexpr std::uint32_t osc_secondary_osc                                      = UINT32_C(0xFFFFFFFC);
    constexpr std::uint32_t osc_low_power_rc_osc                                   = UINT32_C(0xFFFFFFFD);
    constexpr std::uint32_t osc_fast_rc_div16_osc                                  = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t osc_fast_rc_divn_osc                                   = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t ieso_is_on                                             = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t ieso_is_off                                            = UINT32_C(0xFFFFFF7F);
    constexpr std::uint32_t foscen_is_on                                           = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t foscen_is_off                                          = UINT32_C(0xFFFFFFDF);
    constexpr std::uint32_t fnosc_frc                                              = UINT32_C(0xFFFFFFF8);
    constexpr std::uint32_t fnosc_frcpll                                           = UINT32_C(0xFFFFFFF9);
    constexpr std::uint32_t fnosc_pri                                              = UINT32_C(0xFFFFFFFA);
    constexpr std::uint32_t fnosc_pripll                                           = UINT32_C(0xFFFFFFFB);
    constexpr std::uint32_t fnosc_sosc                                             = UINT32_C(0xFFFFFFFC);
    constexpr std::uint32_t fnosc_lprc                                             = UINT32_C(0xFFFFFFFD);
    constexpr std::uint32_t fnosc_frvdiv16                                         = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t fnosc_frcdiv                                           = UINT32_C(0xFFFFFFFF);
  }

  namespace config2
  {
    constexpr std::uint32_t fpllodiv_div_by_1                                      = UINT32_C(0xFFF8FFFF);
    constexpr std::uint32_t fpllodiv_div_by_2                                      = UINT32_C(0xFFF9FFFF);
    constexpr std::uint32_t fpllodiv_div_by_4                                      = UINT32_C(0xFFFAFFFF);
    constexpr std::uint32_t fpllodiv_div_by_8                                      = UINT32_C(0xFFFBFFFF);
    constexpr std::uint32_t fpllodiv_div_by_16                                     = UINT32_C(0xFFFCFFFF);
    constexpr std::uint32_t fpllodiv_div_by_32                                     = UINT32_C(0xFFFDFFFF);
    constexpr std::uint32_t fpllodiv_div_by_64                                     = UINT32_C(0xFFFEFFFF);
    constexpr std::uint32_t fpllodiv_div_by_256                                    = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t upllen_enable_usb_pll                                  = UINT32_C(0xFFFF7FFF);
    constexpr std::uint32_t upllen_disable_and_bypass_usb_pll                      = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_1                              = UINT32_C(0xFFFFF8FF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_2                              = UINT32_C(0xFFFFF9FF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_3                              = UINT32_C(0xFFFFFAFF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_4                              = UINT32_C(0xFFFFFBFF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_5                              = UINT32_C(0xFFFFFCFF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_6                              = UINT32_C(0xFFFFFDFF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_10                             = UINT32_C(0xFFFFFEFF);
    constexpr std::uint32_t upllidiv_usb_pll_div_by_12                             = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t fpllmul_mul_by_15                                      = UINT32_C(0xFFFFFF8F);
    constexpr std::uint32_t fpllmul_mul_by_16                                      = UINT32_C(0xFFFFFF9F);
    constexpr std::uint32_t fpllmul_mul_by_17                                      = UINT32_C(0xFFFFFFAF);
    constexpr std::uint32_t fpllmul_mul_by_18                                      = UINT32_C(0xFFFFFFBF);
    constexpr std::uint32_t fpllmul_mul_by_19                                      = UINT32_C(0xFFFFFFCF);
    constexpr std::uint32_t fpllmul_mul_by_20                                      = UINT32_C(0xFFFFFFDF);
    constexpr std::uint32_t fpllmul_mul_by_21                                      = UINT32_C(0xFFFFFFEF);
    constexpr std::uint32_t fpllmul_mul_by_24                                      = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t fpllidiv_div_by_1                                      = UINT32_C(0xFFFFFFF8);
    constexpr std::uint32_t fpllidiv_div_by_2                                      = UINT32_C(0xFFFFFFF9);
    constexpr std::uint32_t fpllidiv_div_by_3                                      = UINT32_C(0xFFFFFFFA);
    constexpr std::uint32_t fpllidiv_div_by_4                                      = UINT32_C(0xFFFFFFFB);
    constexpr std::uint32_t fpllidiv_div_by_5                                      = UINT32_C(0xFFFFFFFC);
    constexpr std::uint32_t fpllidiv_div_by_6                                      = UINT32_C(0xFFFFFFFD);
    constexpr std::uint32_t fpllidiv_div_by_10                                     = UINT32_C(0xFFFFFFFE);
    constexpr std::uint32_t fpllidiv_div_by_12                                     = UINT32_C(0xFFFFFFFF);
  }

  namespace config3
  {
    constexpr std::uint32_t fvbusonio_vbuson_is_controlled_by_port                 = UINT32_C(0x7FFFFFFF);
    constexpr std::uint32_t fvbusonio_vbuson_is_controlled_by_usb                  = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t fusbidio_usbid_is_controlled_by_port                   = UINT32_C(0xBFFFFFFF);
    constexpr std::uint32_t fusbidio_usbid_is_controlled_by_usb                    = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t fcanio_can_io_uses_alternate_pins                      = UINT32_C(0xFBFFFFFF);
    constexpr std::uint32_t fcanio_can_io_uses_default_pins                        = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t fethio_ethernet_io_uses_alternate_pins                 = UINT32_C(0xFDFFFFFF);
    constexpr std::uint32_t fethio_ethernet_io_uses_default_pins                   = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t fmiien_ethernet_mii_is_enabled                         = UINT32_C(0xFEFFFFFF);
    constexpr std::uint32_t fmiien_ethernet_mii_is_disabled                        = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_1_to_shaddow_regs              = UINT32_C(0xFFF8FFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_2_to_shaddow_regs              = UINT32_C(0xFFF9FFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_3_to_shaddow_regs              = UINT32_C(0xFFFAFFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_4_to_shaddow_regs              = UINT32_C(0xFFFBFFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_5_to_shaddow_regs              = UINT32_C(0xFFFCFFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_6_to_shaddow_regs              = UINT32_C(0xFFFDFFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_7_to_shaddow_regs              = UINT32_C(0xFFFEFFFF);
    constexpr std::uint32_t fsrssel_assign_isr_prio_all_to_shaddow_regs            = UINT32_C(0xFFFFFFFF);
    constexpr std::uint32_t userid_default_id_value                                = UINT32_C(0xFFFFFFFF);
  }

  // Create the value for config-word0.
  constexpr std::uint32_t
    config0_value =   config0::bit31_reserved_write_zero
                    & config0::code_protect_is_off
                    & config0::bwp_flash_is_writable
                    & config0::prog_flash_write_protect_is_off
                    & config0::icesel_pged_uses_pair1
                    & config0::debug_is_disabled
                    ;

  // Create the value for config-word1.
  constexpr std::uint32_t
    config1_value =   config1::fwdten_is_disabled_with_sw_enabled
                    & config1::wdt_prescale_div_when_wdt_is_disabled
                    & config1::poscmod_clock_switch_and_fail_safe_are_disabled
                    & config1::pclock_is_sysclock_div_by_1
                    & config1::output_clock_is_enabled
                    & config1::primary_osc_is_disabled
                    & config1::secondary_osc_is_disabled
                    & config1::internal_external_mode_switch_is_disabled
                    & config1::osc_fast_rc_osc_divn_pll
                    ;

  // Create the value for config-word2.
  constexpr std::uint32_t
    config2_value =   config2::fpllodiv_div_by_2
                    & config2::upllen_enable_usb_pll
                    & config2::upllidiv_usb_pll_div_by_12
                    & config2::fpllmul_mul_by_20
                    & config2::fpllidiv_div_by_2
                    ;

  // Create the value for config-word3.
  constexpr std::uint32_t
    config3_value =   config3::fvbusonio_vbuson_is_controlled_by_usb
                    & config3::fusbidio_usbid_is_controlled_by_usb
                    & config3::fcanio_can_io_uses_default_pins
                    & config3::fethio_ethernet_io_uses_default_pins
                    & config3::fmiien_ethernet_mii_is_disabled
                    & config3::fsrssel_assign_isr_prio_all_to_shaddow_regs
                    & config3::userid_default_id_value
                    ;

} } // namespace crt::config


extern "C"
const volatile std::uint32_t config_words[4U] __attribute__((section(".config")));

extern "C"
const volatile std::uint32_t config_words[4U] __attribute__((section(".config"))) =
{
  crt::config::config3_value,
  crt::config::config2_value,
  crt::config::config1_value,
  crt::config::config0_value
};
