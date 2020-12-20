///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

// This work is also based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef DECWIDE_T_DETAIL_FFT_2013_01_08_H_
  #define DECWIDE_T_DETAIL_FFT_2013_01_08_H_

  #include <array>
  #include <cstdint>

  namespace math { namespace wide_decimal { namespace detail { namespace fft {

  template<typename float_type>
  constexpr float_type template_half();

  template<>
  constexpr float template_half<float>() { return float(0.5L); }

  template<>
  constexpr double template_half<double>() { return double(0.5L); }

  template<>
  constexpr long double template_half<long double>() { return (long double) (0.5L); }

  template<typename float_type>
  float_type template_fast_div_by_two(float_type a);

  template<>
  inline float template_fast_div_by_two<float>(float a) { return a / 2; }

  template<>
  inline double template_fast_div_by_two<double>(double a) { return a / 2; }

  template<>
  inline long double template_fast_div_by_two<long double>(long double a) { return a / 2; }

  template<typename float_type>
  float_type template_sin_order_1(const std::uint32_t NumPoints)
  {
    // TBD: Use constexpr functions here, depending on availability.
    // Mathematica command: Table[N[Sin[Pi / (2^n)], 41], {n, 1, 31, 1}]
    switch(NumPoints)
    {
      default:
      case 0UL       : return float_type(0.0L);                                            // Pi        : as uint64_t --> UINT64_C(0x0000000000000000)
      case 2UL       : return float_type(1.0L);                                            // Pi / 2    : as uint64_t --> UINT64_C(0x3FF0000000000000)
      case 4UL       : return float_type(7.0710678118654752440084436210484903928484E-01L); // Pi / 4    : as uint64_t --> UINT64_C(0x3FE6A09E667F3BCD)
      case 8UL       : return float_type(3.8268343236508977172845998403039886676134E-01L); // Pi / 8    : as uint64_t --> UINT64_C(0x3FD87DE2A6AEA963)
      case 16UL      : return float_type(1.9509032201612826784828486847702224092769E-01L); // Pi / 16   : as uint64_t --> UINT64_C(0x3FC8F8B83C69A60B)
      case 32UL      : return float_type(9.8017140329560601994195563888641845861137E-02L); // Pi / 32   : as uint64_t --> UINT64_C(0x3FB917A6BC29B42C)
      case 64UL      : return float_type(4.9067674327418014254954976942682658314745E-02L); // Pi / 64   : as uint64_t --> UINT64_C(0x3FA91F65F10DD814)
      case 128UL     : return float_type(2.4541228522912288031734529459282925065466E-02L); // Pi / 128  : as uint64_t --> UINT64_C(0x3F992155F7A3667E)
      case 1UL <<  8U: return float_type(1.2271538285719926079408261951003212140372E-02L); // Pi / 2^8  : as uint64_t --> UINT64_C(0x3F8921D1FCDEC784)
      case 1UL <<  9U: return float_type(6.1358846491544753596402345903725809170579E-03L); // Pi / 2^9  : as uint64_t --> UINT64_C(0x3F7921F0FE670071)
      case 1UL << 10U: return float_type(3.0679567629659762701453654909198425189446E-03L); // Pi / 2^10 : as uint64_t --> UINT64_C(0x3F6921F8BECCA4BA)
      case 1UL << 11U: return float_type(1.5339801862847656123036971502640790799549E-03L); // Pi / 2^11 : as uint64_t --> UINT64_C(0x3F5921FAAEE6472E)
      case 1UL << 12U: return float_type(7.6699031874270452693856835794857664314092E-04L); // Pi / 2^12 : as uint64_t --> UINT64_C(0x3F4921FB2AECB360)
      case 1UL << 13U: return float_type(3.8349518757139558907246168118138126339503E-04L); // Pi / 2^13 : as uint64_t --> UINT64_C(0x3F3921FB49EE4EA6)
      case 1UL << 14U: return float_type(1.9174759731070330743990956198900093346887E-04L); // Pi / 2^14 : as uint64_t --> UINT64_C(0x3F2921FB51AEB57C)
      case 1UL << 15U: return float_type(9.5873799095977345870517210976476351187066E-05L); // Pi / 2^15 : as uint64_t --> UINT64_C(0x3F1921FB539ECF31)
      case 1UL << 16U: return float_type(4.7936899603066884549003990494658872746867E-05L); // Pi / 2^16 : as uint64_t --> UINT64_C(0x3F0921FB541AD59E)
      case 1UL << 17U: return float_type(2.3968449808418218729186577165021820094761E-05L); // Pi / 2^17 : as uint64_t --> UINT64_C(0x3EF921FB5439D73A)
      case 1UL << 18U: return float_type(1.1984224905069706421521561596988984804732E-05L); // Pi / 2^18 : as uint64_t --> UINT64_C(0x3EE921FB544197A1)
      case 1UL << 19U: return float_type(5.9921124526424278428797118088908617299872E-06L); // Pi / 2^19 : as uint64_t --> UINT64_C(0x3ED921FB544387BA)
      case 1UL << 20U: return float_type(2.9960562263346607504548128083570598118252E-06L); // Pi / 2^20 : as uint64_t --> UINT64_C(0x3EC921FB544403C1)
      case 1UL << 21U: return float_type(1.4980281131690112288542788461553611206918E-06L); // Pi / 2^21 : as uint64_t --> UINT64_C(0x3EB921FB544422C2)
      case 1UL << 22U: return float_type(7.4901405658471572113049856673065563715596E-07L); // Pi / 2^22 : as uint64_t --> UINT64_C(0x3EA921FB54442A83)
      case 1UL << 23U: return float_type(3.7450702829238412390316917908463317739740E-07L); // Pi / 2^23 : as uint64_t --> UINT64_C(0x3E9921FB54442C73)
      case 1UL << 24U: return float_type(1.8725351414619534486882457659356361712045E-07L); // Pi / 2^24 : as uint64_t --> UINT64_C(0x3E8921FB54442CEF)
      case 1UL << 25U: return float_type(9.3626757073098082799067286680885620193237E-08L); // Pi / 2^25 : as uint64_t --> UINT64_C(0x3E7921FB54442D0E)
      case 1UL << 26U: return float_type(4.6813378536549092695115518138540096959504E-08L); // Pi / 2^26 : as uint64_t --> UINT64_C(0x3E6921FB54442D16)
      case 1UL << 27U: return float_type(2.3406689268274552759505493419034844037886E-08L); // Pi / 2^27 : as uint64_t --> UINT64_C(0x3E5921FB54442D18)
      case 1UL << 28U: return float_type(1.1703344634137277181246213503238103798093E-08L); // Pi / 2^28 : as uint64_t --> UINT64_C(0x3E4921FB54442D18)
      case 1UL << 29U: return float_type(5.8516723170686386908097901008341396943900E-09L); // Pi / 2^29 : as uint64_t --> UINT64_C(0x3E3921FB54442D18)
      case 1UL << 30U: return float_type(2.9258361585343193579282304690689559020176E-09L); // Pi / 2^30 : as uint64_t --> UINT64_C(0x3E2921FB54442D18)
      case 1UL << 31U: return float_type(1.4629180792671596805295321618659637103743E-09L); // Pi / 2^31 : as uint64_t --> UINT64_C(0x3E1921FB54442D18)
    }
  }

  template<typename float_type>
  float_type template_sin_order_2(const std::uint32_t NumPoints)
  {
    return template_sin_order_1<float_type>(NumPoints / 2U);
  }

  // TBD: Use constexpr functions here, depending on availability.
  template<typename float_type,
           const bool is_forward_fft>
  float_type const_unique_wp_real_init(const std::uint32_t N,
                                       const bool = is_forward_fft,
                                       const typename std::enable_if<(is_forward_fft == true)>::type* = nullptr)
  {
    return template_sin_order_1<float_type>(N);
  }

  template<typename float_type,
           const bool is_forward_fft>
  float_type const_unique_wp_real_init(const std::uint32_t N,
                                       const bool = is_forward_fft,
                                       const typename std::enable_if<(is_forward_fft == false)>::type* = nullptr)
  {
    return -template_sin_order_1<float_type>(N);
  }

  template<typename float_type,
           const bool is_forward_fft>
  float_type const_unique_wp_imag(const std::uint32_t N,
                                  const bool = is_forward_fft,
                                  const typename std::enable_if<(is_forward_fft == true)>::type* = nullptr)
  {
    return template_sin_order_2<float_type>(N);
  }

  template<typename float_type,
           const bool is_forward_fft>
  float_type const_unique_wp_imag(const std::uint32_t N,
                                  const bool = is_forward_fft,
                                  const typename std::enable_if<(is_forward_fft == false)>::type* = nullptr)
  {
    return -template_sin_order_2<float_type>(N);
  }

  template<typename float_type,
           const bool is_forward_fft>
  float_type const_unique_wp_real(const std::uint32_t N) { return float_type(float_type(-2) * (  const_unique_wp_real_init<float_type, is_forward_fft>(N)
                                                                                               * const_unique_wp_real_init<float_type, is_forward_fft>(N))); }

  template<typename float_type,
           const bool is_forward_fft>
  void danielson_lanczos_apply_4_basecase(float_type* data);

  template<typename float_type,
           const bool is_forward_fft>
  void danielson_lanczos_apply(const std::uint32_t N,
                               float_type* data)
  {
    if(N == 8U)
    {
      danielson_lanczos_apply_4_basecase<float_type, is_forward_fft>(data);
      danielson_lanczos_apply_4_basecase<float_type, is_forward_fft>(data + N);
    }
    else
    {
      danielson_lanczos_apply<float_type, is_forward_fft>(N / 2U, data);
      danielson_lanczos_apply<float_type, is_forward_fft>(N / 2U, data + N);
    }

    float_type real_part = float_type(1);
    float_type imag_part = float_type(0);

    for(std::uint32_t i = static_cast<std::uint32_t>(0U); i < N; i += 2U)
    {
            float_type tmp_real = (real_part * data[i + (N + 0U)]) - (imag_part * data[i + (N + 1U)]);
      const float_type tmp_imag = (real_part * data[i + (N + 1U)]) + (imag_part * data[i + (N + 0U)]);

      data[i + (N + 0U)] = data[i + 0U] - tmp_real;
      data[i + (N + 1U)] = data[i + 1U] - tmp_imag;

      data[i + 0U] += tmp_real;
      data[i + 1U] += tmp_imag;

      tmp_real = real_part;

      real_part += (((tmp_real  * const_unique_wp_real<float_type, is_forward_fft>(N)) - (imag_part * const_unique_wp_imag<float_type, is_forward_fft>(N))));
      imag_part += (((imag_part * const_unique_wp_real<float_type, is_forward_fft>(N)) + (tmp_real  * const_unique_wp_imag<float_type, is_forward_fft>(N))));
    }
  }

  template<typename float_type,
           const bool is_forward_fft>
  void danielson_lanczos_apply_4_basecase(float_type* data)
  {
    const float_type tmp_real_2_0 = data[2U]; 
    const float_type tmp_imag_2_0 = data[3U]; 

    data[2U]  = data[0U] - tmp_real_2_0;
    data[3U]  = data[1U] - tmp_imag_2_0;
    data[0U] += tmp_real_2_0; 
    data[1U] += tmp_imag_2_0; 

    const float_type tmp_real_2_4 = data[2U + 4U]; 
    const float_type tmp_imag_2_4 = data[3U + 4U]; 

    data[2U + 4U]  = data[0U + 4U] - tmp_real_2_4;
    data[3U + 4U]  = data[1U + 4U] - tmp_imag_2_4;
    data[0U + 4U] += tmp_real_2_4; 
    data[1U + 4U] += tmp_imag_2_4; 

    float_type tmp_real = data[4U];
    float_type tmp_imag = data[5U];

    data[4U] = data[0U] - tmp_real;
    data[5U] = data[1U] - tmp_imag;

    data[0U] += tmp_real;
    data[1U] += tmp_imag;

    const float_type real_part(const_unique_wp_real<float_type, is_forward_fft>(4U) + float_type(1));
    const float_type imag_part(const_unique_wp_imag<float_type, is_forward_fft>(4U));

    tmp_real = (real_part * data[6U]) - (imag_part * data[7U]);
    tmp_imag = (real_part * data[7U]) + (imag_part * data[6U]);

    data[6U] = data[2U] - tmp_real;
    data[7U] = data[3U] - tmp_imag;

    data[2U] += tmp_real;
    data[3U] += tmp_imag;
  }

  template<typename float_type,
           const bool is_forward_fft>
  void fft_lanczos_fft(const std::uint32_t N,
                       float_type* data)
  {
    std::uint32_t j = static_cast<std::uint32_t>(1U);

    for(std::uint32_t i = static_cast<std::uint32_t>(1U); i < static_cast<std::uint32_t>(N << 1U); i += 2U)
    {
      if(j > i)
      {
        std::swap(data[j - 1U], data[i - 1U]);
        std::swap(data[j],      data[i]);
      }

      std::uint32_t m = N;

      while((m > static_cast<std::uint32_t>(1U)) && (j > m))
      {
        j  -= m;
        m >>= 1U;
      }

      j += m;
    }

    danielson_lanczos_apply<float_type, is_forward_fft>(N, data);
  }

  template<typename float_type,
           const bool is_forward_fft>
  void rfft_lanczos_rfft(const std::uint32_t N,
                         float_type* data,
                         const bool = is_forward_fft,
                         const typename std::enable_if<(is_forward_fft == true)>::type* = nullptr)
  {
    fft_lanczos_fft<float_type, true>(N / 2U, data);

    float_type real_part(float_type(1) + const_unique_wp_real<float_type, true>(N));
    float_type imag_part(                const_unique_wp_imag<float_type, true>(N));

    for(std::uint32_t i = static_cast<std::uint32_t>(1U); i < static_cast<std::uint32_t>(N >> 2U); ++i)
    {
      const std::uint32_t i1 = static_cast<std::uint32_t>(i + i);
      const std::uint32_t i3 = static_cast<std::uint32_t>(N - i1);

      const std::uint32_t i2 = static_cast<std::uint32_t>(1U + i1);
      const std::uint32_t i4 = static_cast<std::uint32_t>(1U + i3);

      {
        const float_type h1r = template_fast_div_by_two(data[i1] + data[i3]);
        const float_type h1i = template_fast_div_by_two(data[i2] - data[i4]);

        const float_type h2r = template_fast_div_by_two(data[i2] + data[i4]);
        const float_type h2i = template_fast_div_by_two(data[i1] - data[i3]);

        data[i1] = (+h1r + (real_part * h2r)) + (imag_part * h2i);
        data[i2] = (+h1i - (real_part * h2i)) + (imag_part * h2r);
        data[i3] = (+h1r - (real_part * h2r)) - (imag_part * h2i);
        data[i4] = (-h1i - (real_part * h2i)) + (imag_part * h2r);
      }

      const float_type tmp_real = real_part;

      real_part += (((tmp_real  * const_unique_wp_real<float_type, true>(N)) - (imag_part * const_unique_wp_imag<float_type, true>(N))));
      imag_part += (((imag_part * const_unique_wp_real<float_type, true>(N)) + (tmp_real  * const_unique_wp_imag<float_type, true>(N))));
    }

    const float_type f0_tmp = data[0U];

    data[0U] = f0_tmp + data[1U];
    data[1U] = f0_tmp - data[1U];
  }

  template<typename float_type,
           const bool is_forward_fft>
  void rfft_lanczos_rfft(const std::uint32_t N,
                         float_type* data,
                         const bool = is_forward_fft,
                         const typename std::enable_if<(is_forward_fft == false)>::type* = nullptr)
  {
    float_type real_part(float_type(1) + const_unique_wp_real<float_type, false>(N));
    float_type imag_part(                const_unique_wp_imag<float_type, false>(N));

    for(std::uint32_t i = static_cast<std::uint32_t>(1U); i < static_cast<std::uint32_t>(N >> 2U); ++i)
    {
      const std::uint32_t i1 = static_cast<std::uint32_t>(i + i);
      const std::uint32_t i3 = static_cast<std::uint32_t>(N - i1);

      const std::uint32_t i2 = static_cast<std::uint32_t>(1U + i1);
      const std::uint32_t i4 = static_cast<std::uint32_t>(1U + i3);

      const float_type h1r = template_fast_div_by_two(data[i1] + data[i3]);
      const float_type h1i = template_fast_div_by_two(data[i2] - data[i4]);

      const float_type h2r = template_fast_div_by_two(data[i2] + data[i4]);
      const float_type h2i = template_fast_div_by_two(data[i1] - data[i3]);

      data[i1] = (+h1r - (real_part * h2r)) - (imag_part * h2i);
      data[i2] = (+h1i + (real_part * h2i)) - (imag_part * h2r);
      data[i3] = (+h1r + (real_part * h2r)) + (imag_part * h2i);
      data[i4] = (-h1i + (real_part * h2i)) - (imag_part * h2r);

      const float_type tmp_real = real_part;

      real_part += (((tmp_real  * const_unique_wp_real<float_type, false>(N)) - (imag_part * const_unique_wp_imag<float_type, false>(N))));
      imag_part += (((imag_part * const_unique_wp_real<float_type, false>(N)) + (tmp_real  * const_unique_wp_imag<float_type, false>(N))));
    }

    const float_type f0_tmp = data[0U];

    data[0U] = template_fast_div_by_two(f0_tmp + data[1U]);
    data[1U] = template_fast_div_by_two(f0_tmp - data[1U]);

    fft_lanczos_fft<float_type, false>(N / 2U, data);
  }

  } } } } // namespace math::wide_decimal::detail::fft

#endif // DECWIDE_T_DETAIL_FFT_2013_01_08_H_
