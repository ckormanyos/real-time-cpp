
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CONFIG_2014_08_20_H_
  #define _CONFIG_2014_08_20_H_

  #include <cstdint>

  constexpr std::uint32_t config0_cp_on            = UINT32_C(0xefffffff);
  constexpr std::uint32_t config0_cp_off           = UINT32_C(0xffffffff);
  constexpr std::uint32_t config0_bwp_ro           = UINT32_C(0xfeffffff);
  constexpr std::uint32_t config0_bwp_rw           = UINT32_C(0xffffffff);
  constexpr std::uint32_t config0_pwp_off          = UINT32_C(0xffffffff);
  constexpr std::uint32_t config0_icesel_2         = UINT32_C(0xffffffff);
  constexpr std::uint32_t config0_icesel_1         = UINT32_C(0xfffffff7);
  constexpr std::uint32_t config0_debug_on         = UINT32_C(0xfffffffe);
  constexpr std::uint32_t config0_debug_off        = UINT32_C(0xffffffff);

  constexpr std::uint32_t config1_fwdten_off       = UINT32_C(0xffffffff);
  constexpr std::uint32_t config1_fwdten_on        = UINT32_C(0xff7fffff);

  constexpr std::uint32_t config1_fpbdiv_1         = UINT32_C(0xffffcfff);
  constexpr std::uint32_t config1_fpbdiv_2         = UINT32_C(0xffffdfff);
  constexpr std::uint32_t config1_fpbdiv_4         = UINT32_C(0xffffefff);
  constexpr std::uint32_t config1_fpbdiv_8         = UINT32_C(0xffffffff);

  constexpr std::uint32_t config1_poscmod_off      = UINT32_C(0xffffffff);
  constexpr std::uint32_t config1_poscmod_ec       = UINT32_C(0xfffffcff);
  constexpr std::uint32_t config1_poscmod_xt       = UINT32_C(0xfffffdff);
  constexpr std::uint32_t config1_poscmod_hs       = UINT32_C(0xfffffeff);

  constexpr std::uint32_t config1_ieso_on          = UINT32_C(0xffffffff);
  constexpr std::uint32_t config1_ieso_off         = UINT32_C(0xffffff7f);

  constexpr std::uint32_t config1_foscen_on        = UINT32_C(0xffffffff);
  constexpr std::uint32_t config1_foscen_off       = UINT32_C(0xffffffdf);

  constexpr std::uint32_t config1_fnosc_frc        = UINT32_C(0xfffffff8);
  constexpr std::uint32_t config1_fnosc_frcpll     = UINT32_C(0xfffffff9);
  constexpr std::uint32_t config1_fnosc_pri        = UINT32_C(0xfffffffa);
  constexpr std::uint32_t config1_fnosc_pripll     = UINT32_C(0xfffffffb);
  constexpr std::uint32_t config1_fnosc_sosc       = UINT32_C(0xfffffffc);
  constexpr std::uint32_t config1_fnosc_lprc       = UINT32_C(0xfffffffd);
  constexpr std::uint32_t config1_fnosc_frvdiv16   = UINT32_C(0xfffffffe);
  constexpr std::uint32_t config1_fnosc_frcdiv     = UINT32_C(0xffffffff);

  constexpr std::uint32_t config2_fpllodiv_1       = UINT32_C(0xfff8ffff);
  constexpr std::uint32_t config2_fpllodiv_2       = UINT32_C(0xfff9ffff);
  constexpr std::uint32_t config2_fpllodiv_4       = UINT32_C(0xfffaffff);
  constexpr std::uint32_t config2_fpllodiv_8       = UINT32_C(0xfffbffff);
  constexpr std::uint32_t config2_fpllodiv_16      = UINT32_C(0xfffcffff);
  constexpr std::uint32_t config2_fpllodiv_32      = UINT32_C(0xfffdffff);
  constexpr std::uint32_t config2_fpllodiv_64      = UINT32_C(0xfffeffff);
  constexpr std::uint32_t config2_fpllodiv_256     = UINT32_C(0xffffffff);

  constexpr std::uint32_t config2_upllen_on        = UINT32_C(0xffff7fff);
  constexpr std::uint32_t config2_upllen_off       = UINT32_C(0xffffffff);

  constexpr std::uint32_t config2_upllidiv_1       = UINT32_C(0xfffff8ff);
  constexpr std::uint32_t config2_upllidiv_2       = UINT32_C(0xfffff9ff);
  constexpr std::uint32_t config2_upllidiv_3       = UINT32_C(0xfffffaff);
  constexpr std::uint32_t config2_upllidiv_4       = UINT32_C(0xfffffbff);
  constexpr std::uint32_t config2_upllidiv_5       = UINT32_C(0xfffffcff);
  constexpr std::uint32_t config2_upllidiv_6       = UINT32_C(0xfffffdff);
  constexpr std::uint32_t config2_upllidiv_10      = UINT32_C(0xfffffeff);
  constexpr std::uint32_t config2_upllidiv_12      = UINT32_C(0xffffffff);

  constexpr std::uint32_t config2_fpllmul_15       = UINT32_C(0xffffff8f);
  constexpr std::uint32_t config2_fpllmul_16       = UINT32_C(0xffffff9f);
  constexpr std::uint32_t config2_fpllmul_17       = UINT32_C(0xffffffaf);
  constexpr std::uint32_t config2_fpllmul_18       = UINT32_C(0xffffffbf);
  constexpr std::uint32_t config2_fpllmul_19       = UINT32_C(0xffffffcf);
  constexpr std::uint32_t config2_fpllmul_20       = UINT32_C(0xffffffdf);
  constexpr std::uint32_t config2_fpllmul_21       = UINT32_C(0xffffffef);
  constexpr std::uint32_t config2_fpllmul_24       = UINT32_C(0xffffffff);

  constexpr std::uint32_t config2_fpllidiv_1       = UINT32_C(0xfffffff8);
  constexpr std::uint32_t config2_fpllidiv_2       = UINT32_C(0xfffffff9);
  constexpr std::uint32_t config2_fpllidiv_3       = UINT32_C(0xfffffffa);
  constexpr std::uint32_t config2_fpllidiv_4       = UINT32_C(0xfffffffb);
  constexpr std::uint32_t config2_fpllidiv_5       = UINT32_C(0xfffffffc);
  constexpr std::uint32_t config2_fpllidiv_6       = UINT32_C(0xfffffffd);
  constexpr std::uint32_t config2_fpllidiv_10      = UINT32_C(0xfffffffe);
  constexpr std::uint32_t config2_fpllidiv_12      = UINT32_C(0xffffffff);

  #define CONFIG_QUOTE(arg)       #arg
  #define CONFIG_STRVAL(arg)      CONFIG_QUOTE(arg)

  #define CONFIG_NUMBER_0  0
  #define CONFIG_NUMBER_1  1
  #define CONFIG_NUMBER_2  2
  #define CONFIG_NUMBER_3  3

  #define CONFIG_DECLARE_CONFIG(x, val)                              \
     asm(".section .config" CONFIG_STRVAL(x) ",\"ax\",@progbits");   \
     asm(".word " CONFIG_STRVAL(UINT32_C(0xffffffff) & (val)));      \
     asm(".text");

#endif // _CONFIG_2014_08_20_H_
