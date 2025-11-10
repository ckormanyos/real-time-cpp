# Example Chapter12_04a (variation 32-bit microcontroller)
## Benchmarking Floating-Point Calculations

Example chapter12_04a performs a variety of floating-point
calculations of selected special functions of pure and applied
mathematics.

## Selected Special Functions

The same special functions and arguments are used as in
Example Chapter12_04. In variation 12_04a, however,
a 32-bit, single-core ARM(R) Cortex(R)-M3 microcontroller
is used.

## Hardware Setup

In this particular example, we have simply used
the commercially-available, open-platform
[STM32F100 Value Line Discovery Kit](https://www.st.com/en/evaluation-tools/stm32vldiscovery.html)
directly out-of-the-box.

The wiring is straightforward. The blinking LED uses the blue colored
user LED controlled by pin `portc.8`. The benchmark toggle pin is `portb.9`.
The microcontroller is clocked at $24~\text{MHz}$.
