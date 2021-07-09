# Example Chapter16_08
# Generating and displaying 128-bit Random Prime Numbers

This advanced example uses an extended integer class
to create 128-bit random unsigned prime integers with
primality testing performed via Miller-Rabin.

This example also provides fascinating, intuitive,
visual insight into the prime number theorem
of pure mathematics.

# Application Description

This project uses a hardware electronic subcircuit to generate random noise.
Bits are collected from the digitized random noise and used
to create random 128-bit pseudo-prime numbers.
Primality testing uses the Miller-Rabin algorithm.
The [wide-integer](https://github.com/ckormanyos/wide-integer)
project is used to implement 128-bit unsigned integers.

In this example, Miller-Rabin testing has been implemented as a state machine.
The individual states of the prime testing machine are serviced within the
time slices of the multitasking scheduler.
Representation of the 128-bit integers is in hexadecimal format
on an LCD module havint width of 40 characters.

The electronic subcircuit used for creating the random digitized noise
is sketched below.

![](./images/circuit16_08.svg).

The oscilloscope image below shows a small snapshot
of the random digitized noise from this circuit.

![](./images/signal16_08.jpg)

# Deep Connection to the Prime Number Theorem

TBD

# Hardware Setup

The target hardware featuring the is shown in the following image.

![](./images/board16_08.jpg)
