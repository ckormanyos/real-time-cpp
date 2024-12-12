///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MILLER_RABIN_BASE_2020_05_30_H_
  #define MILLER_RABIN_BASE_2020_05_30_H_

  #include <math/wide_integer/miller_rabin/miller_rabin_digits.h>

  WIDE_INTEGER_NAMESPACE_BEGIN

  namespace math { namespace wide_integer {

  template<typename Generator1Type,
           typename Generator2Type,
           const size_t Digits2,
           typename LimbType>
  class miller_rabin_base
  {
  public:
    using wide_integer_type = uintwide_t<Digits2, LimbType>;
    using limb_type         = typename wide_integer_type::limb_type;
    using distribution_type = math::wide_integer::uniform_int_distribution<Digits2, limb_type>;

    using generator1_type    = Generator1Type;
    using generator2_type    = Generator2Type;

    virtual ~miller_rabin_base() = default;

    virtual auto search() -> bool = 0;

    auto get_n_is_probably_prime() const -> bool
    {
      return my_n_is_probably_prime;
    }

    auto get_n() const -> const wide_integer_type&
    {
      return my_n;
    }

    auto reseed1(const typename generator1_type::result_type seed1) -> void { my_generator1.seed(seed1); }
    auto reseed2(const typename generator2_type::result_type seed2) -> void { my_generator2.seed(seed2); }

    static auto get_n_total_mul_10() -> std::uint64_t { return my_n_total_mul_10; }

  protected:
    using distribution_param_type = typename distribution_type::param_type;

    static constexpr std::uint_fast32_t my_number_of_trials { UINT8_C(25) };

    wide_integer_type   my_n_trial;
    bool                my_n_trial_is_probably_prime;
    wide_integer_type   my_n;
    bool                my_n_is_probably_prime;
    wide_integer_type   my_n_m1;
    generator1_type     my_generator1;
    generator2_type     my_generator2;
    distribution_type   my_distribution { };
    std::uint_fast32_t  my_k            { };
    wide_integer_type   my_q            { };

    constexpr miller_rabin_base(const typename generator1_type::result_type seed1 = typename generator1_type::result_type(),
                                const typename generator2_type::result_type seed2 = typename generator2_type::result_type())
      : my_n_trial                  (),
        my_n_trial_is_probably_prime(false),
        my_n                        (),
        my_n_is_probably_prime      (false),
        my_n_m1                     (),
        my_generator1               (seed1),
        my_generator2               (seed2) { }

    auto set_n() -> bool
    {
      my_distribution.param(distribution_param_type());

      bool set_n_is_ok = false;

      my_n_trial = my_distribution(my_generator1);

      const limb_type hi_limb = my_n_trial.crepresentation().back();

      const std::uint8_t hi_nibble = std::uint8_t(std::uint8_t(hi_limb >> (std::numeric_limits<limb_type>::digits - 4)) & 0xFU);

      if(hi_nibble != 0U)
      {
        const limb_type lo_limb = my_n_trial.crepresentation().front();

        const std::uint8_t lo_bit = std::uint8_t(std::uint8_t(lo_limb) & 1U);

        // Remove all even candidates since they are non-prime.
        if(lo_bit != 0U)
        {
          const std::uint8_t lo_digit10 = std::uint8_t(my_n_trial % std::uint8_t(10U));

          // Continue by removing candidates having trailing digit 5.
          // The result is all candidates have trailing digit 1,3,7,9
          if(lo_digit10 != 5U)
          {
            // Now remove candidates having digital root 3, 6 or 9
            // because these are divisible by 3 and thus non-prime.

            // To compute the digital root of n dr(n), use
            // dr(n) = 1 + (n - 1) % 9.
            wide_integer_type n_minus_one(my_n_trial);

            --n_minus_one;

            const std::uint8_t dr =
              std::uint8_t(UINT8_C(1) + (std::uint8_t(n_minus_one % std::uint8_t(9U))));

            if((dr != UINT8_C(3)) && (dr != UINT8_C(6)) && (dr != UINT8_C(9)))
            {
              set_n_is_ok = true;

              my_n_trial_is_probably_prime = false;
              my_n                         = my_n_trial;
              my_n_is_probably_prime       = false;

              my_n_total_mul_10 += 10U;
            }
          }
        }
      }

      return set_n_is_ok;
    }

    auto exclude_small_factors_1_0() -> bool { return do_exclude_small_factors_from_ppn({   3U,   5U,   7U,  11U,  13U,  17U,  19U,  23U }, UINT32_C( 223092870)); }
    auto exclude_small_factors_2_0() -> bool { return do_exclude_small_factors_from_ppn({  29U,  31U,  37U,  41U,  43U,  47U },             UINT32_C(2756205443)); }
    auto exclude_small_factors_3_0() -> bool { return do_exclude_small_factors_from_ppn({  53U,  59U,  61U,  67U,  71U },                   UINT32_C( 907383479)); }
    auto exclude_small_factors_4_0() -> bool { return do_exclude_small_factors_from_ppn({  73U,  79U,  83U,  89U,  97U },                   UINT32_C(4132280413)); }
    auto exclude_small_factors_5_0() -> bool { return do_exclude_small_factors_from_ppn({ 101U, 103U, 107U, 109U },                         UINT32_C( 121330189)); }
    auto exclude_small_factors_5_1() -> bool { return do_exclude_small_factors_from_ppn({ 113U, 127U, 131U, 137U },                         std::uint32_t(113ULL * 127ULL * 131ULL * 137ULL)); }
    auto exclude_small_factors_5_2() -> bool { return do_exclude_small_factors_from_ppn({ 139U, 149U, 151U, 157U },                         std::uint32_t(139ULL * 149ULL * 151ULL * 157ULL)); }
    auto exclude_small_factors_5_3() -> bool { return do_exclude_small_factors_from_ppn({ 163U, 167U, 173U, 179U },                         std::uint32_t(163ULL * 167ULL * 173ULL * 179ULL)); }
    auto exclude_small_factors_5_4() -> bool { return do_exclude_small_factors_from_ppn({ 181U, 191U, 193U, 197U },                         std::uint32_t(181ULL * 191ULL * 193ULL * 197ULL)); }
    auto exclude_small_factors_5_5() -> bool { return do_exclude_small_factors_from_ppn({ 199U, 211U, 223U, 227U },                         std::uint32_t(199ULL * 211ULL * 223ULL * 227ULL)); }

    auto prepare_random_trials() -> void
    {
      my_k = lsb(my_n_m1);

      my_q = my_n_m1 >> my_k;

      my_distribution.param(distribution_param_type(wide_integer_type(2U),
                                                    wide_integer_type(my_n_trial - 2U)));

      my_n_trial_is_probably_prime = true;
    }

    virtual auto execute_one_trial() -> bool
    {
      wide_integer_type y = powm(my_distribution(my_generator2), my_q, my_n_trial);

      std::uint_fast32_t j = 0U;

      while(y != my_n_m1)
      {
        const limb_type y0(y);

        if((y0 == 1U) && (y == 1U))
        {
          if(j != 0U)
          {
            my_n_trial_is_probably_prime = false;
          }

          break;
        }

        ++j;

        if(j == my_k)
        {
          my_n_trial_is_probably_prime = false;

          break;
        }
        else
        {
          y = powm(y, 2U, my_n_trial);
        }
      }

      return true;
    }

  private:
    static std::uint64_t my_n_total_mul_10;

    auto do_exclude_small_factors_from_ppn(std::initializer_list<std::uint8_t> small_factors, const std::uint32_t& ppn) -> bool
    {
      bool exclude_does_terminate_prime_candidate = false;

      const std::uint32_t mn(my_n_trial % ppn);

      for(std::size_t i = 0U; i < small_factors.size(); ++i)
      {
        if((mn % *(small_factors.begin() + i)) == 0U)
        {
          my_n_trial_is_probably_prime = false;

          exclude_does_terminate_prime_candidate = true;

          break;
        }
      }

      return exclude_does_terminate_prime_candidate;
    }
  };

  template<typename Generator1Type,
           typename Generator2Type,
           const size_t Digits2,
           typename LimbType>
  std::uint64_t miller_rabin_base<Generator1Type, Generator2Type, Digits2, LimbType>::my_n_total_mul_10;

  } // namespace wide_integer
  } // namespace math

  WIDE_INTEGER_NAMESPACE_END

#endif // MILLER_RABIN_BASE_2020_05_30_H_
