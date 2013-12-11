
This is the companion code for the book "Real-Time C++".

See : C.M. Kormanyos, Real-Time C++: Efficient Object-Oriented and
Template Microcontroller Programming (Springer, Heidelberg, 2013).

Details on the Reference Application
------------------------------------

The reference application boots via a small startup code and subsequently
initializes a skinny microcontroller abstraction layer (MCAL). Control is
then passed to a simple multitasking scheduler which schedules the
LED application, a debug monitor task, a (predominantly empty) system task,
and an idle task. The idle task performs ROM and RAM integrity checks
and triggers the watchdog. The LED application toggles the LED with
a frequency of 1/2 Hz.

Supported Targets in the Reference Application
----------------------------------------------

The reference application supports the following targets:
  * Win32 in both Release and Debug modes
  * ATMEL(R) AVR(R) Atmega328P
  * ST microelectronics(R) STM32F10x ARM(R) Cortex(TM)-M3
  * BeagleBone with Texas Instruments AM335x ARM(R) A8
  * Under construction: Microchip(R) PIC(R)32, aka MIPS(R) 4K
  * Considered: Raspberry Pi with ARM(R) 11

Cross Development in the Reference Application
----------------------------------------------

The reference application uses cross-development based on *nix-like make tools
in combination with Microsoft(R) Visual Studio(R) 2012. The *nix-like
make tools have been built in MinGW.

The ATMEL(R) AVR(R) Atmega328P configuration in the reference application
also has a project workspace for ATMEL(R) Atmel Studio(R) 6.

Getting Started with the Reference Application
----------------------------------------------

It is easiest to get started with the reference application using one of the
supported boards, such as Arduino(R) or BeagleBone. The reference application
can be found in the directory ref_app and its subdirectories.

To get started with the reference application, start Visual Studio(R) 2012
and open the solution ref_app_vs2012.sln. Select the desired configuration
and then rebuild the entire solution. Note that the build in Visual Studio(R)
makes heavy use of cross development using a project workspace of type
"external makefile" to invoke GNUmake (via batch file) in combination
with several makefiles.

Upon successful build, the build results, such as the HEX-files, map files, etc.,
will be placed in the bin directory.

There is also a workspace solution for ATMEL(R) Atmel Studio(R) 6. It is called
ref_app.atsln.

Target Details
--------------

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
  * GCC 4.7.2 for avr-unknown-elf : For ATMEL(R) microcontrollers
  * GCC 4.7.2 for arm-unknown-eabi: For ARM(R) microcontrollers
  * (still needed) GCC for MIPS(R) 4K.

The compilers that are present have been built in MinGW and moved to
the solution. They have been subsequently stored in a convenient location
in the tools directory.

The make-files are aware of the location of their respective tool chains.
It is not necessary to add any kind of path information to the
PC operating system or to Visual Studio(R) in order to buld the
reference application.
