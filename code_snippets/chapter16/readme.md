# Code Snippets
## Chapter 16

This folder contains the code snippets for Chapter 16.

## Try it at _godbolt_

<p align="center">
    <a href="https://godbolt.org/z/TcxxEG6sK" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

Try the [`chapter16_08-001_random_engine.cpp`](./chapter16_08-001_random_engine.cpp)
program at this
[short link](https://godbolt.org/z/TcxxEG6sK) to [godbolt](https://godbolt.org/).

This program creates a mock-up of a non-cryptographic, _toy_ random engine.
It uses a combination of both the time-and-date functions of C/C++ as well as
a 64-bit standard CRC to create a pseudo-random seed for
a self-written random engine. This engine is subsequently used to seed
a standard generator that makes sequences of random numbers.
