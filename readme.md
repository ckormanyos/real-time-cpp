Companion code for the book Real-Time C++\
[![Build Status](https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp.yml/badge.svg)](https://github.com/ckormanyos/real-time-cpp/actions)
==================

This is the companion code
for the book C.M. Kormanyos,
[Real-Time C++](https://www.springer.com/de/book/9783662629956):
Efficient Object-Oriented
and Template Microcontroller Programming, Fourth Edition
(Springer, Heidelberg, 2021). ISBN 9783662629956

This repository has three main parts.
  - Reference Application `ref_app` located in [./ref_app](./ref_app)
  - [Examples](./examples) from the book
  - [Code Snippets](./code_snippets) from the book

## Details on the Reference Application

The reference application boots via a small startup code and subsequently
initializes a skinny microcontroller abstraction layer (MCAL). Control is
then passed to a simple multitasking scheduler that schedules the
LED application, calls a cyclic a benchmark task, and services the watchdog.
The LED application toggles a user-LED with a frequency of 1/2 Hz.

## Supported Targets in the Reference Application

The reference application supports the following targets:
  * MICROCHIP(R) [former ATMEL(R)] AVR(R) ATmega328P
  * MICROCHIP(R) [former ATMEL(R)] AVR(R) ATmega2560
  * MICROCHIP(R) [former ATMEL(R)] AVR(R) ATmegax4809
  * BeagleBone with Texas Instruments(R) AM335x ARM(R) A8
  * Espressif (XTENSA) NodeMCU ESP32
  * NXP(R) OM13093 LPC11C24 board ARM(R) Cortex(TM)-M0
  * RaspberryPi(R) Zero with ARM1176-JZFS(TM)
  * Renesas(R) RL78/G13
  * Renesas(R) RX600
  * ST Microelectronics(R) STM32F100 ARM(R) Cortex(R)-M3
  * ST Microelectronics(R) STM32L100 ARM(R) Cortex(R)-M3
  * ST Microelectronics(R) STM32L152 ARM(R) Cortex(R)-M3
  * ST Microelectronics(R) STM32F407 ARM(R) Cortex(R)-M4
  * ST Microelectronics(R) STM32F429 ARM(R) Cortex(R)-M4
  * ST Microelectronics(R) STM32F446 ARM(R) Cortex(R)-M4
  * VC, MinGW, or other `*nix`-like generic host

## Getting Started with the Reference Application

It is easiest to get started with the reference application using one of the
supported boards, such as Arduino or RaspberryPi ZERO or BeagleBone, etc.
The reference application can be found
in the directory [./ref_app](./ref_app) and its
subdirectories.

The reference application uses cross-development based on `*nix`-like make
tools in combination with either Bash Shell and GNU make,
Microsoft(R) Visual Studio(R) via _External Makefile_ or CMake.
Tool chains are not available in this repo (see below for further details).

### Build with Bash Shell Script and GNU make

To get started with the reference application on `*nix`
  - Open a terminal in the directory  [./ref_app](./ref_app).
  - The terminal should be located directly in [./ref_app](./ref_app) for the paths to work out (be found by the upcoming build).
  - Identify the Bash shell script [./ref_app/target/build/build.sh](./ref_app/target/build/build.sh).
  - Consider which configuration (such as `target avr`) you would like to build.
  - Execute `build.sh` with the command: `./target/build/build.sh avr rebuild`.
  - This shell script calls GNU make with parameters `avr rebuild` which subsequently rebuilds the entire solution for `target avr`.
  - If you're missing AVR GCC tools and need to get them on `*nix`, run `sudo apt install gcc-avr avr-libc`.

In summary, on `*nix` for `target avr`

```sh
cd real-time-cpp
cd ref_app
./target/build/build.sh avr rebuild
```

### Build with VisualStudio(R) Project and CMD Batch

To get started with the reference application on `Win*`
  - Start Visual Studio(R) 2019 (or later)
  - Open the solution [./ref_app/ref_app.sln](./ref_app/ref_app.sln).
  - Select the desired configuration.
  - Then rebuild the entire solution.

Note that the build in
Visual Studio(R) makes heavy use of cross development using a project
workspace of type _external makefile_ in order
to invoke GNUmake via batch file. The build process
runs in combination with several makefiles.

To build any target other than Debug or Release for Win32, a cross-compiler
(GNU GCC cross compiler) is required. See the text below for additional details.

Upon successful build, the build results, such as the HEX-files, map files, etc.,
will be placed in the `bin` directory.

There is also a workspace solution for ATMEL(R) Atmel Studio(R) 7.
It is called [./ref_app/ref_app.atsln](./ref_app/ref_app.atsln).

### Build with Cross-Environment CMake

Cross-Environment CMake can build the reference application.
For this purpose, CMake files have also been created for each supported target.

Consider, for instance, building the reference application for the
`avr`target with CMake. The pattern is shown below.

```sh
cd real-time-cpp
mkdir build
cd build
cmake ../ref_app -DTRIPLE=avr -DTARGET=avr -DCMAKE_TOOLCHAIN_FILE=../ref_app/cmake/gcc-toolchain.cmake
make -j ref_app
```

Switch from `avr` to, for instance, `bcm2835_raspi_b` or `stm32f446`
to build for one of the supported ARM(R) targets such as
RaspberryPi(R) Zero with ARM(R) 1176-JZF-S or
ST Microelectronics(R) STM32F446 ARM(R) featuring Cortex(TM)-M4.

Following the standard `*nix` pattern to build with `x86_64-w64-mingw32`
or `host` from the MSYS or Cygwin console should work too.

## Target Details

Target details including startup code and linker definition files can
be found in the target-directory and its subdirectories.

The MICROCHIP(R) [former ATMEL(R)] AVR(R) configuration
called `target avr` runs
on a classic ARDUINO(R) compatible board.
The program toggles the yellow LED on `portb.5`.

The MICROCHIP(R) [former ATMEL(R)] ATmega4809 configuration
called `target atmega4809` runs
on an ARDUINO(R) EVERY compatible board clocked
with the internal resonator at 20MHz.
The program toggles the yellow LED on `porte.2` (i.e., `D5`).

The Espressif (XTENSA) NodeMCU ESP32 implementation uses
a subset of the Espressif SDK to run the reference application
with a single OS task exclusively on 1 of its cores.

The NXP(R) OM13093 LPC11C24 board ARM(R) Cortex(TM)-M0 configuration
called "target lpc1124" toggles the LED on `port0.8`.

The ARM(R) Cortex(TM)-M3 configuration (called `target stm32f100`) runs on
the STM32VLDISCOVERY board commercially available from ST Microelectronics(R).
The program toggles the blue LED on `portc.8`.

The second ARM(R) Cortex(TM)-M3 configuration (called `target stm32l100c`)
runs on the STM32L100 DISCOVERY board commercially available from
ST Microelectronics(R). The program toggles the blue LED on `portc.8`.

The third ARM(R) Cortex(TM)-M3 configuration (called `target stm32l152`)
runs on the STM32L152C-DISCO board commercially available from
ST Microelectronics(R). The program toggles the blue LED on `portb.6`.

The first ARM(R) Cortex(TM)-M4 configuration (called `target stm32f407`) runs on
the STM32F4DISCOVERY board commercially available from ST Microelectronics(R).
The program toggles the blue LED on `portd.15`.

Another ARM(R) Cortex(TM)-M4 configuration (called `target stm32f446`) runs on
the STM32F446 Nucleo-64 board commercially available from ST Microelectronics(R).
The program toggles the green LED on `porta.5`.

The ARM(R) A8 configuration (called `target am335x`) runs on the BeagleBone
board (black edition). For the white edition, the CPU clock needs to be reduced
from 900MHz to something like 600MHz. This project creates a bare-metal program
for the BeagleBone that runs independently from any kind of `*nix` distro on
the board. Our program is designed to boot the BeagleBone from a raw binary file
called _MLO_ stored on a FAT32 SDHC microcard. The binary file includes a
special boot header comprised of two 32-bit integers. The program is loaded
from SD-card into RAM memory and subsequently executed. When switching on
the BeagleBone black, the boot button (S2) must be pressed while powering
up the board. The program toggles the first user LED (LED1 on `port1.21`).

The ARM(R) 1176-JZF-S configuration (called `target bcm2835_raspi_b`) runs on the
RaspberryPi(R) Zero (PiZero) single core controller.
This project creates a bare-metal program for the PiZero.
This program runs independently from any kind of `*nix` distro on the board.
Our program is designed to boot the PiZero from a raw binary file.
The raw binary file is called _kernel.img_ and it is stored on a FAT32 SDHC
microcard. The program _objcopy_ can be used to extract raw binary
from a ELF-file using the output flags `-O binary`.
The kernel.img file is stored on the SD card together with
three other files: bootcode.bin, start.elf and (an optional)
config.txt, all described on internet. A complete set of
[PiZero boot contents for an SD card](./ref_app/target/micros/bcm2835_raspi_b/startup/SD_CARD/PiZero)
running the bare-metal reference application are included in this repo.
The program toggles the GPIO status LED  at GPIO index `0x47`.

For other compatible boards, feel free contact me directly or submit
an issue requesting support for your desired target system.

## Benchmarks

[Benchmarks](./ref_app/src/app/benchmark)
provide scalable, portable C++11 means for identifying
the performance and the performance class of the microcontroller.
For more information, see the detailed information
on the [benchmarks](./ref_app/src/app/benchmark) pages.

## All Bare-Metal

Projects in this repo are programmed _OS-less_ in bare-metal mode
making use of self-written startup code.
No external libraries other than native C++ and its own
standard libraries are used.

Consider, for instance, the BeagleBone Black Edition
(known as `target am335x` below) --- one of several
target systems supported in this repository.
The projects on this board boot from the binary image file
_MLO_ the SD card and subsequently perform their own
static initialization and chip initialization
of the ARM(R) 8 AM335x processor.

The following [pdf image](./images/bare_metal_bbb.pdf)
depicts the bare-metal BeagleBobe Black Edition (BBB)
in action. The microcontroller on the board is cyclically performing
one of the [benchmarks](./ref_app/src/app/benchmark)
mentioned above. The first
user LED is toggled on `port1.21` in multitasking operation
and the oscilloscope captures
a real-time measurement of the benchmark's time signal
on digital I/O `port1.15`, header pin `P8.15` of the BBB.

## Continuous Integration (CI)

Continuous integration uses GitHub Actions programmed in YAML.
The [CI script](.github/workflows/real-time-cpp.yml)
exercises various target builds, example builds
and benchmark builds/runs on Ubuntu or Windows-Latest
using GNUmake, CMake or MSBuild
depending on the particular OS/build/target configuration.

### Build Status
[![Build Status](https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp.yml/badge.svg)](https://github.com/ckormanyos/real-time-cpp/actions)

## GNU GCC Compilers

GNU GCC cross compilers for the microcontroller solutions are *not*
available here.

A GNU GCC port with a relatively high level of C++11 awareness such as
GCC 5 through 11 (higher generally being more advantageous)
is required for building the reference application.

Some of the code snippets demonstrate language elements not only from C++11,
but also from C++14, 17, 20. A compiler with C++17 support (such as GCC 6, 7, or 8)
or even C++20 support (such as GCC 11) can, therefore,
be beneficial for success with *all* of the code snippets.

In the reference application on `Win*`, the makefiles are aware of a default location
for the respective GCC toolchains.
This [toolchain location](ref_app/tools/Util/MinGW/msys/1.0/local)
has been defined by myself at the beginning of the project.
Toolchains intended for the cross MSVC/GCC builds should be located there
(although these are not _yet_ part of this repository).

Open issues such as [this issue](https://github.com/ckormanyos/real-time-cpp/issues/103)
and/or [this issue](https://github.com/ckormanyos/real-time-cpp/issues/108)
track the ongoing effort to make cross-compilers available
in efficient forms in this repository.
At the moment, however, when using the reference application
or designing a custom build for msvc or similar,
the root directory of the tool chain must be properly
supplied to the makefiles.
