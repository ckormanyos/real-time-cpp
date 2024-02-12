Real-Time-C++
==================

<p align="center">
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp.yml/badge.svg" alt="Build Status"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-examples.yml/badge.svg" alt="Build Examples"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-snippets.yml/badge.svg" alt="Build Snippets"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-benchmarks.yml/badge.svg" alt="Build Benchmarks"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/issues?q=is%3Aissue+is%3Aopen+sort%3Aupdated-desc">
        <img src="https://custom-icon-badges.herokuapp.com/github/issues-raw/ckormanyos/real-time-cpp?logo=github" alt="Issues" /></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/actions/workflows/codeql.yml">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/codeql.yml/badge.svg" alt="CodeQL"></a>
    <a href="https://scan.coverity.com/projects/ckormanyos-real-time-cpp">
        <img src="https://scan.coverity.com/projects/24862/badge.svg" alt="Coverity Scan"></a>
    <a href="https://sonarcloud.io/summary/new_code?id=ckormanyos_real-time-cpp">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=ckormanyos_real-time-cpp&metric=alert_status" alt="Quality Gate Status"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/blob/master/LICENSE_1_0.txt">
        <img src="https://img.shields.io/badge/license-BSL%201.0-blue.svg" alt="Boost Software License 1.0"></a>
    <a href="https://img.shields.io/github/commit-activity/y/ckormanyos/real-time-cpp">
        <img src="https://img.shields.io/github/commit-activity/y/ckormanyos/real-time-cpp" alt="GitHub commit activity" /></a>
    <a href="https://github.com/ckormanyos/real-time-cpp">
        <img src="https://img.shields.io/github/languages/code-size/ckormanyos/real-time-cpp" alt="GitHub code size in bytes" /></a>
</p>

This is the companion code
for the book C.M. Kormanyos,
[Real-Time C++](https://www.springer.com/de/book/9783662629956):
Efficient Object-Oriented
and Template Microcontroller Programming, Fourth Edition
(Springer, Heidelberg, 2021) ISBN 9783662629956.

This repository has several main parts.
  - Reference Application `ref_app` located in [ref_app](./ref_app). This also includes the [benchmarks](./ref_app/src/app/benchmark).
  - [Examples](./examples) from the book
  - [Code Snippets](./code_snippets) from the book

GNU/GCC cross compilers and various additional tools
running on `Win*`, optionally needed for certain builds
as described below, can be found in the related
[ckormanyos/real-time-cpp-toolchains](https://github.com/ckormanyos/real-time-cpp-toolchains)
repository.

## Details on the Reference Application

The reference application boots via a small startup code and subsequently
initializes a skinny microcontroller abstraction layer (MCAL). Control is
then passed to a simple multitasking scheduler that schedules the
LED application, calls a cyclic a benchmark task, and services the watchdog.

The LED application toggles a user-LED with a frequency of $\frac{1}{2}~\text{Hz}$
The result is LED on for one second, LED off for one second.
The LED application runs cyclically and perpetually
without break or pause.

The reference application is compatible with C++14, 17, 20, 23 and beyond.

## Portability

The application software is implemented once and used uniformly
on each supported target in the reference application.
Differences among the individual targets arise only
in the lower software layers pertaining
to chip-specific and board-specific startup/MCAL details.

In this way the application software exhibits a high level
of portability.

## Supported Targets in the Reference Application

The reference application supports the following targets:

| Target name (as used in build command) | Target Description |
| -------------------------------------- | ------------------ |
| `avr`                                  | MICROCHIP(R) [former ATMEL(R)] AVR(R) ATmega328P            |
| `atmega2560`                           | MICROCHIP(R) [former ATMEL(R)] AVR(R) ATmega2560            |
| `atmega4809`                           | MICROCHIP(R) [former ATMEL(R)] AVR(R) ATmegax4809           |
| `am335x`                               | BeagleBone with Texas Instruments(R) AM335x ARM(R) A8       |
| `bcm2835_raspi_b`                      | RaspberryPi(R) Zero with ARM1176-JZFS(TM)                   |
| `Debug`/`Release`                      | PC on `Win*` via MSVC x64 compiler `Debug`/`Release`        |
| `host`                                 | PC/Workstation on `Win*`/`mingw64`/`*nix` via host compiler |
| `lpc11c24`                             | NXP(R) OM13093 LPC11C24 board ARM(R) Cortex(R)-M0           |
| `nxp_imxrt1062`                        | Teensy 4.0 Board / NXP(R) iMXRT1062 ARM(R) Cortex(R)-M7     |
| `riscvfe310`                           | SiFive RISC-V FE310 SoC                                     |
| `rl78`                                 | Renesas(R) RL78/G13                                         |
| `rx63n`                                | Renesas(R) RX630/RX631                                      |
| `stm32f100`                            | STMicroelectronics(R) STM32F100 ARM(R) Cortex(R)-M3         |
| `stm32l100c`                           | STMicroelectronics(R) STM32L100 ARM(R) Cortex(R)-M3         |
| `stm32l152`                            | STMicroelectronics(R) STM32L152 ARM(R) Cortex(R)-M3         |
| `stm32f407`                            | STMicroelectronics(R) STM32F407 ARM(R) Cortex(R)-M4         |
| `stm32f429`                            | STMicroelectronics(R) STM32F429 ARM(R) Cortex(R)-M4         |
| `stm32f446`                            | STMicroelectronics(R) STM32F446 ARM(R) Cortex(R)-M4         |
| `stm32h7a3`                            | STMicroelectronics(R) STM32H7A3 ARM(R) Cortex(R)-M7         |
| `v850es_fx2`                           | Renesas(R) Electronics V850es/Fx2 upd703231                 |
| `x86_64-w64-mingw32`                   | PC on `Win*`/`mingw64` via GNU/GCC x86_x64 compiler         |
| `xtensa32`                             | Espressif (XTENSA) NodeMCU ESP32                            |


## Getting Started with the Reference Application

It is easiest to get started with the reference application using one of the
supported boards, such as `avr` (ARDUINO) or `bcm2835_raspi_b`
(RaspberryPi ZERO) or `am335x` (BeagleBoneBlack), etc.
The reference application can be found
in the directory [ref_app](./ref_app) and its
subdirectories.

The reference application uses cross-development based on
`*nix`-like make tools in combination with either
Bash/GNUmake, Microsoft(R) Visual Studio(R) via _External Makefile_,
or platform-independent CMake.

Upon successful completion of the build,
the resulting build artifacts, including HEX-files
(such as `ref_app.hex`), map files, size reports, etc.,
are available in the `bin` directory.

### Build with Bash Shell Script and GNU make

To get started with the reference application on `*nix`
  - Open a terminal in the directory  [ref_app](./ref_app).
  - The terminal should be located directly in [ref_app](./ref_app) for the paths to work out (be found by the upcoming build).
  - Identify the Bash shell script [ref_app/target/build/build.sh](./ref_app/target/build/build.sh).
  - Consider which configuration (such as `target avr`) you would like to build.
  - Execute `build.sh` with the command: `./target/build/build.sh avr rebuild`.
  - This shell script calls GNU make with parameters `avr rebuild` which subsequently rebuilds the entire solution for `target avr`.
  - If you're missing AVR GCC tools and need to get them on `*nix`, run `sudo apt install gcc-avr avr-libc`.

### Example build on `*nix` for `target avr`

We will now exemplify how to build the reference application on a command shell
in `*nix` for `target avr`. This target system includes essentially
_any_ ARDUINO(R)-compatible board. This is also the board compatibility
actually used with the homemade boards in the book.

Install `gcc-avr` if needed.

```sh
sudo apt install gcc-avr avr-libc
```

Clone or get the [ckormanyos/real-time-cpp](https://github.com/ckormanyos/real-time-cpp)
repository. Then build with:

```sh
cd real-time-cpp
cd ref_app
./target/build/build.sh avr rebuild
```

### Example build on `*nix` for `target stm32f446`

We will now exemplify how to build the reference application on a command shell
in `*nix` for an ARM(R) target. Consider, for example, the build variant
`target stm32f446`. The NUCLEO-F446RE board from STMicroelectronics(R)
can conveniently be used for this.

Install `gcc-arm-none-eabi` if needed.

```sh
sudo apt install gcc-arm-none-eabi
```

Clone or get the [ckormanyos/real-time-cpp](https://github.com/ckormanyos/real-time-cpp)
repository. Then build with:

```sh
cd real-time-cpp
cd ref_app
./target/build/build.sh stm32f446 rebuild
```

### Example build on MacOS for `target stm32f446`

We will now exemplify how to build the reference application in a command shell
in MacOS for an ARM(R) target. Consider, for example, the build variant
`target stm32f446`. The NUCLEO-F446RE board from STMicroelectronics(R)
can conveniently be used for this.

Clone or get the [ckormanyos/real-time-cpp](https://github.com/ckormanyos/real-time-cpp)
repository.

The default version 3.81 of GNUmake on MacOS can (now) be used.
The make files used in this repository have been made
compatible with it. For background information, see also
[issue 273](https://github.com/ckormanyos/real-time-cpp/issues/273).

Build the target with a direct call to `make`.

```sh
cd real-time-cpp
cd ref_app
make -f target/app/make/app_make_linux.gmk rebuild TGT=stm32f446
```

If the toolchain is needed then it must be installed or retrieved
prior to building the target of the reference application.

You can `wget` (or with a slightly different procedure optionally install)
the `gcc-arm-none-eabi` toolchain if needed.
In this case, I have found it convenient to use
a modern `gcc-arm-none-eabi` for MacOS which can be found at
[Arm GNU Toolchain Downloads](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads).

The `arm-non-eabi` toolchain can be fetched via `wget`
and successfully used locally in the shell. If this is desired,
follow the step-by-step procedure below.

Step 1: Make a local directory (such as `macos-gnu-arm-toolchain`) and `cd` into it.

```sh
cd real-time-cpp
mkdir -p macos-gnu-arm-toolchain
cd macos-gnu-arm-toolchain
```

Step 2: Fetch the toolchain's tarball with `wget`, unpack it
and add the compiler's `bin`-directory to the shell's executable path.

```sh
wget --no-check-certificate https://developer.arm.com/-/media/Files/downloads/gnu/12.2.rel1/binrel/arm-gnu-toolchain-12.2.rel1-darwin-x86_64-arm-none-eabi.tar.xz
tar -xvf arm-gnu-toolchain-12.2.rel1-darwin-x86_64-arm-none-eabi.tar.xz
PATH=$(pwd)/arm-gnu-toolchain-12.2.rel1-darwin-x86_64-arm-none-eabi/bin:$PATH
```

Step 3: Optionally `echo` the `PATH` for a quick path-check.
It can also be helpful to query `arm-non-eabi-g++`'s version
in order to verify that the toolchain is correctly added
to this shell's local `PATH`.

```sh
echo $PATH
arm-none-eabi-g++ -v
```

Now repeat (or retry) the commands to build the target,
as shown above with a direct call to `make`.

### Build with VisualStudio(R) Project and CMD Batch

To get started with the reference application on `Win*`
  - Clone or get the [ckormanyos/real-time-cpp](https://github.com/ckormanyos/real-time-cpp) repository.
  - Get and setup (from the [ckormanyos/real-time-cpp-toolchains](https://github.com/ckormanyos/real-time-cpp-toolchains) repository) any needed GNU/GCC cross compilers running on `Win*`, as described in detail a few paragraphs below.
  - Start Visual Studio(R) 2019 (or later, Community Edition is OK)
  - Open the solution `ref_app.sln` in the [ref_app](./ref_app) directory.
  - Select the desired configuration.
  - Then rebuild the entire solution.

The `ref_app` build in Microsoft(R) VisualStudio(R)
makes heavy use of cross development using a project
workspace of type _External_ _Makefile_.
GNUmake is invoked via batch file in the build process.
It subsequently runs in combination with several Makefiles.

To build any `ref_app` target other than `Debug` or `Release` for Win32, a cross-compiler
(GNU/GCC cross compiler) is required. See the text below for additional details.

GNU/GCC cross compilers running on `Win*` intended
for the reference application on VisualStudio(R)
can be found in the _toolchains_ repository,
[ckormanyos/real-time-cpp-toolchains](https://github.com/ckormanyos/real-time-cpp-toolchains).
The _toolchains_ repository contains detailed instructions on
installing, moving and using these ported GNU/GCC compilers.

Note on GNUmake for `Win*`: A GNUmake capable of being used on `Win*`
can be found in the
[ckormanyos/make-4.2.1-msvc-build](https://github.com/ckormanyos/make-4.2.1-msvc-build)
repository.
If desired, clone or get the code of this repository.
Build `make-4.2.1` in its `x64` `Release` configuration
with MSVC (i.e., VC 14.2 or later, Community Edition is OK).

### Build with Cross-Environment CMake

Cross-Environment CMake can build the reference application.
For this purpose, CMake files have also been created for each supported target.

Consider, for instance, building the reference application for the
`avr` target with CMake. The pattern is shown below.

```sh
cd real-time-cpp
mkdir build
cd build
cmake ../ref_app -DTRIPLE=avr -DTARGET=avr -DCMAKE_TOOLCHAIN_FILE=../ref_app/cmake/gcc-toolchain.cmake
make -j ref_app
```

We will now consider, for instance, building the reference application for
one of the supported ARM(R) targets with CMake. The pattern is shown below.
In this case, we need to identify the following make options:

```
-DTRIPLE=avr -DTARGET=avr
```

Switch these options to the ones intended for the `stm32f446` ARM(R)-based target being built.

```
-DTRIPLE=arm-none-eabi -DTARGET=stm32f446
```

Let's clarify the commands in their entirety in order to run a CMake build for `stm32f446`
(i.e., ST Microelectronics(R) STM32F446 ARM(R) featuring Cortex(R)-M4).

```sh
cd real-time-cpp
mkdir build
cd build
cmake ../ref_app -DTRIPLE=arm-none-eabi -DTARGET=stm32f446 -DCMAKE_TOOLCHAIN_FILE=../ref_app/cmake/gcc-toolchain.cmake
make -j ref_app
```

When building with CMake for other targets,
follow the standard `*nix` pattern to build.
Also building with CMake for `x86_64-w64-mingw32`
or `host` from MSYS, Cygwin or any similar `*nix`-like
shell or console should work too.

The following command sequence will build for the
native `host` on a `*nix`-like shell or console.

```sh
cd real-time-cpp
mkdir build
cd build
cmake ../ref_app -DTARGET=host -DCMAKE_TOOLCHAIN_FILE=../ref_app/cmake/gcc-toolchain.cmake
make -j ref_app
```

### Build with MICROCHIP's ATMEL Studio

There is also a workspace solution for ATMEL(R) AtmelStudio(R) 7.
It is called `ref_app.atsln` and is also located
in the [ref_app](./ref_app) directory.
There are ATMEL Studio projects for
both the reference application as well as for each of the examples.
ATMEL Studio projects in this repository support
the AVR target only.

If you decide to use ATMEL Studio, you do not need to use or include
any additional libraries for these projects
(other than those that are ordinarily installed
during the standard installation of ATMEL Studio).

## Target Details

Target details including startup code and linker definition files can
be found in the [ref_app/target](./ref_app/target) directory
and its subdirectories. There are individual subdirectories for
each supported target microcontroller system.

The MICROCHIP(R) [former ATMEL(R)] AVR(R) configuration
called `target avr` runs
on a classic ARDUINO(R) compatible board.
The program toggles the yellow LED on `portb.5`.

The MICROCHIP(R) [former ATMEL(R)] ATmega4809 configuration
called `target atmega4809` runs
on an ARDUINO(R) EVERY compatible board clocked
with the internal resonator at $20~\text{MHz}$.
The program toggles the yellow LED on `porte.2` (i.e., `D5`).

The Espressif (XTENSA) NodeMCU ESP32 implementation uses
a subset of the Espressif SDK to run the reference application
with a single OS task exclusively on 1 of its cores.

The NXP(R) OM13093 LPC11C24 board ARM(R) Cortex(R)-M0 configuration
called "target lpc11c24" toggles the LED on `port0.8`.

The ARM(R) Cortex(R)-M3 configuration (called `target stm32f100`) runs on
the STM32VLDISCOVERY board commercially available from ST Microelectronics(R).
The program toggles the blue LED on `portc.8`.

The second ARM(R) Cortex(R)-M3 configuration (called `target stm32l100c`)
runs on the STM32L100 DISCOVERY board commercially available from
ST Microelectronics(R). The program toggles the blue LED on `portc.8`.

The third ARM(R) Cortex(R)-M3 configuration (called `target stm32l152`)
runs on the STM32L152C-DISCO board commercially available from
ST Microelectronics(R). The program toggles the blue LED on `portb.6`.

The first ARM(R) Cortex(R)-M4 configuration (called `target stm32f407`) runs on
the STM32F4DISCOVERY board commercially available from ST Microelectronics(R).
The program toggles the blue LED on `portd.15`.

Another ARM(R) Cortex(R)-M4 configuration (called `target stm32f446`) runs on
the STM32F446 Nucleo-64 board commercially available from ST Microelectronics(R).
The program toggles the green LED on `porta.5`.

The first ARM(R) Cortex(R)-M7 configuration (called `target stm32h7a3`) runs on
the STM32H7A3 Nucleo-144 board commercially available from ST Microelectronics(R).
The program toggles the green LED on `portb.0`.

The ARM(R) A8 configuration (called `target am335x`) runs on the BeagleBone
board (black edition). For the white edition, the CPU clock needs to be reduced
from $900~\text{MHz}$ to something like $600~\text{MHz}$. This project creates a bare-metal program
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

Target `v850es_fx2` uses a classic Renesas(R) V850es/Fx2 core.
The upd703231 microcontroller derivative on an F-Line _Drive_ _It_
starter kit is used.

The `riscvfe310` target utilizes the SiFive RISC-V FE310 SoC
on Spark Fun's commercially available _Red_ _Thing_ _Plus_ Board.
The blue LED on port `GPIO0.5` is toggled.

Target `nxp_imxrt1062` runs on the Teensy 4.0 board from Spark Fun.
The orange user-LED is toggled.

For other compatible boards, feel free contact me directly or submit
an issue requesting support for your desired target system.

## Benchmarks

[Benchmarks](./ref_app/src/app/benchmark)
provide scalable, portable means for identifying
the performance and the performance class of the microcontroller.
For more information, see the detailed information
on the [benchmarks](./ref_app/src/app/benchmark) pages.

## All Bare-Metal

Projects in this repo are programmed _OS-less_ in naked,
bare-metal mode making use of self-written startup code.
No external libraries other than native C++ and its own
standard libraries are used.

Consider, for instance, the BeagleBone Black Edition
(BBB, also known as `target am335x`) which is one
of several popular
target systems supported in this repository.
The projects on this board boot from the binary image file
_MLO_ on the SD card. Like all other projects in this repository,
the BBB projects perform their own
[static initialization](./ref_app/target/micros/am335x/startup)
and
[chip initialization](./ref_app/src/mcal/am335x/mcal_cpu_detail_secure.cpp)
(i.e., in this particular case chip initialization
of the ARM(R) 8 AM335x processor).
The BBB projects, following initialization,
subsequently jump to `main()` which
initializes the
[`am335x` MCAL](./ref_app/src/mcal/am335x)
and starts our self-written
[multitasking scheduler](./ref_app/src/os).

The image below
depicts the bare-metal BeagleBone Black Edition
in action. In this bare-metal operation mode, there is
no running `*nix` OS on the BBB, no keyboard,
no mouse, no monitor, no debug interface and no emulator.

The microcontroller on the board is cyclically performing
one of the [benchmarks](./ref_app/src/app/benchmark)
mentioned above. The first
user LED is toggled on `port1.21` in multitasking operation
and the oscilloscope captures
a real-time measurement of the benchmark's time signal
on digital I/O `port1.15`, header pin `P8.15` of the BBB.

![](./images/bare_metal_bbb.jpg)

## Continuous Integration (CI)

Continuous integration uses GitHub Actions programmed in YAML.
The [CI script](.github/workflows/real-time-cpp.yml)
exercises various target builds, example builds
and benchmark builds/runs on GitHub Actions' instances
of `ubuntu-latest`, `windows-latest` and `macos-latest`
using GNUmake, CMake or MSBuild
depending on the particular OS/build/target-configuration.

### Build Status

At the moment, there are distinct and separate, major individual builds.
Each build emphasizes different capabilities of the companion code.

  - Build `ref_app` and benchmarks for various targets and hosts on  both `*nix` as well as `Win*`.
  - Build the examples for selected hosts on `*nix`.
  - Build the code snippets for selected hosts on `*nix`.
  - Build the benchmarks for selected embedded targets and for selected hosts on `*nix`.

Here are the build status badges.

<p align="center">
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp.yml/badge.svg" alt="Build Status"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-examples.yml/badge.svg" alt="Build Examples"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-snippets.yml/badge.svg" alt="Build Snippets"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-benchmarks.yml/badge.svg" alt="Build Benchmarks"></a>
</p>

The build status badges represent the state of the nightly CI builds and tests.

## Modern `avr-gcc` Toolchain

The repo [ckormanyos/avr-gcc-build](https://github.com/ckormanyos/avr-gcc-build)
builds up-to-date `avr-gcc` toolchains for `x86_64-linux-gnu` and `x86_64-w64-mingw32`.
Shell and YAML scripts build `avr-gcc` directly from source on GHA runner(s).
In addition, occasional GitHub-releases provide pre-built
`avr-gcc` toolchains for `x86_64-linux-gnu` and `x86_64-w64-mingw32`.

This repo is a great place to learn how to build your own `avr-gcc` toolchain
from source. The straightforward, well-described shell and YAML scripts
are easy to understand, use or adapt.

As mentioned above, a much more detailed and wider scope
of embedded toolchains are described in
[ckormanyos/real-time-cpp-toolchains](https://github.com/ckormanyos/real-time-cpp-toolchains).
These include the afore-mentioned `avr-gcc` toolchain as well as others
(some hard-to-find elsewhere).

## GNU/GCC Compilers

The reference application and the examples (also the code snippets)
can be built with GNU/GCC compilers and GNUmake on `*nix`.
GNU/GCC cross compilers and GNUmake on `*nix` are assumed to
be available in the standard executable path,
such as after standard get-install practices.

Some ported GNU/GCC cross compilers for `Win*` are available in the
_toolchains_ repository,
[real-time-cpp-toolchains](https://github.com/ckormanyos/real-time-cpp-toolchains).
These can be used with the microcontroller solution configurations
in the reference application when developing/building
within Microsoft(R) VisualStudio(R). Various other GNU
tools such as GNUmake, SED, etc. have been ported
and can be found there. These are used in the Makefiles
When building cross embedded projects such as `ref_app`
on `Win*`.

In the reference application on `Win*`,
the Makefiles use a self-defined, default location
for the respective tools and GNU/GCC toolchains.
The toolchain default location on `Win*` is
`./ref_app/tools/Util/msys64/usr/local`.
This particular toolchain location is inspired by the
[`msys2`/`mingw64`](https://www.msys2.org)
system.

Toolchains intended for cross MSVC/GCC builds on `Win*`
should be located there.
These toolchains are not part of this repository
and it is necessary to get these toolchains separately
when using the supported `Win*` builds when optionally using
VisualStudio(R) Projects with CMD Batch.

Detailed instructions on getting and using the
toolchains for cross MSVC/GCC builds on `Win*`
are available in the
[real-time-cpp-toolchains](https://github.com/ckormanyos/real-time-cpp-toolchains)
repository. These instructions provide guidance on using these toolchains
when selecting the Microsoft(R) VisualStudio(R) project
(via the usual, above-described MSVC/`Win*`-way) to build the reference application.

## C++ Language Adherence

A GNU/GCC port (or other compiler)
with a high level of C++14 (or higher) awareness and adherence
such as GCC 5 through 13 (higher generally being more advantageous)
or MSVC 14.2 or higher is required for building the reference application
(and the examples and code snippets).

Some of the code snippets demonstrate language elements not only from C++14,
but also from C++17, 20, 23 and beyond. A compiler with C++17 support
or even C++20, 23 support (such as GCC 13, clang 15, MSVC 14.3, or higher) can,
therefore, be beneficial for success with *all* of the code snippets.
