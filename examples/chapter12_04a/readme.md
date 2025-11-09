# Example Chapter12_04a (variation 32-bit controller)
## Benchmarking Floating-Point Calculations

Example chapter12_04a performs a variety of floating-point
calculations of selected special functions of pure and applied
mathematics.

## Selected Special Functions

The same special functions and arguments are used as in
Example Chapter12_04. In variation 12_04a, however,
the open-source 32-bit BL602 single-core RISC-V (SiFive E24)
microcontroller is used.

## Hardware Setup

In this particular example, we have simply used a commercially-available
BL602 single-core RISC-V (SiFive E24) board placed on a breadboard
with soldered-on pins.

The wiring is straightforward. The blinking LED uses an external green LED
controlled by pin `IO3`. THe benchmark toggle pin is `IO4`.
