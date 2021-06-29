///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MILLER_RABIN_STATE_2020_05_31_H_
  #define MILLER_RABIN_STATE_2020_05_31_H_

  #include <math/wide_integer/miller_rabin/miller_rabin_base.h>
  #include <math/wide_integer/miller_rabin/miller_rabin_powm_state.h>

  namespace math { namespace wide_integer {

  template<typename Generator1Type,
           typename Generator2Type,
           const size_t Digits2,
           typename LimbType>
  class miller_rabin_state : public miller_rabin_base<Generator1Type,
                                                      Generator2Type,
                                                      Digits2,
                                                      LimbType>
  {
  private:
    using base_class_type = miller_rabin_base<Generator1Type,
                                              Generator2Type,
                                              Digits2,
                                              LimbType>;

    using miller_rabin_powm_type = miller_rabin_powm_state<Digits2, LimbType>;

    enum struct search_state_type
    {
      search_state_set_n,
      search_state_calculate_n,
      search_state_done
    };

    enum struct calculate_state_type
    {
      calculate_state_exclude_prime_factors_1_0,
      calculate_state_exclude_prime_factors_2_0,
      calculate_state_exclude_prime_factors_3_0,
      calculate_state_exclude_prime_factors_4_0,
      calculate_state_exclude_prime_factors_5_0,
      calculate_state_exclude_prime_factors_5_1,
      calculate_state_exclude_prime_factors_5_2,
      calculate_state_exclude_prime_factors_5_3,
      calculate_state_exclude_prime_factors_5_4,
      calculate_state_exclude_prime_factors_5_5,
      calculate_state_exclude_many_non_prime_candidates_via_fermat_test,
      calculate_state_prepare_random_trials,
      calculate_state_next_powm_for_random_trials,
      calculate_state_next_y_for_random_trials,
      calculate_state_execute_random_trials,
      calculate_state_done,
    };


  public:
    constexpr miller_rabin_state(const typename base_class_type::generator1_type::result_type seed1 = typename base_class_type::generator1_type::result_type(),
                                 const typename base_class_type::generator2_type::result_type seed2 = typename base_class_type::generator2_type::result_type())
      : base_class_type(seed1, seed2),
        my_search_state   (search_state_type::search_state_set_n),
        my_calculate_state(calculate_state_type::calculate_state_done),
        my_i              (0U),
        my_j              (0U),
        my_y              (),
        my_powm           () { }

    virtual ~miller_rabin_state() = default;

    virtual bool search()
    {
      bool search_is_done = false;

      switch(my_search_state)
      {
        case search_state_type::search_state_set_n:
          if(base_class_type::set_n())
          {
            my_calculate_state = calculate_state_type::calculate_state_exclude_prime_factors_1_0;

            my_search_state = search_state_type::search_state_calculate_n;
          }

          break;

        case search_state_type::search_state_calculate_n:
          calculate();

          if(my_calculate_state == calculate_state_type::calculate_state_done)
          {
            my_search_state = search_state_type::search_state_done;
          }

          break;

        case search_state_type::search_state_done:
        default:
          if(base_class_type::my_n_trial_is_probably_prime)
          {
            base_class_type::my_n_is_probably_prime = true;
          }

          my_search_state = search_state_type::search_state_set_n;

          search_is_done = true;

          break;
      }

      return search_is_done;
    }

  private:
    search_state_type                           my_search_state;
    calculate_state_type                        my_calculate_state;
    std::uint_fast32_t                          my_i;
    std::uint_fast32_t                          my_j;
    typename base_class_type::wide_integer_type my_y;
    miller_rabin_powm_type                      my_powm;

    void calculate()
    {
      switch(my_calculate_state)
      {
        case calculate_state_type::calculate_state_exclude_prime_factors_1_0:
          my_calculate_state = base_class_type::exclude_small_factors_1_0()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_2_0;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_2_0:
          my_calculate_state = base_class_type::exclude_small_factors_2_0()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_3_0;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_3_0:
          my_calculate_state = base_class_type::exclude_small_factors_3_0()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_4_0;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_4_0:
          my_calculate_state = base_class_type::exclude_small_factors_4_0()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_5_0;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_5_0:
          my_calculate_state = base_class_type::exclude_small_factors_5_0()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_5_1;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_5_1:
          my_calculate_state = base_class_type::exclude_small_factors_5_1()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_5_2;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_5_2:
          my_calculate_state = base_class_type::exclude_small_factors_5_2()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_5_3;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_5_3:
          my_calculate_state = base_class_type::exclude_small_factors_5_3()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_5_4;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_5_4:
          my_calculate_state = base_class_type::exclude_small_factors_5_4()
                                 ? calculate_state_type::calculate_state_done
                                 : calculate_state_type::calculate_state_exclude_prime_factors_5_5;
          break;

        case calculate_state_type::calculate_state_exclude_prime_factors_5_5:

          if(base_class_type::exclude_small_factors_5_5())
          {
            my_calculate_state = calculate_state_type::calculate_state_done;
          }
          else
          {
            base_class_type::my_n_m1 = base_class_type::my_n_trial;
            --base_class_type::my_n_m1;

            my_powm.init(typename base_class_type::wide_integer_type(typename base_class_type::limb_type(228U)),
                         base_class_type::my_n_m1,
                         base_class_type::my_n_trial);

            my_calculate_state = calculate_state_type::calculate_state_exclude_many_non_prime_candidates_via_fermat_test;
          }

          break;

        case calculate_state_type::calculate_state_exclude_many_non_prime_candidates_via_fermat_test:

          // Perform a single Fermat test.
          if(my_powm.get_done() == false)
          {
            my_powm.calculate();
          }
          else
          {
            typename base_class_type::wide_integer_type fn;

            my_powm.get_result(fn);

            const typename base_class_type::limb_type fn0 = static_cast<typename base_class_type::limb_type>(fn);

            if((fn0 != 1U) && (fn != 1U))
            {
              base_class_type::my_n_trial_is_probably_prime = false;

              my_calculate_state = calculate_state_type::calculate_state_done;
            }
            else
            {
              my_calculate_state = calculate_state_type::calculate_state_prepare_random_trials;
            }
          }

          break;

        case calculate_state_type::calculate_state_prepare_random_trials:

          // Prepare the random trials.
          base_class_type::prepare_random_trials();

          my_i = 0U;

          my_calculate_state = calculate_state_type::calculate_state_next_powm_for_random_trials;

          break;

        case calculate_state_type::calculate_state_next_powm_for_random_trials:

          my_powm.init(base_class_type::my_distribution(base_class_type::my_generator2),
                       base_class_type::my_q,
                       base_class_type::my_n_trial);

          my_j = 0U;

          my_calculate_state = calculate_state_type::calculate_state_next_y_for_random_trials;

          break;

        case calculate_state_type::calculate_state_next_y_for_random_trials:

          if(my_powm.get_done() == false)
          {
            my_powm.calculate();
          }
          else
          {
            my_powm.get_result(my_y);

            my_calculate_state = calculate_state_type::calculate_state_execute_random_trials;
          }

          break;

        case calculate_state_type::calculate_state_execute_random_trials:

          // Execute the random trials.
          if(my_i < base_class_type::my_number_of_trials)
          {
            const bool trials_are_finished = this->execute_one_trial();

            if(trials_are_finished)
            {
              if(base_class_type::my_n_trial_is_probably_prime == false)
              {
                my_calculate_state = calculate_state_type::calculate_state_done;
              }
              else
              {
                ++my_i;

                my_calculate_state = calculate_state_type::calculate_state_next_powm_for_random_trials;
              }
            }
          }
          else
          {
            my_calculate_state = calculate_state_type::calculate_state_done;
          }

          break;

        case calculate_state_type::calculate_state_done:
        default:
          break;
      }
    }

    virtual bool execute_one_trial()
    {
      // TBD: Reduce the number of return points in this subroutine.

      if(my_y == base_class_type::my_n_m1)
      {
        return true;
      }

      const typename base_class_type::limb_type y0(my_y);

      if((y0 == 1U) && (my_y == 1U))
      {
        if(my_j != 0U)
        {
          base_class_type::my_n_trial_is_probably_prime = false;
        }

        return true;
      }

      ++my_j;

      if(my_j == base_class_type::my_k)
      {
        base_class_type::my_n_trial_is_probably_prime = false;

        return true;
      }
      else
      {
        using local_double_width_type = typename base_class_type::wide_integer_type::double_width_type;

        local_double_width_type yd(my_y);

        yd *= yd;
        yd %= local_double_width_type(base_class_type::my_n_trial);

        my_y = typename base_class_type::wide_integer_type(yd);
      }

      return false;
    }
  };

  } } // namespace wide_integer::generic_template

#endif // MILLER_RABIN_STATE_2020_05_31_H_
