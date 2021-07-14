///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <app/benchmark/app_benchmark.h>

#if(APP_BENCHMARK_TYPE == APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1)

//#define APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1_USES_BUILTIN_DOUBLE

#if !defined (APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1_USES_BUILTIN_DOUBLE)
#define SOFT_DOUBLE_DISABLE_IOSTREAM
#endif

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numeric>

#if !defined (APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1_USES_BUILTIN_DOUBLE)
#include <math/softfloat/soft_double.h>
#endif

namespace local
{
  template<typename T>
  T hypergeometric_2f1(const T& AP, const T& BP, const T& CP, const T& ZM)
  {
    // Implement a rational approximation of hypergeometric_2f1.
    // This C++11 code uses a computational scheme similar to
    // one shown in Y.L. Luke, "Algorithms for the Comuptation
    // of Mathematical Functions", Academic Press, New York, 1977.
    // The original Fortran77 source can be found in the subroutine
    // R2F1() on pages 167-168. Slight corrections are made here
    // in order to repair one or two type-setting errors in the
    // original publication.

    // Luke's original Fortran77 and algorithmic work are fascinating
    // since they are generic and scalable --- decades ahead of their time.
    // Here, in fact, the calculation is scaled down to 15 decimal digits.
    // In other works of mine, the samp algorithm has been scaled up
    // to 1,001 decimal digits of precision --- proof of the remarkable
    // generic-ness of Luke's ground-breaking algorithms from a past
    // time epoch.

    // Retain some stylistic elements and comments from Luke's
    // original Fortran77 coding style.

    const T Z(-ZM);

    const T my_zero(0U);
    const T my_one (1U);

    // C
    // C INITIALIZATION :
    // C

          T SABZ((AP + BP) * Z);
    const T AB   (AP * BP);
    const T ABZ  (AB * Z);
    const T ABZ1((Z + ABZ) + SABZ);
    const T ABZ2((ABZ1 + SABZ) + (3U * Z));

    std::array<T, 4U> A;
    std::array<T, 4U> B;

    B[0U] = my_one;
    A[0U] = my_one;

    const T CP1(CP + my_one);

    B[1U] = my_one + (ABZ1 / (CP * 2U));
    A[1U] = B[1U]  - (ABZ  / CP);

    const T CT1(2U * CP1);

    B[2U] = my_one + ((ABZ2 / CT1) * (my_one + ABZ1 / ((-T(6U)) + (CT1 * 3U))));
    A[2U] = B[2U]  - ((ABZ  / CP)  * (my_one + ((ABZ2 - ABZ1) / CT1)));

    SABZ /= 4U;

    const T Z2(Z / 2U);

    std::array<T, 9U> D;

    D[0U] = (((T(7U) / 2U) - AB) * Z2) - SABZ;
    D[1U] = ABZ1 / 4U;
    D[2U] = D[1U] - (SABZ * 2U);
    D[3U] = CP1 + my_one;
    D[4U] = CP1 * D[3U];
    D[5U] = CP  * D[4U];
    D[6U] = T(3U) / 2U;
    D[7U] = T(3U) / 4U;
    D[8U] = D[7U] * Z;

    std::array<T, 3U> G;

    // C
    // C FOR I=3,...,N , THE VALUES A(I) AND B(I) ARE CALCULATED
    // C USING THE RECURRENCE RELATIONS BELOW.
    // C

    for(std::uint_fast16_t XI = UINT16_C(3); XI < UINT16_C(10000); ++XI)
    {
      G[2U]  = (D[2U] * D[1U]) / (D[7U] * D[5U]);
      D[1U] += (D[8U] + SABZ);
      D[2U] += (D[8U] - SABZ);
      G[2U] *= (D[1U] / D[6U]);
      G[0U]  =  my_one + ((D[1U] + D[0U]) / (D[6U] * D[3U]));
      G[1U]  =  D[1U] / (D[4U] * D[6U]);
      D[7U] += (D[6U] * 2U);
      ++D[6U];
      G[1U] *= ((CP1 - XI) - ((D[2U] + D[0U]) / D[6U]));

      // C -----------------------------------------------------------------
      // C THE RECURRENCE RELATIONS FOR A(I) and B(I) ARE AS FOLLOWS
      // C -----------------------------------------------------------------

      A[3U] = std::inner_product(G.crbegin(), G.crend(), A.cbegin(), my_zero);
      B[3U] = std::inner_product(G.crbegin(), G.crend(), B.cbegin(), my_zero);

      // Check if the iteration difference (delta) is within
      // tolerance and break from the recursion if it is.
      // Here we analyze the difference between this iteration
      // result and the previous iteration result using:
      //
      //         |     |(A2/B2)]| |
      // delta = | 1 - |--------| |
      //         |     |(A3/B3) | |
      //
      //         |     |(A2*B3)| |
      //       = | 1 - |-------| |,
      //         |     |(A3*B2)| |
      //
      // where the absolute value of the ratio in the second term
      // is used and the absolute value of delta is used.

      using std::fabs;

      const T ratio = fabs((A[2U] * B[3U]) / (A[3U] * B[2U]));
      const T delta = fabs(my_one - ratio);

      if((XI > UINT16_C(7)) && (delta < std::numeric_limits<T>::epsilon()))
      {
        break;
      }

      // Shift the arrays for the next recursion.
      std::copy(A.cbegin() + 1U, A.cend(), A.begin());
      std::copy(B.cbegin() + 1U, B.cend(), B.begin());

      D[8U] +=  Z2;
      D[0U] += (D[8U] * 2U);
      D[5U] += (D[4U] * 3U);
      D[4U] += (D[3U] * 2U);

      ++D[3U];
    }

    // Return the rational approximation. This is given
    // by the ratio of the final recursions of A and B.
    return A.back() / B.back();
  }
}

bool app::benchmark::run_soft_double_h2f1()
{
  #if defined (APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1_USES_BUILTIN_DOUBLE)
  using float64_t = double;
  #else
  using float64_t = math::softfloat::float64_t;
  #endif

  static_assert(std::numeric_limits<float64_t>::digits >= 53, "Error: incorrect float64_t type definition");

  const float64_t a( float64_t(2U) / 3U);
  const float64_t b( float64_t(4U) / 3U);
  const float64_t c( float64_t(5U) / 7U);
  const float64_t z(-float64_t(3U) / 4U);

  const float64_t h2f1 = local::hypergeometric_2f1(a, b, c, z);

  // N[Hypergeometric2F1[2/3, 4/3, 5/7, -3/4], 41]
  #if defined (APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1_USES_BUILTIN_DOUBLE)
  const float64_t control = 0.50100473608761064038202987077811306637010;
  #else
  const float64_t control(UINT64_C(0x3FE0083B15946592), math::softfloat::detail::nothing());
  #endif

  using std::fabs;

  const float64_t closeness = fabs(1 - fabs(h2f1 / control));

  const bool result_is_ok = closeness < (std::numeric_limits<float64_t>::epsilon() * 10);

  return result_is_ok;
}

#if defined(APP_BENCHMARK_STANDALONE_MAIN)
int main()
{
  // g++ -Wall -O3 -march=native -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_CRC -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_crc.cpp -o ./ref_app/bin/app_benchmark_crc.exe

  bool result_is_ok = true;

  for(unsigned i = 0U; i < 64U; ++i)
  {
    result_is_ok &= app::benchmark::run_soft_double_h2f1();
  }

  return result_is_ok ? 0 : -1;
}

#endif

#endif // APP_BENCHMARK_TYPE_CRC
