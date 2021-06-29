///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// The pi spigot program, as single-shot calculation.

#ifndef PI_SPIGOT_SINGLE_2019_05_12_H_
  #define PI_SPIGOT_SINGLE_2019_05_12_H_

  #include <math/constants/pi_spigot_base.h>

  namespace math { namespace constants {

  template<const std::uint32_t ResultDigit,
           const std::uint32_t LoopDigit>
  class pi_spigot_single
    : public pi_spigot_base<ResultDigit,
                            LoopDigit>
  {
  private:
    using base_class_type = pi_spigot_base<ResultDigit,
                                           LoopDigit>;

  public:
    pi_spigot_single() = default;

    virtual ~pi_spigot_single() = default;

    template<typename ItIn,
             typename ItOut>
    void calculate(ItIn  input_first,
                   ItOut output_first)
    {
      // Use pi_spigot::calculate() to calculate
      // result_digit decimal digits of pi.

      // The caller is responsible for providing both
      // input memory for the internal calculation details
      // as well as output memory for the result of pi.

      base_class_type::my_c = UINT32_C(0);

      base_class_type::my_output_count = UINT32_C(0);

      base_class_type::my_operation_count = UINTMAX_C(0);

      // Operation count Mathematica(R), example for loop_digit=9.
      // Sum[Floor[((d - j) (Floor[((10 9)/3)] + 1))/9], {j, 0, Floor[d/9] 9, 9}]
      for(base_class_type::my_j = 0U;
          base_class_type::my_j  < base_class_type::result_digit;
          base_class_type::my_j += base_class_type::loop_digit)
      {
        base_class_type::my_d = UINT64_C(0);

        auto i = std::int32_t(base_class_type::input_scale(base_class_type::result_digit - base_class_type::my_j) - INT32_C(1));

        for( ; i >= INT32_C(0); --i)
        {
          const std::uint32_t di =
            ((base_class_type::my_j == UINT32_C(0)) ? base_class_type::d_init : input_first[std::uint32_t(i)]);

          base_class_type::my_d +=
            std::uint64_t(std::uint64_t(di) * base_class_type::pow10_maker(base_class_type::loop_digit));

          const std::uint32_t b =
            std::uint32_t(std::uint32_t(i) * UINT32_C(2)) + UINT32_C(1);

          input_first[std::uint32_t(i)] = std::uint32_t(base_class_type::my_d % b);

          base_class_type::my_d /= b;

          if(i > INT32_C(1))
          {
            base_class_type::my_d *= std::uint32_t(i);
          }

          ++base_class_type::my_operation_count;
        }

        base_class_type::do_extract_digit_group(output_first);
      }
    }
  };

  } } // namespace math::constants

#endif // PI_SPIGOT_SINGLE_2019_05_12_H_
