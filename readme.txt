
This is the companion code for the book "Real-Time C++".

See : C.M. Kormanyos, Real-Time C++: Efficient Object-Oriented and
Template Microcontroller Programming (Springer, Heidelberg, 2013).

Details on the Reference Project
--------------------------------

The reference project boots via a small startup code and subsequently initializes
a skinny microcontroller abstraction layer (MCAL). Control is then passed to a
simple multitasking scheduler which schedules the LED application and an (empty)
system task. The LED application toggles the LED with a frequency of 1/2 Hz.

Supported Targets in the Reference Project
------------------------------------------

The reference project supports the following targets:
  * Win32 in both Release and Debug modes
  * ATMEL(R) AVR(R) Atmega328P
  * ST microelectronics(R) STM32F10x ARM(R) Cortex(TM)-M3
  * BeagleBone with Texas Instruments AM335x ARM(R) A8
  * Under construction: Microchip(R) PIC(R)32, aka MIPS(R)
  * Considered: Raspberry Pi with ARM(R) 11

Cross Development in the Reference Project
------------------------------------------

The reference project uses cross-development based on *nix-like make tools
in combination with Microsoft(R) Visual Studio(R) 2012. The *nix-like
make tools have been built in MinGW.

The ATMEL(R) AVR(R) Atmega328P configuration in the reference project
also has a project workspace for ATMEL(R) Atmel Studio(R) 6.

Getting Started
---------------

It is easiest to get started with the reference application using one of the
supported boards, such as Arduino(R) or BeagleBone. The reference application
is in the directory ref_app.

To get started with the reference application, start Visual Studio(R) 2012
and open the solution ref_app_vs2012.sln. Select the desired configuration
and then rebuild the entire solution. Note that this is cross development
using Visual Studio(R) 2012 to invoke an external makefile subsequently
built with GNUmake.

Upon successful build, the build results (such as the HEX-file, etc.)
will be placed in the bin directory.

There is also a workspace solution for ATMEL(R) Atmel Studio(R) 6. It is called
ref_app.atsln.

Target Details
-----------------

The ATMEL(R) AVR(R) configuration runs on an Arduino(R) compatible board.
The program toggles the yellow LED on portb.5.

The ARM(R) Cortex(TM)-M3 configuration runs on the STM32VLDISCOVERY board available
from ST Microelectronics(R). The program toggles the blue LED on portc.8.

The ARM(R) A8 configuration runs on the BeagleBone board. There is support for both
the black edition as well as the white edition. This is a bare-metal program for
the BeagleBone. The program is designed to boot the BeagleBone from a binary file
called "MLO" stored on a FAT32 SDHC microcard. The binary file includes a special
boot header comprised of two 32-bit integers. The program is loaded from SD-card
into RAM memory and subsequently executed. The program toggles the first user
LED1 on port1.21.

The GNU Compilers
-----------------

GCC ports for the microcontroller solutions are available in the directory:
  ref_app/tools/Util/MinGW/msys/1.0/local/*

The following compilers are available:
  GCC 4.7.2 for avr-unknown-elf : For ATMEL(R) AVR(R)
  GCC 4.7.2 for arm-unknown-eabi: For ARM(R) Cortex(TM)-M3 and ARM(R) A8
  (still needed) GCC for MIPS 4K.

The compilers that are present have been built in MinGW and moved to
the solution. They have been subsequently stored in a convenient location
in the tools directory. The make-files are aware of the location of their
respective tool chains and it is not necessary to add any kind of path
information to the PC operating system or to Visual Studio(R).
