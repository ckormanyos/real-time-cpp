
## These examples are motivated from the book "Real-Time C++".

See : C.M. Kormanyos, Real-Time C++: Efficient Object-Oriented
and Template Microcontroller Programming, Third Edition
(Springer, Heidelberg, 2018). ISBN 9783662567173

## Summary of the Examples

Example ![chapter02_02](./chapter02_02) The LED program.\
This example implements the LED program (blinky) for the target with the 8-bit microcontroller.

Example ![chapter02_03](./chapter02_03) The LED program with timing.\
This example implements the LED program (with timing) for the target with the 8-bit microcontroller.

Example ![chapter02_03a](./chapter02_03a) The LED program with cooperative multitasking scheduler.\
This example implements the LED program with a tiny cooperative multitasking scheduler for the target with the 8-bit microcontroller.

Example ![chapter02_06](./chapter02_06) The Led Program (with template LED class).\
This example implements the LED program with a template LED class for the target with the 8-bit microcontroller.

Example ![chapter03_02](./chapter03_02) Integer Types Having Fixed Widths and Prime Numbers.\
This example focuses on integer types having fixed widths using a fascinating calculation
of prime numbers that is simultaneously intended to emphasize the usefullness and portability
of fixed-width integer types.

Example ![chapter04_04](./chapter04_04) LED Objects and Polymorphism.\
This example exhibits object oriented polymorphism through
an intuitive LED class hierarchy. Base class pointers stored in an
`std::array` are used in combination with dynamic polymorphism.

Example ![chapter04_04a](./chapter04_04a) LED Objects and Polymorphism via References.\
This example exhibits object oriented polymorphism in essentially the same
way as in example chapter04_04. In example chapter04_04a, however, we use base class
references instead of base class pointers stored in an `std::array`
in order to utilitze object oriented polymorphism.

Example ![chapter06_01](./chapter06_01) A CRC Benchmark.\
This example illustrates certain optimization techniques through the calculation
of a standard CRC32 checksum (cycle redundancy check).

Example ![chapter06_14](./chapter06_14) A CRC Benchmark with ROM-based Table and Data.\
This example features essentially the same functionality as example chapter06_01.
The checksum table and benchmark data, however, are ROM-able.

Example ![chapter09_07](./chapter09_07) Controlling a Seven Segment Display.\
This example makes use of object oriented programming methods to control a seven segment display.

Example ![chapter09_08](./chapter09_08) Controlling an RGB LED.\
This example utilizes object oriented programming techniques to control an RGB LED.

Example ![chapter12_04](./chapter12_04) Floating-Point Calculations.\
This example performs a variety of floating-point calculations
of selected special functions of pure and applied mathematics.

Example ![chapter17_03](./chapter17_03) Traditional C Language Code in a Modern C++ Project.\
This example depicts some methods that potentially allow the successful use
of traditional C-language code within a modern C++ project.

Example ![chapter17_03a](./chapter17_03a) Traditional C-Language in Modern C++, Using Time Slices.\
This example is almost identical with example chapter17_03. In fact, it performs
the same CRC calculations and uses essentially the same code technical methods
for accessing traditional C-language code within a modern C++ project.
Example chapter17_03a, however, distributes the CRC calculations
over multitasking using time slices.

## Further Information on the Examples

For further informatin on the examples, see the readme notes
in each individual example directory.
