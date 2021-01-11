#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2007 - 2020.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
# Description of the build options used in the build command below.
#
# %1: target
#       avr                : MICROCHIP [former ATMEL(R)] AVR(R) ATmega328P
#       atmega2560         : MICROCHIP [former ATMEL(R)] AVR(R) ATmega2560
#       atmega4809         : MICROCHIP [former ATMEL(R)] ATmegax4809
#       am335x             : BeagleBone with Texas Instruments(R) AM335x ARM(R) A8
#       xtensa32           : Espressif (XTENSA) NodeMCU ESP32
#       lpc11c24           : NXP(R) OM13093 LPC11C24 board ARM(R) Cortex(TM)-M0
#       bcm2835_raspi_b    : RaspberryPi(R) Zero with ARM(R) 1176-JZF-S
#       rl78               : Renesas(R) RL78/G13
#       rx63n              : Renesas(R) RX600
#       stm32f100          : ST Microelectronics(R) STM32F100 ARM(R) Cortex(TM)-M3
#       stm32f100          : ST Microelectronics(R) STM32L152 ARM(R) Cortex(TM)-M3
#       stm32l100c         : ST Microelectronics(R) STM32L100 ARM(R) Cortex(TM)-M3
#       stm32l152          : ST Microelectronics(R) STM32L100 ARM(R) Cortex(TM)-M3
#       stm32f407          : ST Microelectronics(R) STM32F407 ARM(R) Cortex(TM)-M4
#       stm32f429          : ST Microelectronics(R) STM32F429 ARM(R) Cortex(TM)-M4
#       stm32f446          : ST Microelectronics(R) STM32F446 ARM(R) Cortex(TM)-M4
#       host               : VC, MinGW, or other `*nix`-like generic host
#       x86_64-w64-mingw32 : VC, MinGW, or other `*nix`-like generic host

#
# %2: buildtype
#                        : None. Build the project. Compile and link outdated files only.
#       rebuild          : Rebuild the project. Clean the project. Compile and link all files.
#       clean_all        : Clean the project only.
#
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

SCRIPT_PATH=$(readlink -f "$BASH_SOURCE")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

build_command="make -f $SCRIPT_DIR/../app/make/app_make_linux.gmk $2 TGT=$1"

echo Executing Command: $build_command

$build_command

exit
