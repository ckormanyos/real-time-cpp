///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MILLER_RABIN_SINGLE_2020_05_30_H_
  #define MILLER_RABIN_SINGLE_2020_05_30_H_

  #include <math/wide_integer/miller_rabin/miller_rabin_base.h>

  WIDE_INTEGER_NAMESPACE_BEGIN

  namespace math { namespace wide_integer {

  template<typename Generator1Type,
           typename Generator2Type,
           const size_t Digits2,
           typename LimbType>
  class miller_rabin_single : public miller_rabin_base<Generator1Type,
                                                       Generator2Type,
                                                       Digits2,
                                                       LimbType>
  {
  private:
    using base_class_type = miller_rabin_base<Generator1Type,
                                              Generator2Type,
                                              Digits2,
                                              LimbType>;

  public:
    constexpr miller_rabin_single(const typename base_class_type::generator1_type::result_type seed1 = typename base_class_type::generator1_type::result_type(),
                                  const typename base_class_type::generator2_type::result_type seed2 = typename base_class_type::generator2_type::result_type())
      : base_class_type(seed1, seed2) { }

    virtual ~miller_rabin_single() = default;

    virtual bool search()
    {
      while(base_class_type::set_n() == false)
      {
        ;
      }

      calculate();

      if(base_class_type::my_n_trial_is_probably_prime)
      {
        base_class_type::my_n_is_probably_prime = true;
      }

      return true;
    }

  private:
    void calculate()
    {
      // This Miller-Rabin primality test is loosely based on
      // an adaptation of some code from Boost.Multiprecision.
      // The Boost.Multiprecision code can be found here:
      // https://www.boost.org/doc/libs/1_73_0/libs/multiprecision/doc/html/boost_multiprecision/tut/primetest.html

      // Note: Some comments in this subroutine use the Wolfram Language(TM).

      // Check small prime factors.
      if(base_class_type::exclude_small_factors_1_0()) { return; }
      if(base_class_type::exclude_small_factors_2_0()) { return; }
      if(base_class_type::exclude_small_factors_3_0()) { return; }
      if(base_class_type::exclude_small_factors_4_0()) { return; }
      if(base_class_type::exclude_small_factors_5_0()) { return; }
      if(base_class_type::exclude_small_factors_5_1()) { return; }
      if(base_class_type::exclude_small_factors_5_2()) { return; }
      if(base_class_type::exclude_small_factors_5_3()) { return; }
      if(base_class_type::exclude_small_factors_5_4()) { return; }
      if(base_class_type::exclude_small_factors_5_5()) { return; }

      // Perform a single Fermat test.
      base_class_type::my_n_m1 = base_class_type::my_n_trial;
      --base_class_type::my_n_m1;

      const typename base_class_type::wide_integer_type fn =
        powm(typename base_class_type::wide_integer_type(typename base_class_type::limb_type(228U)),
             base_class_type::my_n_m1,
             base_class_type::my_n_trial);

      const typename base_class_type::limb_type fn0 = static_cast<typename base_class_type::limb_type>(fn);

      if((fn0 != 1U) && (fn != 1U))
      {
        base_class_type::my_n_trial_is_probably_prime = false;

        return;
      }

      // Prepare the random trials.
      base_class_type::prepare_random_trials();

      std::uint_fast32_t i = 0U;

      // Execute the random trials.
      while(   (i < base_class_type::my_number_of_trials)
            && (base_class_type::my_n_trial_is_probably_prime == true))
      {
        base_class_type::execute_one_trial();

        ++i;
      }
    }
  };

  } // namespace wide_integer
  } // namespace math

  WIDE_INTEGER_NAMESPACE_END

#endif // MILLER_RABIN_SINGLE_2020_05_30_H_
