///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// The pi spigot program, as state machine.

#ifndef PI_SPIGOT_STATE_2019_05_12_H_
  #define PI_SPIGOT_STATE_2019_05_12_H_

  #include <cstdint>

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
      loop_i_run_01,
      extract_digit_group,
      finished
    };

  public:
    constexpr pi_spigot_state() noexcept : my_state(state_type::finished),
                                           my_i    (0U) { }

    pi_spigot_state(const pi_spigot_state& other) noexcept
      : my_state(other.my_state),
        my_i    (other.my_i) { }

    pi_spigot_state(pi_spigot_state&& other) noexcept
      : my_state(other.my_state),
        my_i    (other.my_i) { }

    virtual ~pi_spigot_state() { }

    pi_spigot_state& operator=(const pi_spigot_state& other) noexcept
    {
      if(this != &other)
      {
        my_state = other.my_state;
        my_i     = other.my_i;
      }

      return *this;
    }

    pi_spigot_state& operator=(pi_spigot_state&& other) noexcept
    {
      my_state = other.my_state;
      my_i     = other.my_i;

      return *this;
    }

    void initialize() noexcept
    {
      my_state = state_type::loop_j_init;
    }

    template<typename InputIteratorType,
             typename OutputIteratorType>
    void calculate(InputIteratorType input_first, OutputIteratorType output_first) noexcept;

    bool is_finished() const noexcept
    {
      return (my_state == state_type::finished);
    }

  private:
    state_type    my_state;
    std::uint32_t my_i;
  };

  template<const std::uint32_t ResultDigit,
           const std::uint32_t LoopDigit>
  template<typename InputIteratorType,
           typename OutputIteratorType>
  void pi_spigot_state<ResultDigit, LoopDigit>::calculate(InputIteratorType  input_first,
                                                          OutputIteratorType output_first) noexcept
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

        my_i = std::uint32_t(base_class_type::input_scale(base_class_type::result_digit - base_class_type::my_j) - 1U);

        my_state = state_type::loop_i_run_01;

        break;

      case state_type::loop_i_run_01:

        {
          using input_difference_type = typename std::iterator_traits<InputIteratorType>::difference_type;

          const std::uint32_t di =
            ((base_class_type::my_j == UINT32_C(0)) ? base_class_type::d_init
                                                    : *(input_first + input_difference_type(my_i)));

          base_class_type::my_d +=
            std::uint64_t(std::uint64_t(di) * base_class_type::pow10_maker(base_class_type::loop_digit));

          const std::uint32_t b =
            std::uint32_t(my_i << 1U) + 1U;

          const std::uint32_t d_mod_b = std::uint32_t(base_class_type::my_d % b);

          base_class_type::my_d /= b;

          *(input_first + input_difference_type(my_i)) = d_mod_b;
        }

        ++base_class_type::my_operation_count;

        if(my_i == 0U)
        {
          my_state = state_type::extract_digit_group;
        }
        else
        {
          base_class_type::my_d *= my_i;

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
    }
  }

  } } // namespace math::constants

#endif // PI_SPIGOT_STATE_2019_05_12_H_
