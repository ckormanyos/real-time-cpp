Real-Time-C++ - Examples
==================

<p align="center">
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-examples.yml/badge.svg" alt="Build Examples"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/blob/master/LICENSE_1_0.txt">
        <img src="https://img.shields.io/badge/license-BSL%201.0-blue.svg" alt="Boost Software License 1.0"></a>
    <a href="https://godbolt.org/z/fxWzb6h6f" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

﻿These examples are motivated by the book
C.M. Kormanyos,
[Real-Time C++](https://www.springer.com/de/book/9783662629956):
Efficient Object-Oriented
and Template Microcontroller Programming, Fourth Edition
(Springer, Heidelberg, 2021) ISBN 9783662629956.

The first couple of example projects can use the ARDUINO board directly
and non-modified. Examples from the later chapters in the book do, however,
need additional components at times. These need to be provided independently.

Consider, for instance,
[example chapter04_04](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter04_04).
It employs a self-fitted DIY custom breadboard.
Other examples use even higher levels of customization such as
[example chapter10_08a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter10_08a)
which requires sophistocated breadboard and laboratory techniques,
providing a DIY challenge at an advanced level.

## Summary of the Examples

Example ![chapter02_02](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter02_02) The LED program.\
This example implements the LED program (blinky) for the target with the 8-bit microcontroller.

Example ![chapter02_03](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter02_03) The LED program with timing.\
This example implements the LED program (with timing) for the target with the 8-bit microcontroller.

Example ![chapter02_03a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter02_03a) The LED program with cooperative multitasking scheduler.\
This example implements the LED program with a tiny cooperative multitasking scheduler for the target with the 8-bit microcontroller.

Example ![chapter02_06](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter02_06) The Led Program (with template LED class).\
This example implements the LED program with a template LED class for the target with the 8-bit microcontroller.

Example ![chapter03_02](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter03_02) Integer Types Having Fixed Widths and Prime Numbers.\
This example focuses on integer types having fixed widths using a fascinating calculation
of prime numbers that is simultaneously intended to emphasize the usefullness and portability
of fixed-width integer types.

Example ![chapter04_04](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter04_04) LED Objects and Polymorphism.\
This example exhibits object oriented polymorphism through
an intuitive LED class hierarchy. Base class pointers stored in an
`std::array` are used in combination with dynamic polymorphism.

Example ![chapter04_04a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter04_04a) LED Objects and Polymorphism via References.\
This example exhibits object oriented polymorphism in essentially the same
way as in example chapter04_04. In example chapter04_04a, however, we use base class
references instead of base class pointers stored in an `std::array`
in order to utilitze object oriented polymorphism.

Example ![chapter06_01](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter06_01) A CRC Benchmark.\
This example illustrates certain optimization techniques through the calculation
of a standard CRC32 checksum (cycle redundancy check).

Example ![chapter06_14](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter06_14) A CRC Benchmark with ROM-Based Table and Data.\
This example features essentially the same functionality as example chapter06_01.
The checksum table and benchmark data, however, are ROM-able.

Example ![chapter09_07](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter09_07) Controlling a Seven Segment Display.\
This example makes use of object oriented programming methods to control a seven segment display.

Example ![chapter09_08](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter09_08) Controlling an RGB LED.\
This example utilizes object oriented programming techniques to control an RGB LED.

Example ![chapter09_08a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter09_08a) Controlling an RGB LED of Type WS2812.\
This example controls an RGB LED using programming techniques similar to those used in the previous example.
There are, however, several differences such as the refactored, modernized LED-class hierarchy.
The main difference, however, is that a _digitally_-controlled industry-standard
RGB LED of type WS2812 is used. In addition, the color transitions at and around $255~\text{bits}$-RGB
are slowed down providing emphasized, longer-lasting RGB hues near these points.

Example ![chapter09_08b](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter09_08b) Controlling an RGB LED of Type WS2812  (variation 32-bit microcontroller).\
Example chapter09_08b utilizes essentially the same techniques to control its ws2812 RGB LED
as were used in Example Chapter09_08a. In variation 09_08b, however,
the open-platform [STM32F100 Value Line Discovery Kit](https://www.st.com/en/evaluation-tools/stm32vldiscovery.html)
is used.


Example ![chapter10_08](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter10_08) External SPI RAM and Computing $10,001$ Digits of Pi.\
This advanced example extends available RAM via SPI SRAM chips and uses a Pi Spigot algorithm
to compute $10,001$ digits of the mathematical constant $\pi$
showing fascinating memory management iterators, containers and algorithms along the way.
This example depicts algorithmic complexity running in a real-world system
and highlights the real-time numeric expression of the detailed description
of algorithmic complexity in the corresponding book section.

Example ![chapter10_08a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter10_08a) Parallel SRAM and Computing $100,001$ Digits of Pi.\
This advanced example extends RAM even further with a $2~\text{MByte}$ parallel SRAM brick. This extended memory
is used for storage in Pi Spigot calculations
of the mathematical constant $\pi$ up to $100,001$ decimal digits.

Example ![chapter10_09](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter10_09) $100,001$ Digits of Pi on Raspberry Pi(R).\
This advanced example ports the Pi Spigot calculation
of $100,001$ decimal digits of $\pi$
to the powerful ARM(R)-based Raspberry Pi(R) single-board computer.

Example ![chapter11_07](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter11_07) Preemptive Multitasking.\
This example makes straightforward use of preemptive multitasking scheduling with a blinky-style application that features a main task and a low-priority background task.

Example ![chapter11_07a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter11_07a) Preemptive Multitasking and an Advanced, Memory-Intensive Mathematical Calculation.\
In this example, advanced use of preemptive multitasking scheduling is used to combine a blinky-style application with a highly detailed and exciting calculation of the mathematical constant $\pi$ to high precision in the background task.

Example ![chapter12_04](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter12_04) Benchmarking Floating-Point Calculations.\
This example performs a variety of floating-point calculations of selected special functions of pure and applied mathematics.

Example ![chapter12_04a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter12_04a) Benchmarking Floating-Point Calculations (variation 32-bit microcontroller).\
The same special functions and arguments are used as in Example Chapter12_04. In variation 12_04a, however,
the open-platform [STM32F100 Value Line Discovery Kit](https://www.st.com/en/evaluation-tools/stm32vldiscovery.html)
is used directly out-of-the-box.

Example ![chapter16_08](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter16_08) Generating and displaying 128-bit Random Prime Numbers.\
This advanced example uses an extended integer class to create 128-bit unsigned prime integers with primality testing performed via Miller-Rabin.
This example also provides fascinating, intuitive, visual insight into the prime number theory of pure mathematics.

Example ![chapter17_03](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter17_03) Traditional C Language Code in a Modern C++ Project.\
This example depicts some methods that potentially allow the successful use
of traditional C-language code within a modern C++ project.

Example ![chapter17_03a](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter17_03a) Traditional C-Language in Modern C++, Using Time Slices.\
This example is almost identical with example chapter17_03. In fact, it performs
the same CRC calculations and uses essentially the same code technical methods
for accessing traditional C-language code within a modern C++ project.
Example chapter17_03a, however, distributes the CRC calculations
over multitasking using time slices.

## Further Information on the Examples

For further informatin on the examples, see the readme notes
in each individual example directory.

## Try it at _godbolt_

<p align="center">
    <a href="https://godbolt.org/z/fxWzb6h6f" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

Use this [short link](https://godbolt.org/z/fxWzb6h6f)
to [godbolt](https://godbolt.org) in order to further explore
Example ![chapter02_02](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter02_02)
(the LED program). In the link, the main source file of the example
is compiled with a modern `avr-gcc` compiler and the compiler-generated
assembly listing can also be investigated.
