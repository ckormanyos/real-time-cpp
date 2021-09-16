///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MILLER_RABIN_POWM_STATE_2020_06_05_H_
  #define MILLER_RABIN_POWM_STATE_2020_06_05_H_

  #define WIDE_INTEGER_DISABLE_IOSTREAM
  #define WIDE_INTEGER_DISABLE_FLOAT_INTEROP

  #include <math/wide_integer/uintwide_t.h>

  namespace math { namespace wide_integer {

  template<const size_t Digits2,
           typename LimbType>
  class miller_rabin_powm_state final
  {
  private:
    using local_normal_width_type = uintwide_t<Digits2, LimbType>;
    using local_double_width_type = typename local_normal_width_type::double_width_type;
    using local_limb_type         = typename local_normal_width_type::limb_type;

  public:
    miller_rabin_powm_state() : my_done(false),
                                my_y   (),
                                my_p   (),
                                my_m   () { }

    ~miller_rabin_powm_state() = default;

    void init(const local_normal_width_type& b,
              const local_normal_width_type& p,
              const local_normal_width_type& m)
    {
      my_done = false;
      my_y    = local_double_width_type(b);
      my_x    = local_double_width_type(1U);
      my_p    = p;
      my_m    = m;

      if((local_limb_type(my_p) == 0U) && (my_p == 0U))
      {
        my_x = ((my_m != 1U) ? typename local_double_width_type::limb_type(1U)
                             : typename local_double_width_type::limb_type(0U));

        my_done = true;
      }
      else if((local_limb_type(my_p) == 1U) && (my_p == 1U))
      {
        my_x = local_double_width_type(b) % local_double_width_type(m);

        my_done = true;
      }
      else if((local_limb_type(my_p) == 2U) && (my_p == 2U))
      {
        my_y *= my_y;
        my_y %= local_double_width_type(my_m);

        my_x = my_y;

        my_done = true;
      }
    }

    bool get_done() const
    {
      return my_done;
    }

    void get_result(local_normal_width_type& result)
    {
      result = local_normal_width_type(my_x);
    }

    void calculate()
    {
      // Calculate (b ^ p) % m.

      if(my_done == false)
      {
        const local_limb_type p0 = static_cast<local_limb_type>(my_p);

        if(!((p0 == 0U) && (my_p == 0U)))
        {
          if(local_limb_type(p0 & 1U) != 0U)
          {
            my_x *= my_y;
            my_x %= local_double_width_type(my_m);
          }

          my_y *= my_y;
          my_y %= local_double_width_type(my_m);

          my_p >>= 1;
        }
        else
        {
          my_done = true;
        }
      }
    }

  private:
    bool                    my_done;
    local_double_width_type my_y;
    local_double_width_type my_x;
    local_normal_width_type my_p;
    local_normal_width_type my_m;
  };

  } } // namespace wide_integer::generic_template

#endif // MILLER_RABIN_POWM_STATE_2020_06_05_H_
