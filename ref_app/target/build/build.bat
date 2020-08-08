@rem
@rem  Copyright Christopher Kormanyos 2007 - 2020.
@rem  Distributed under the Boost Software License,
@rem  Version 1.0. (See accompanying file LICENSE_1_0.txt
@rem  or copy at http://www.boost.org/LICENSE_1_0.txt)
@rem

@rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
@rem
@rem Description of the build options used in the build command below.
@rem
@rem %1: target
@rem       am335x           : BeagleBone with TI(R) AM3359, creates a bare-metal binary file "MLO"
@rem       avr              : ATMEL(R) AVR(R) ATmega328P i.e., Arduino compatible
@rem       bcm2835_raspi_b  : RaspberryPi Zero, creates a bare-metal binary file "kernel.img"
@rem       rl78             : Renesas(R) RL78
@rem       rx63n            : Renesas(R) RX600
@rem       stm32f100        : ST Microelectronics STM32F100 ARM(R) Cortex(TM)-M3, STM32VLDISCOVERY board
@rem       stm32f407        : ST Microelectronics STM32F407 ARM(R) Cortex(TM)-M4, STM32F4DISCOVERY board
@rem       stm32f429        : ST Microelectronics STM32F429 ARM(R) Cortex(TM)-M4, 32F429IDISCOVERY board
@rem       stm32f446        : ST Microelectronics STM32F446 ARM(R) Cortex(TM)-M4, 32F446-Nucleo
@rem
@rem %2: buildtype
@rem                        : None. Build the project. Compile and link outdated files only.
@rem       rebuild          : Rebuild the project. Clean the project. Compile and link all files.
@rem       clean_all        : Clean the project only.
@rem
@rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

@Set build_command=tools\Util\MinGW\msys\1.0\bin\make.exe -f target/app/make/app_make.gmk %2 TGT=%1

@echo Executing Command: %build_command%

@%build_command%
