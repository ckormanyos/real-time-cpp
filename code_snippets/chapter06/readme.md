# Code Snippets
## Chapter 6

This folder contains the code snippets for Chapter 6.

## Try it at _godbolt_

<p align="center">
    <a href="https://godbolt.org/z/qGh6WMYvh" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

Try the [`chapter06_14-003_romable_initializer_list.cpp`](./chapter06_14-003_romable_initializer_list.cpp)
program at this
[short link](https://godbolt.org/z/qGh6WMYvh) to [godbolt](https://godbolt.org/).

## Higher-Level Host Programming Techniques

Chapter 6 covers a wide variety of optimization and best-practice techniques
relevant to the domain of real-time microcontroller programming.
Adapting the Chapter 6 snippets to the PC host has, accordingly,
made use of some higher-level C++ host programming methods.

  - Snippet [`chapter06_14-005_iterator_facade.cpp`](./chapter06_14-005_iterator_facade.cpp) makes use of Boost's iterator-facade library. See also this [short link](https://godbolt.org/z/8e7zPGErd) to [godbolt](https://godbolt.org/)
  - Snippets [`chapter06_15-001_minimize_interrupt_frame.cpp`](./chapter06_15-001_minimize_interrupt_frame.cpp) [`chapter06_15-002_minimize_interrupt_frame.cpp`](./chapter06_15-002_minimize_interrupt_frame.cpp) utilize the `<thread>` library and must be linked with _pthread_, as shown in CI. See also this [short link](https://godbolt.org/z/sv9x7qrfb) to [godbolt](https://godbolt.org/)
