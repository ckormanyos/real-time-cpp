
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _APP_BENCHMARK_FPU_HYPERGEOMETRIC_2014_04_29_H_
  #define _APP_BENCHMARK_FPU_HYPERGEOMETRIC_2014_04_29_H_

  #include <algorithm>
  #include <array>
  #include <functional>
  #include <limits>
  #include <numeric>
  #include <vector>
  #include <util/memory/util_ring_allocator.h>

  template <class T,
            class iterator_a_type,
            class iterator_b_type>
  T hypergeometric_pfq(iterator_a_type coefficients_a_begin,
                       iterator_a_type coefficients_a_end,
                       iterator_b_type coefficients_b_begin,
                       iterator_b_type coefficients_b_end,
                       T x)
  {
    // Compute the Taylor series expansion of:
    // hypergeometric_pfq[{a0, a1, a2, ... an}; {b0, b1, b2, ... bm}, x].

    T x_pow_n_div_n_fact(x);

    // The pochhammer symbols for the multiplications in the series expansion
    // will be stored in STL-containers.
    std::vector<T, util::ring_allocator<T> > an(coefficients_a_begin, coefficients_a_end);
    std::vector<T, util::ring_allocator<T> > bm(coefficients_b_begin, coefficients_b_end);

    const T my_one(1);

    // Initialize the pochhammer product terms with the products of the form:
    // [(a0)_1 * (a1)_1 * (a2)_1 * ...], or [(b0)_1 * (b1)_1 * (b2)_1 * ...].
    T pochhammer_sequence_a = std::accumulate(an.begin(), an.end(), my_one, std::multiplies<T>());
    T pochhammer_sequence_b = std::accumulate(bm.begin(), bm.end(), my_one, std::multiplies<T>());

    // Calculate the first term in the Taylor series expansion.
    // Use either: (an * (x^n / n!)) / bn
    // or else use: (an / bn) * (x^n / n!)
    // based on whether or not (x^n / n!) > 1.
    const T first_term = ((x_pow_n_div_n_fact > 1)
                           ? T((pochhammer_sequence_a / pochhammer_sequence_b) * x_pow_n_div_n_fact)
                           : T((pochhammer_sequence_a * x_pow_n_div_n_fact) / pochhammer_sequence_b));

    T hypergeometric_pfq_result = my_one + first_term;

    int n;

    // Calculate the maximum number of iterations allowed.
    const int max_iteration = std::numeric_limits<T>::digits10 * 10;

    for(n = 2; n < max_iteration; ++n)
    {
      x_pow_n_div_n_fact *= x;
      x_pow_n_div_n_fact /= n;

      // Increment each of the pochhammer elements in {an} and {bm}.
      std::for_each(an.begin(), an.end(), [](T& a) { ++a; });
      std::for_each(bm.begin(), bm.end(), [](T& b) { ++b; });

      // Multiply the pochhammer product terms with the products of the incremented
      // pochhammer elements. These are products of the form:
      // [(a0)_k * (a1)_k * (a2)_k * ...], or [(b0)_k * (b1)_k * (b2)_k * ...].
      pochhammer_sequence_a *= std::accumulate(an.begin(), an.end(), my_one, std::multiplies<T>());
      pochhammer_sequence_b *= std::accumulate(bm.begin(), bm.end(), my_one, std::multiplies<T>());

      // Calculate the next term in the Taylor series expansion.
      // Use either: (an * (x^n / n!)) / bn
      // or else use: (an / bn) * (x^n / n!)
      // based on whether or not (x^n / n!) > 1.
      const T next_term = ((x_pow_n_div_n_fact > 1)
                            ? T((pochhammer_sequence_a / pochhammer_sequence_b) * x_pow_n_div_n_fact)
                            : T((pochhammer_sequence_a * x_pow_n_div_n_fact) / pochhammer_sequence_b));

      using std::fabs;

      if((n > 9) && (fabs(next_term) < std::numeric_limits<T>::epsilon()))
      {
        break;
      }

      hypergeometric_pfq_result += next_term;
    }

    if(n < max_iteration)
    {
      return hypergeometric_pfq_result;
    }
    else
    {
      return T();
    }
  }

#endif // _APP_BENCHMARK_FPU_HYPERGEOMETRIC_2014_04_29_H_
