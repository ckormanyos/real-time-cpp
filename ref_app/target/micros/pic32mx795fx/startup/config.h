
#ifndef _CONFIG_2014_08_20_H_
  #define _CONFIG_2014_08_20_H_

  #if !defined(QUOTE)
  #define QUOTE(arg)     #arg
  #define STRVAL(arg)    QUOTE(arg)
  #endif

  #define DEVCFG0                  0
  #define DEVCFG1                  1
  #define DEVCFG2                  2
  #define DEVCFG3                  3

  #define DEVCFG0_CP_ON            0xefffffff
  #define DEVCFG0_CP_OFF           0xffffffff
  #define DEVCFG0_BWP_RO           0xfeffffff
  #define DEVCFG0_BWP_RW           0xffffffff
  #define DEVCFG0_PWP_OFF          0xffffffff
  #define DEVCFG0_ICESEL_2         0xffffffff
  #define DEVCFG0_ICESEL_1         0xfffffff7
  #define DEVCFG0_DEBUG_ON         0xfffffffe
  #define DEVCFG0_DEBUG_OFF        0xffffffff

  #define DEVCFG1_FWDTEN_OFF       0xffffffff
  #define DEVCFG1_FWDTEN_ON        0xff7fffff

  #define DEVCFG1_FPBDIV_1         0xffffcfff
  #define DEVCFG1_FPBDIV_2         0xffffdfff
  #define DEVCFG1_FPBDIV_4         0xffffefff
  #define DEVCFG1_FPBDIV_8         0xffffffff

  #define DEVCFG1_POSCMOD_OFF      0xffffffff
  #define DEVCFG1_POSCMOD_EC       0xfffffcff
  #define DEVCFG1_POSCMOD_XT       0xfffffdff
  #define DEVCFG1_POSCMOD_HS       0xfffffeff

  #define DEVCFG1_IESO_ON          0xffffffff
  #define DEVCFG1_IESO_OFF         0xffffff7f

  #define DEVCFG1_FOSCEN_ON        0xffffffff
  #define DEVCFG1_FOSCEN_OFF       0xffffffdf

  #define DEVCFG1_FNOSC_FRC        0xfffffff8
  #define DEVCFG1_FNOSC_FRCPLL     0xfffffff9
  #define DEVCFG1_FNOSC_PRI        0xfffffffa
  #define DEVCFG1_FNOSC_PRIPLL     0xfffffffb
  #define DEVCFG1_FNOSC_SOSC       0xfffffffc
  #define DEVCFG1_FNOSC_LPRC       0xfffffffd
  #define DEVCFG1_FNOSC_FRVDIV16   0xfffffffe
  #define DEVCFG1_FNOSC_FRCDIV     0xffffffff

  #define DEVCFG2_FPLLODIV_1       0xfff8ffff
  #define DEVCFG2_FPLLODIV_2       0xfff9ffff
  #define DEVCFG2_FPLLODIV_4       0xfffaffff
  #define DEVCFG2_FPLLODIV_8       0xfffbffff
  #define DEVCFG2_FPLLODIV_16      0xfffcffff
  #define DEVCFG2_FPLLODIV_32      0xfffdffff
  #define DEVCFG2_FPLLODIV_64      0xfffeffff
  #define DEVCFG2_FPLLODIV_256     0xffffffff

  #define DEVCFG2_UPLLEN_ON        0xffff7fff
  #define DEVCFG2_UPLLEN_OFF       0xffffffff

  #define DEVCFG2_UPLLIDIV_1       0xfffff8ff
  #define DEVCFG2_UPLLIDIV_2       0xfffff9ff
  #define DEVCFG2_UPLLIDIV_3       0xfffffaff
  #define DEVCFG2_UPLLIDIV_4       0xfffffbff
  #define DEVCFG2_UPLLIDIV_5       0xfffffcff
  #define DEVCFG2_UPLLIDIV_6       0xfffffdff
  #define DEVCFG2_UPLLIDIV_10      0xfffffeff
  #define DEVCFG2_UPLLIDIV_12      0xffffffff

  #define DEVCFG2_FPLLMUL_15       0xffffff8f
  #define DEVCFG2_FPLLMUL_16       0xffffff9f
  #define DEVCFG2_FPLLMUL_17       0xffffffaf
  #define DEVCFG2_FPLLMUL_18       0xffffffbf
  #define DEVCFG2_FPLLMUL_19       0xffffffcf
  #define DEVCFG2_FPLLMUL_20       0xffffffdf
  #define DEVCFG2_FPLLMUL_21       0xffffffef
  #define DEVCFG2_FPLLMUL_24       0xffffffff

  #define DEVCFG2_FPLLIDIV_1       0xfffffff8
  #define DEVCFG2_FPLLIDIV_2       0xfffffff9
  #define DEVCFG2_FPLLIDIV_3       0xfffffffa
  #define DEVCFG2_FPLLIDIV_4       0xfffffffb
  #define DEVCFG2_FPLLIDIV_5       0xfffffffc
  #define DEVCFG2_FPLLIDIV_6       0xfffffffd
  #define DEVCFG2_FPLLIDIV_10      0xfffffffe
  #define DEVCFG2_FPLLIDIV_12      0xffffffff

  #define DECLARE_CONFIG(x, val)                              \
     asm(".section .config" STRVAL(x) ",\"ax\",@progbits");   \
     asm(".word " STRVAL(0xffffffff & val));                  \
     asm(".text");

#endif // _CONFIG_2014_08_20_H_
