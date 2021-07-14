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

    static constexpr std::uint32_t result_digit = ResultDigit;
    static constexpr std::uint32_t loop_digit   = LoopDigit;

    static_assert(result_digit <= UINT32_C(1001001),
                  "Error: result_digit exceeds its limit of 1,001,001");

    static_assert((loop_digit >= UINT32_C(4)) && (loop_digit <= UINT32_C(9)),
                  "Error: loop_digit is outside its range of 4...9");

    static constexpr std::uint32_t input_scale(std::uint32_t x)
    {
      return std::uint32_t(x * std::uint32_t((std::uint32_t(UINT32_C(10) * loop_digit) / UINT32_C(3)) + UINT32_C(1))) / loop_digit;
    }

    static constexpr std::uint32_t pow10(std::uint32_t n)
    {
      return ((n == UINT32_C(0)) ? UINT32_C(1) : pow10(n - UINT32_C(1)) * UINT32_C(10));
    }

    static constexpr std::uint32_t d_init = pow10(loop_digit) / UINT32_C(5);

  public:
    using output_value_type = std::uint8_t;

    pi_spigot_base(const pi_spigot_base& other)
      : my_c              (other.my_c),
        my_d              (other.my_d),
        my_j              (other.my_j),
        my_operation_count(other.my_operation_count),
        my_output_count   (other.my_output_count) { }

    pi_spigot_base(pi_spigot_base&& other)
      : my_c              (other.my_c),
        my_d              (other.my_d),
        my_j              (other.my_j),
        my_operation_count(other.my_operation_count),
        my_output_count   (other.my_output_count) { }

    virtual ~pi_spigot_base() { }

    pi_spigot_base& operator=(const pi_spigot_base& other)
    {
      if(this != &other)
      {
        my_c               = other.my_c;
        my_d               = other.my_d;
        my_j               = other.my_j;
        my_operation_count = other.my_operation_count;
        my_output_count    = other.my_output_count;
      }

      return *this;
    }

    pi_spigot_base& operator=(pi_spigot_base&& other)
    {
      my_c               = other.my_c;
      my_d               = other.my_d;
      my_j               = other.my_j;
      my_operation_count = other.my_operation_count;
      my_output_count    = other.my_output_count;

      return *this;
    }

    static constexpr std::uint32_t get_output_static_size() noexcept
    {
      return result_digit;
    }

    static constexpr std::uint32_t get_input_static_size() noexcept
    {
      return input_scale(get_output_static_size());
    }

    std::uintmax_t get_operation_count() const noexcept
    {
      return my_operation_count;
    }

    std::uint32_t get_output_digit_count() const noexcept
    {
      const std::uint32_t value = (std::min)(my_j, get_output_static_size());

      return value;
    }

  protected:
    std::uint32_t  my_c;
    std::uint64_t  my_d;
    std::uint32_t  my_j;
    std::uintmax_t my_operation_count;
    std::uint32_t  my_output_count;

    pi_spigot_base() noexcept
      : my_c              (0U),
        my_d              (0U),
        my_j              (0U),
        my_operation_count(0U),
        my_output_count   (0U) { }

    template<typename OutputIteratorType>
    void do_extract_digit_group(OutputIteratorType output_first)
    {
      using output_difference_type = typename std::iterator_traits<OutputIteratorType>::difference_type;

      // Parse the next digits of pi, where the group has loop_digit digits.
      // If loop_digit is 4, for instance, then successive groups
      // of digits have a form such as: 3141, 5926, ..., etc.
      const std::uint32_t d_div10(static_cast<std::uint32_t>(my_d / pow10(loop_digit)));
      const std::uint32_t d_mod10(static_cast<std::uint32_t>(my_d % pow10(loop_digit)));

      const std::uint32_t next_digits = my_c + d_div10;

      my_c = d_mod10;

      const std::uint32_t n =
        (std::min)(loop_digit, std::uint32_t(result_digit - my_j));

      std::uint32_t scale10 = pow10(loop_digit - UINT32_C(1));

      for(std::uint32_t i = 0U; i < n; ++i)
      {
        const std::uint32_t d10(next_digits / scale10);

        *(output_first + output_difference_type(my_j + i)) = output_value_type(d10 % UINT32_C(10));

        scale10 /= UINT32_C(10);
      }

      my_output_count += n;
    }
  };

  } } // namespace math::constants

#endif // PI_SPIGOT_BASE_2019_11_24_H_
