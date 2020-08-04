///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// The pi spigot program, as state machine.

#ifndef PI_SPIGOT_STATE_2019_05_12_H_
  #define PI_SPIGOT_STATE_2019_05_12_H_

  #include <math/constants/pi_spigot_base.h>

  namespace math { namespace constants {

  template<const std::uint32_t ResultDigit,
           const std::uint32_t LoopDigit>
  class pi_spigot_state
    : public pi_spigot_base<ResultDigit,
                            LoopDigit>
  {
  private:
    using base_class_type = pi_spigot_base<ResultDigit,
                                           LoopDigit>;

    enum struct state_type
    {
      loop_j_init,
      loop_i_init,
      loop_i_run,
      extract_digit_group,
      finished
    };

  public:
    pi_spigot_state() : my_state(state_type::finished),
                        my_i    (0) { }

    virtual ~pi_spigot_state() { }

    void initialize()
    {
      my_state = state_type::loop_j_init;
    }

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

      switch(my_state)
      {
        case state_type::loop_j_init:
          base_class_type::my_c               = UINT32_C(0);
          base_class_type::my_output_count    = UINT32_C(0);
          base_class_type::my_operation_count = UINTMAX_C(0);
          base_class_type::my_j               = UINT32_C(0);

          my_state = state_type::loop_i_init;

          break;

        case state_type::loop_i_init:
          base_class_type::my_d = UINT64_C(0);

          my_i = std::int32_t(base_class_type::input_scale(base_class_type::result_digit - base_class_type::my_j) - INT32_C(1));

          my_state = state_type::loop_i_run;

          break;

        case state_type::loop_i_run:

          {
            const std::uint32_t di =
              ((base_class_type::my_j == UINT32_C(0)) ? base_class_type::d_init : input_first[std::uint32_t(my_i)]);

            base_class_type::my_d +=
              std::uint64_t(std::uint64_t(di) * detail::pow10<base_class_type::loop_digit>::value);

            const std::uint32_t b =
              std::uint32_t(std::uint32_t(my_i) * UINT32_C(2)) + UINT32_C(1);

            input_first[std::uint32_t(my_i)] = std::uint32_t(base_class_type::my_d % b);

            base_class_type::my_d /= b;
          }

          ++base_class_type::my_operation_count;

          if(my_i == INT32_C(0))
          {
            my_state = state_type::extract_digit_group;
          }
          else
          {
            base_class_type::my_d *= std::uint32_t(my_i);

            --my_i;
          }

          break;

        case state_type::extract_digit_group:

          base_class_type::do_extract_digit_group(output_first);

          base_class_type::my_j += base_class_type::loop_digit;

          if(base_class_type::my_j < base_class_type::result_digit)
          {
            my_state = state_type::loop_i_init;
          }
          else
          {
            my_state = state_type::finished;
          }

          break;

        case state_type::finished:
        default:
          break;
      };
    }

    bool is_finished() const
    {
      return (my_state == state_type::finished);
    }

  private:
    state_type   my_state;
    std::int32_t my_i;
  };

  } } // namespace math::constants

#endif // PI_SPIGOT_STATE_2019_05_12_H_
