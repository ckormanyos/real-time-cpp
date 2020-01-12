# Example Chapter03_02
# Integer Types Having Fixed Widths and Prime Numbers

Example chapter03_02 focuses on integer types having fixed widths.
The example uses a fascinating calculation of prime numbers in order
to emphasize the usefullness and portability of fixed-width
integer types.

# Fixed-Width Integer Types

The code below asserts that the
<img src="https://render.githubusercontent.com/render/math?math=664,999^{th}">
prime number is
<img src="https://render.githubusercontent.com/render/math?math=10,006,721">.
This integer is stored in a fixed width
unsigned integer variable having 32 bits. The storage
is of type `constexpr`, which is compile-time constant.

```
#include <cstdint>

// Initialize the 664,999th prime number.

constexpr std::uint32_t prime_664999 = UINT32_C(10’006’721);
```

# Application Description

In the running code of Example03_02, the first 100 prime numbers are
calculated with a sieve method. The sieve-based prime number calculation
is realized within the application task of the software in the
cooperative multitasking scheduler.

We note that the
<img src="https://render.githubusercontent.com/render/math?math=100^{th}">
prime number is
<img src="https://render.githubusercontent.com/render/math?math=541">.
This can, for instance, be verified at [WolframAlpha](http://www.wolframalpha.com)
with the input `Prime[100]`.

# Prime Counting Function

The prime counting function fascinates mathematicians and
hobbyists alike. In the prime number theorem,
the prime counting function
is related to the logarithmic integral function via

<img src="https://render.githubusercontent.com/render/math?math=\text{Li}(x)-\pi(x)=O(\sqrt{x}\log{x})">,

where

<img src="https://render.githubusercontent.com/render/math?math=\text{Li}(x)=\text{li}(x)-\text{li}(2)">

and

<img src="https://render.githubusercontent.com/render/math?math=\text{li}(2)\approx{1.045}\ldots">.

See also this article on the [Prime-counting function](http://en.wikipedia.org/wiki/Prime-counting_function).

So for the
<img src="https://render.githubusercontent.com/render/math?math=664,999^{th}">
prime number, which is
<img src="https://render.githubusercontent.com/render/math?math=10,006,721">,
how close is the prime number theorem?

For the input

```
N[(LogIntegral[10006721] - LogIntegral[2])/664999, 20]
```

[WolframAlpha](http://www.wolframalpha.com) gives
<img src="https://render.githubusercontent.com/render/math?math=1.0005042653265034897">.
