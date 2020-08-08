///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef PI_SPIGOT_BASE_2019_11_24_H_
  #define PI_SPIGOT_BASE_2019_11_24_H_

  #include <algorithm>
  #include <cstdint>

  namespace math { namespace constants {

  namespace detail
  {

  template<const std::uint32_t LoopDigit>
  struct pow10
  {
    static constexpr std::uint32_t value = pow10<LoopDigit - 1U>::value * UINT32_C(10);
  };

  template<>
  struct pow10<0U>
  {
    static constexpr std::uint32_t value = 1U;
  };

  } // namespace detail

  template<const std::uint32_t ResultDigit,
           const std::uint32_t LoopDigit>
  class pi_spigot_base
  {
  protected:
    // Support up to one million one thousand and one decimal digits.

    // Table of calculation characteristics
    //   digits(*)   operation count   time[s]   memory[byte]
    //  -----------------------------------------------------
    // 1,000,001(9)  191,360,030,868   2,100      13,777,788
    //   500,001(9)   47,840,521,610     520       6,888,900
    //   250,001(9)   11,960,387,349     130       3,444,456
    //   100,001(9)    1,913,780,868      21       1,377,788
    //    50,001(9)      478,496,610       5.3       688,900
    //    25,001(9)      119,649,849       1.4       344,456
    //    10,001(9)       19,155,868       0.23      137,788
    //     5,001(9)        4,794,110       0.055      68,900
    //     1,001(9)          193,368       0.002      13,788

    //    50,001(8)      527,446,878
    //    25,001(8)      131,887,503
    //    10,001(8)       21,114,378

    //    54,932(4)    1,320,263,154
    //    50,001(4)    1,093,875,003
    //    25,001(4)      273,500,003
    //    10,001(4)       43,775,003
    //     5,001(4)       10,950,003
    //     2,001(4)        1,755,003
    //     1,001(4)          440,003
    //       501(4)          110,628
    //       201(4)           18,003
    //       101(4)            4,628
    //        51(4)            1,222
    //        21(4)              228
    //        11(4)               72

    // (*) Here, the number in parentheses such as
    // (9), (8) or (4) means calculating groups
    // of 9, 8 or 4 digits per loop, corresponding
    // to the template parameter loop_digit.

    static const std::uint32_t result_digit = ResultDigit;
    static const std::uint32_t loop_digit   = LoopDigit;

    static_assert(result_digit <= UINT32_C(1001001),
                  "Error: result_digit exceeds its limit of 1,001,001");

    static_assert((loop_digit >= UINT32_C(4)) && (loop_digit <= UINT32_C(9)),
                  "Error: loop_digit is outside its range of 4...9");

    static constexpr std::uint32_t input_scale(std::uint32_t x)
    {
      return std::uint32_t(x * std::uint32_t((std::uint32_t(UINT32_C(10) * loop_digit) / UINT32_C(3)) + UINT32_C(1))) / loop_digit;
    }

    static constexpr std::uint32_t d_init = detail::pow10<loop_digit>::value / UINT32_C(5);

  public:
    using output_value_type = std::uint8_t;

    pi_spigot_base(const pi_spigot_base&) = delete;

    virtual ~pi_spigot_base() = default;

    pi_spigot_base& operator=(const pi_spigot_base&) = delete;

    static constexpr std::uint32_t get_output_static_size()
    {
      return result_digit;
    }

    static constexpr std::uint32_t get_input__static_size()
    {
      return input_scale(result_digit);
    }

    std::uintmax_t get_operation_count() const
    {
      return my_operation_count;
    }

    std::uint32_t get_output_digit_count() const
    {
      return (std::min)(my_j, get_output_static_size());
    }

  protected:
    std::uint32_t  my_c;
    std::uint64_t  my_d;
    std::uint32_t  my_j;
    std::uintmax_t my_operation_count;
    std::uint32_t  my_output_count;

    pi_spigot_base() : my_c              (0U),
                       my_d              (0U),
                       my_j              (0U),
                       my_operation_count(0U),
                       my_output_count   (0U) { }

    template<typename OutIn>
    void do_extract_digit_group(OutIn output_first)
    {
      // Parse the next digits of pi, where the group has loop_digit digits.
      // If loop_digit is 4, for instance, then successive groups
      // of digits have a form such as: 3141, 5926, ..., etc.

      const std::uint32_t next_digits =
        my_c + std::uint32_t(my_d / detail::pow10<loop_digit>::value);

      my_c = std::uint32_t(my_d % detail::pow10<loop_digit>::value);

      const std::uint32_t n =
        (std::min)(loop_digit,
                    std::uint32_t(result_digit - my_j));

      std::uint32_t scale10 = detail::pow10<loop_digit - UINT32_C(1)>::value;

      for(std::size_t i = std::size_t(0U); i < std::size_t(n); ++i)
      {
        output_first[my_j + i] =
          output_value_type(std::uint32_t(next_digits / scale10) % UINT32_C(10));

        scale10 /= UINT32_C(10);
      }

      my_output_count += n;
    }
  };

  template<const std::uint32_t ResultDigit, const std::uint32_t LoopDigit> const std::uint32_t pi_spigot_base<ResultDigit, LoopDigit>::result_digit;
  template<const std::uint32_t ResultDigit, const std::uint32_t LoopDigit> const std::uint32_t pi_spigot_base<ResultDigit, LoopDigit>::loop_digit;

  } } // namespace math::constants

#endif // PI_SPIGOT_BASE_2019_11_24_H_
