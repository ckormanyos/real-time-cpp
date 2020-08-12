///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_2020_06_11_H_
  #define UTIL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_2020_06_11_H_

  namespace util {

  template <class UnsignedIntegralType,
            UnsignedIntegralType AxValue,
            UnsignedIntegralType CxValue,
            UnsignedIntegralType MxValue>
  UnsignedIntegralType linear_congruential_value(UnsignedIntegralType previous) noexcept
  {
    const std::uint64_t multiplier = std::uint64_t(std::uint64_t(previous) * AxValue) + CxValue;

    return UnsignedIntegralType(multiplier % MxValue);
  }

  template <class UnsignedIntegralType, UnsignedIntegralType CxValue, UnsignedIntegralType MxValue>
  UnsignedIntegralType linear_congruential_seed(UnsignedIntegralType s) noexcept
  {
    return s;
  }

  template <typename UnsignedIntegralType,
            const UnsignedIntegralType AxValue,
            const UnsignedIntegralType CxValue,
            const UnsignedIntegralType MxValue>
  class linear_congruential_engine
  {
  public:
      static_assert((MxValue == 0) || ((AxValue < MxValue) && (CxValue < MxValue)),
                    "Error: Bad parameters for linear_congruential_engine");

      using result_type                       = UnsignedIntegralType;
      static constexpr result_type multiplier = AxValue;
      static constexpr result_type increment  = CxValue;
      static constexpr result_type modulus    = MxValue;

      static constexpr result_type(min)() noexcept
      {
        return (CxValue == 0) ? result_type(1U) : result_type(0U);
      }

      static constexpr result_type(max)() noexcept
      {
        return static_cast<result_type>(MxValue - 1U);
      }

      static constexpr result_type default_seed = 1U;

      linear_congruential_engine() noexcept
        : my_previous(linear_congruential_seed<result_type, CxValue, MxValue>(default_seed)) { }

      explicit linear_congruential_engine(result_type s) noexcept
        : my_previous(linear_congruential_seed<result_type, CxValue, MxValue>(s)) { }

      void seed(result_type s = default_seed) noexcept
      {
        my_previous = linear_congruential_seed<result_type, CxValue, MxValue>(s);
      }

      result_type operator()() noexcept
      {
        my_previous = linear_congruential_value<result_type, AxValue, CxValue, MxValue>(my_previous);

        return my_previous;
      }

      void discard(unsigned long long skip) noexcept
      {
        result_type tmp = my_previous;

        for( ; 0U < skip; --skip)
        {
          tmp = linear_congruential_value<UnsignedIntegralType, AxValue, CxValue, MxValue>(tmp);
        }

        my_previous = tmp;
      }

  private:
      result_type my_previous;
  };

  using min_stdrand = util::linear_congruential_engine<std::uint_fast32_t,
                                                       UINT32_C(48271),
                                                       UINT32_C(0),
                                                       UINT32_C(2147483647)>;

  } // namespace util

#endif // UTIL_RANDOM_LINEAR_CONGRUENTIAL_ENGINE_2020_06_11_H_
