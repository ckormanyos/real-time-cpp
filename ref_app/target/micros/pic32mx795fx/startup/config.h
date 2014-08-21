
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CONFIG_2014_08_20_H_
  #define _CONFIG_2014_08_20_H_

  #if !defined(QUOTE)
  #define QUOTE(arg)     #arg
  #define STRVAL(arg)    QUOTE(arg)
  #endif

  #define CONFIG0                  0
  #define CONFIG1                  1
  #define CONFIG2                  2
  #define CONFIG3                  3

  #define CONFIG0_CP_ON            0xefffffff
  #define CONFIG0_CP_OFF           0xffffffff
  #define CONFIG0_BWP_RO           0xfeffffff
  #define CONFIG0_BWP_RW           0xffffffff
  #define CONFIG0_PWP_OFF          0xffffffff
  #define CONFIG0_ICESEL_2         0xffffffff
  #define CONFIG0_ICESEL_1         0xfffffff7
  #define CONFIG0_DEBUG_ON         0xfffffffe
  #define CONFIG0_DEBUG_OFF        0xffffffff

  #define CONFIG1_FWDTEN_OFF       0xffffffff
  #define CONFIG1_FWDTEN_ON        0xff7fffff

  #define CONFIG1_FPBDIV_1         0xffffcfff
  #define CONFIG1_FPBDIV_2         0xffffdfff
  #define CONFIG1_FPBDIV_4         0xffffefff
  #define CONFIG1_FPBDIV_8         0xffffffff

  #define CONFIG1_POSCMOD_OFF      0xffffffff
  #define CONFIG1_POSCMOD_EC       0xfffffcff
  #define CONFIG1_POSCMOD_XT       0xfffffdff
  #define CONFIG1_POSCMOD_HS       0xfffffeff

  #define CONFIG1_IESO_ON          0xffffffff
  #define CONFIG1_IESO_OFF         0xffffff7f

  #define CONFIG1_FOSCEN_ON        0xffffffff
  #define CONFIG1_FOSCEN_OFF       0xffffffdf

  #define CONFIG1_FNOSC_FRC        0xfffffff8
  #define CONFIG1_FNOSC_FRCPLL     0xfffffff9
  #define CONFIG1_FNOSC_PRI        0xfffffffa
  #define CONFIG1_FNOSC_PRIPLL     0xfffffffb
  #define CONFIG1_FNOSC_SOSC       0xfffffffc
  #define CONFIG1_FNOSC_LPRC       0xfffffffd
  #define CONFIG1_FNOSC_FRVDIV16   0xfffffffe
  #define CONFIG1_FNOSC_FRCDIV     0xffffffff

  #define CONFIG2_FPLLODIV_1       0xfff8ffff
  #define CONFIG2_FPLLODIV_2       0xfff9ffff
  #define CONFIG2_FPLLODIV_4       0xfffaffff
  #define CONFIG2_FPLLODIV_8       0xfffbffff
  #define CONFIG2_FPLLODIV_16      0xfffcffff
  #define CONFIG2_FPLLODIV_32      0xfffdffff
  #define CONFIG2_FPLLODIV_64      0xfffeffff
  #define CONFIG2_FPLLODIV_256     0xffffffff

  #define CONFIG2_UPLLEN_ON        0xffff7fff
  #define CONFIG2_UPLLEN_OFF       0xffffffff

  #define CONFIG2_UPLLIDIV_1       0xfffff8ff
  #define CONFIG2_UPLLIDIV_2       0xfffff9ff
  #define CONFIG2_UPLLIDIV_3       0xfffffaff
  #define CONFIG2_UPLLIDIV_4       0xfffffbff
  #define CONFIG2_UPLLIDIV_5       0xfffffcff
  #define CONFIG2_UPLLIDIV_6       0xfffffdff
  #define CONFIG2_UPLLIDIV_10      0xfffffeff
  #define CONFIG2_UPLLIDIV_12      0xffffffff

  #define CONFIG2_FPLLMUL_15       0xffffff8f
  #define CONFIG2_FPLLMUL_16       0xffffff9f
  #define CONFIG2_FPLLMUL_17       0xffffffaf
  #define CONFIG2_FPLLMUL_18       0xffffffbf
  #define CONFIG2_FPLLMUL_19       0xffffffcf
  #define CONFIG2_FPLLMUL_20       0xffffffdf
  #define CONFIG2_FPLLMUL_21       0xffffffef
  #define CONFIG2_FPLLMUL_24       0xffffffff

  #define CONFIG2_FPLLIDIV_1       0xfffffff8
  #define CONFIG2_FPLLIDIV_2       0xfffffff9
  #define CONFIG2_FPLLIDIV_3       0xfffffffa
  #define CONFIG2_FPLLIDIV_4       0xfffffffb
  #define CONFIG2_FPLLIDIV_5       0xfffffffc
  #define CONFIG2_FPLLIDIV_6       0xfffffffd
  #define CONFIG2_FPLLIDIV_10      0xfffffffe
  #define CONFIG2_FPLLIDIV_12      0xffffffff

  #define DECLARE_CONFIG(x, val)                              \
     asm(".section .config" STRVAL(x) ",\"ax\",@progbits");   \
     asm(".word " STRVAL(0xffffffff & val));                  \
     asm(".text");

#endif // _CONFIG_2014_08_20_H_
