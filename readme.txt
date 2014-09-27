
This is the companion code for the book "Real-Time C++".

See : C.M. Kormanyos, Real-Time C++: Efficient Object-Oriented and
Template Microcontroller Programming (Springer, Heidelberg, 2013).

Details on the Reference Application
------------------------------------

The reference application boots via a small startup code and subsequently
initializes a skinny microcontroller abstraction layer (MCAL). Control is
then passed to a simple multitasking scheduler that schedules the
LED application, services a debug monitor, and triggers the watchdog.
The LED application toggles the LED with a frequency of 1/2 Hz.

Supported Targets in the Reference Application
----------------------------------------------

The reference application supports the following targets:
  * Win32 in both Release and Debug modes
  * ATMEL(R) AVR(R) Atmega328P
  * ST microelectronics(R) STM32F100 ARM(R) Cortex(TM)-M3
  * ST microelectronics(R) STM32F407 ARM(R) Cortex(TM)-M4
  * ST microelectronics(R) STM32F429 ARM(R) Cortex(TM)-M4
  * BeagleBone with Texas Instruments(R) AM3359 ARM(R) A8
  * Renesas(R) RL78/G13
  * Renesas(R) RX600
  * Microchip(R) PIC(R)32 MIPS4K
  * Raspberry Pi with ARM(R) 11

Cross Development in the Reference Application
----------------------------------------------

The reference application uses cross-development based on *nix-like make
tools in combination with Microsoft(R) Visual Studio(R). Tool chains
are not available in this repo (see below for further details).

The ATMEL(R) AVR(R) Atmega328P configuration in the reference application
also has a project workspace for ATMEL(R) Atmel Studio(R) 6.

Getting Started with the Reference Application
----------------------------------------------

It is easiest to get started with the reference application using one of the
supported boards, such as Arduino or RaspberryPi or BeagleBone. etc.
The reference application can be found in the directory ref_app and its
subdirectories.

To get started with the reference application, start Visual Studio(R) 2012
(or later) and open the solution ref_app_vs2012.sln. Select the desired
configuration. Then rebuild the entire solution. Note that the build in
Visual Studio(R) makes heavy use of cross development using a project
workspace of type "external makefile" to invoke GNUmake (via batch file)
in combination with several makefiles.

To build any target other than Debug or Release for Win32, a cross-compiler
(GNU GCC cross compiler) is required. See the text below for additional
details.

Upon successful build, the build results, such as the HEX-files, map files, etc.,
will be placed in the bin directory.

There is also a workspace solution for ATMEL(R) Atmel Studio(R) 6. It is called
ref_app.atsln.

Target Details
--------------

Target details including startup code and linker definition files can
be found in the target-directory and its subdirectories.

The ATMEL(R) AVR(R) configuration runs on an Arduino(R) compatible board.
The program toggles the yellow LED on portb.5.

The ARM(R) Cortex(TM)-M3 configuration (called "target stm32f100") runs on
the STM32VLDISCOVERY board commercially available from ST Microelectronics(R).
The program toggles the blue LED on portc.8.

The ARM(R) A8 configuration (called "target am335x") runs on the BeagleBone
board (black edition). For the white edition, the CPU clock needs to be reduced
from 900MHz to something like 600MHz. This project creates a bare-metal program
for the BeagleBone that runs independently form any kind of *nix distro on
the board. Our program is designed to boot the BeagleBone from a raw binary file
called "MLO" stored on a FAT32 SDHC microcard. The binary file includes a
special boot header comprised of two 32-bit integers. The program is loaded
from SD-card into RAM memory and subsequently executed. When switching on
the BeagleBone black, the boot button (S2) must be pressed while powering
up the board. The program toggles the first user LED (LED1 on port1.21).

The ARM(R) 11 configuration (called "target bcm2835_raspi_b") runs on the
RaspberryPi-B. This project creates a bare-metal program for the RaspberryPi.
This program runs independently form any kind of *nix distro on the board.
Our program is designed to boot the RaspberryPi from a raw binary file.
The raw binary file is called "kernel.img" and it is stored on a FAT32 SDHC
microcard. The kernel.img file is stored on the SD card together with two
other files: bootcode.bin and start.elf, both available from internet.

For other compatible boards, feel free contact me with an issue requesting
further details on your desired target system.

GNU GCC Compilers
-----------------

GNU GCC cross compilers for the microcontroller solutions are *not*
available here.

A GNU GCC port with a relatively high level of C++11 awareness such as
GCC 4.8 or higher is required for building the reference application.

The make-files are aware of the location of a default location of the
respective tool chain. When using the reference application or designing
a custom build, the root directory of the tool chain must be properly
supplied to the makefiles.
