# Code Snippets
## Chapter 10

This folder contains the code snippets for Chapter 10.

Some of the content and examples in Chapter 10 deal with high-precision
calculations of the fundamental constant $\pi$. Accordingly, some of the
Chapter 10 code snippets do as well.

## Try it at _godbolt_

<p align="center">
    <a href="https://godbolt.org/z/M68ojdzr4" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

Try the [`chapter10_08-000_pi_spigot_single.cpp`](./chapter10_08-000_pi_spigot_single.cpp)
program at this
[short link](https://godbolt.org/z/M68ojdzr4) to [godbolt](https://godbolt.org/).

This program computes ${\sim}~100,000$ decimal digits of $\pi$ using
a spigot-type algorithm, as described in great detail in Chapter 10 of the book.

## A million digits of $\pi$ at _godbolt_

<p align="center">
    <a href="https://godbolt.org/z/5cd4YonWq" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

The [`chapter10_08-001_pi_millions_with_boost.cpp`](./chapter10_08-001_pi_millions_with_boost.cpp)
program for computing ${\sim}~1,000,000$ decimal digits of $\pi$
can be found at this
[short link](https://godbolt.org/z/5cd4YonWq) to [godbolt](https://godbolt.org/).

It is fun and exciting to investigate this program and the underlying
high-precision AGM calculation at its foundation.
It performs the mega-digit $\pi$ calculation within a few seconds.

This program uses [Boost.Multiprecision](https://www.boost.org/doc/libs/1_84_0/libs/multiprecision/doc/html/index.html).
In particular, the [`gmp_float`](https://github.com/boostorg/multiprecision/blob/develop/include/boost/multiprecision/gmp.hpp)
backend is used. This C++ multiple-precision backend
wraps the high-precision, high-performance, C-language big-number-implementation
found in the [GMP](https://gmplib.org/) multiple precision arithmetic library.
