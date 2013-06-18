
This is the companion code for "Real-Time C++".

See the book:
C.M. Kormanyos, Real-Time C++: Efficient Object-Oriented and
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
  * Under construction: BeagleBone with ARM(R) A8
  * Considered: Microchip(R) PIC(R)32, aka MIPS(R)

Cross Development in the Reference Project
------------------------------------------

The reference project uses cross-development based on *nix-like make tools
in combination with Microsoft(R) Visual Studio(R) 2012. The *nix-like
make tools have been built in MinGW.

The ATMEL(R) AVR(R) Atmega328P configuration in the reference project
also has a project workspace for ATMEL(R) Atmel Studio(R) 6.

Getting Started
---------------

To get started, start Visual Studio(R) 2012 and open the solution ref_app_vs2012.sln.
Select the desired configuration and then rebuild the entire solution.

Upon successful build, the build results (such as the HEX-file, etc.) should apear
in the bin directory.

There is also a workspace solution for ATMEL(R) Atmel Studio(R) 6. It is called
ref_app.atsln.

Target Details
-----------------

The ATMEL(R) AVR(R) configuration runs on an Arduino(R) compatible board. It toggles
the yellow LED on portb.5.

The ARM(R) Cortex(TM)-M3 configuration runs on the STM32VLDISCOVERY board available
from ST Microelectronics(R). It toggles the blue LED on portc.8.

The GNU Compilers
-----------------

GCC ports for the microcontroller solutions are available in the directory:
  ref_app/tools/Util/MinGW/msys/1.0/local/*

The following compilers are available:
  GCC 4.7.2 for avr-unknown-elf, for ATMEL(R) AVR(R)
  GCC 4.7.2 for arm-unknown-eabi, for ARM(R) Cortex(TM)-M3

These compilers have been built in MinGW and moved to the solution.
