///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _PAIR_IMPL_2010_02_23_H_
  #define _PAIR_IMPL_2010_02_23_H_

  #include "cstddef_impl.h"

  // Implement some of std::pair for compilers that do not yet support it.

  namespace std
  {
    template<typename T1,
             typename T2>
    class pair
    {
    public:
      typedef T1 first_type;
      typedef T2 second_type;

      first_type  first;
      second_type second;

      pair() : first(T1()), second(T2()) { }

      pair(const first_type& t1, const second_type& t2) : first (t1),
                                                          second(t2) { }

      pair(const pair& other) : first (other.first),
                                second(other.second) { }

      template<typename other_type1,
               typename other_type2>
      pair(const pair<other_type1, other_type2>& p) : first (T1(p.first)),
                                                      second(T2(p.second)) { }
    };
  }

  namespace xpair_helper
  {
    template<int I, typename T>
    class xget { };

    template<typename T1, typename T2>
    class xget<0, std::pair<T1, T2> >
    {
    public:
      typedef       T1& nonconstant_reference_type;
      typedef const T1&    constant_reference_type;

      static nonconstant_reference_type my_value(      std::pair<T1, T2>& my_pair) { return my_pair.first; }
      static    constant_reference_type my_value(const std::pair<T1, T2>& my_pair) { return my_pair.first; }
    };

    template<typename T1, typename T2>
    class xget<1, std::pair<T1, T2> >
    {
    public:
      typedef       T2& nonconstant_reference_type;
      typedef const T2&    constant_reference_type;

      static nonconstant_reference_type my_value(      std::pair<T1, T2>& my_pair) { return my_pair.second; }
      static    constant_reference_type my_value(const std::pair<T1, T2>& my_pair) { return my_pair.second; }
    };
  }

#endif // _PAIR_IMPL_2010_02_23_H_
