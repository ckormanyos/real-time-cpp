#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2007 - 2015.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
# Description of the build options used in the build command below.
#
# %1: target
#       am335x           : BeagleBone with TI(R) AM3359, creates a bare-metal binary file "MLO"
#       avr              : ATMEL(R) AVR(R) ATmega328P i.e., Arduino compatible
#       bcm2835_raspi_b  : RaspberryPi Model B, creates a bare-metal binary file "kernel.img"
#       pic32mx795fx     : PIC32(R) MIPS
#       rl78             : Renesas(R) RL78
#       rx63n            : Renesas(R) RX600
#       stm32f100        : ST Microelectronics STM32F100 ARM(R) Cortex(TM)-M3, STM32VLDISCOVERY board
#       stm32f407        : ST Microelectronics STM32F407 ARM(R) Cortex(TM)-M4, STM32F4DISCOVERY board
#       stm32f429        : ST Microelectronics STM32F429 ARM(R) Cortex(TM)-M4, 32F429IDISCOVERY board
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
