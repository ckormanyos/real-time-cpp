///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTILITY_IMPL_2010_02_23_H_
  #define _UTILITY_IMPL_2010_02_23_H_

  #include "pair_impl.h"
  #include "tuple_impl.h"

  // Implement most of <utility> for compilers that do not yet support it.

  namespace std
  {
    template<int I, typename T1, typename T2>
    inline typename xpair::xpair_get_helper<I, std::pair<T1, T2> >::nonconstant_reference_type
    get(std::pair<T1, T2>& my_pair)
    {
      return (xpair::xpair_get_helper<I, std::pair<T1, T2> >::my_value(my_pair));
    }

    template<int I, typename T1, typename T2>
    inline typename xpair::xpair_get_helper<I, std::pair<T1, T2> >::constant_reference_type
    get(const std::pair<T1, T2>& my_pair)
    {
      return (xpair::xpair_get_helper<I, std::pair<T1, T2> >::my_value(my_pair));
    }

    template<typename T1, typename T2>
    class tuple_element<0, std::pair<T1, T2> >
    {
    public:
      typedef T1 type;
    };

    template<typename T1, typename T2>
    class tuple_element<1, std::pair<T1, T2> >
    {
    public:
      typedef T2 type;
    };

    template<typename T1, typename T2>
    class tuple_size<std::pair<T1, T2> >
    {
    public:
      static const unsigned int value = 2;
    };

    template<typename T1, typename T2>
    inline void swap(std::pair<T1, T2>& left, std::pair<T1, T2>& right)
    {
      const std::pair<T1, T2> tmp(left);
      left  = right;
      right = tmp;
    }

    template<typename T1, typename T2>
    inline bool operator==(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return ((left.first == right.first) && (left.second == right.second));
    }

    template<typename T1, typename T2>
    inline bool operator!=(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return (!(left == right));
    }

    template<typename T1, typename T2>
    inline bool operator<(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return (((left.first < right.first) || (!(right.first < left.first))) && (left.second < right.second));
    }

    template<typename T1, typename T2>
    inline bool operator>(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return (right < left);
    }

    template<typename T1, typename T2>
    inline bool operator<=(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return (!(right < left));
    }

    template<typename T1, typename T2>
    inline bool operator>=(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return (!(left < right));
    }

    template<typename T1, typename T2>
    inline std::pair<T1, T2> make_pair(T1 value1, T2 value2)
    {
      return std::pair<T1, T2>(value1, value2);
    }
  }

#endif // _UTILITY_IMPL_2010_02_23_H_
