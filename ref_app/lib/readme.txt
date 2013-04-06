
-----------------------------------------------
Description of libcrtavr.a
-----------------------------------------------

The library archive libcrtavr.a can be used as
startup code for bare bones C++ projects for
the AVR(R) ATmega(R) such as on the Arduino(R).

The symbols in the interrupt vector table are
qualified with "weak" and can be overwritten
in the user code. These symbols need to be
named: __vector_2, 3, 4, etc.

A "clean" startup without watchdog trigger
or chip initialization has been used.

Some common patch stuff from the gcc_patch 
has been included.
