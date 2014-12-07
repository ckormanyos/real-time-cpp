///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTILITY_IMPL_2010_02_23_H_
  #define _UTILITY_IMPL_2010_02_23_H_

  #include "cstddef_impl.h"
  #include "pair_impl.h"

  // Implement some of <utility> for compilers that do not yet support it.

  namespace std
  {
    template<int I, typename T1, typename T2>
    typename xpair_helper::xget<I, std::pair<T1, T2> >::nonconstant_reference_type
    get(std::pair<T1, T2>& my_pair)
    {
      return (xpair_helper::xget<I, std::pair<T1, T2> >::my_value(my_pair));
    }

    template<int I, typename T1, typename T2>
    typename xpair_helper::xget<I, std::pair<T1, T2> >::constant_reference_type
    get(const std::pair<T1, T2>& my_pair)
    {
      return (xpair_helper::xget<I, std::pair<T1, T2> >::my_value(my_pair));
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
      static const std::size_t value = 2;
    };

    template<typename T1, typename T2>
    void swap(std::pair<T1, T2>& left, std::pair<T1, T2>& right)
    {
      const std::pair<T1, T2> tmp(left);
      left  = right;
      right = tmp;
    }

    template<typename T1, typename T2>
    bool operator==(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return ((left.first == right.first) && (left.second == right.second));
    }

    template<typename T1, typename T2>
    bool operator!=(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return ((left.first != right.first) || (left.second != right.second));
    }

    template<typename T1, typename T2>
    bool operator<(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return ((left.first < right.first)
               ? true
               : ((right.first < left.first)
                   ? false
                   : ((left.second < right.second) ? true : false)));
    }

    template<typename T1, typename T2>
    bool operator>(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return (right < left);
    }

    template<typename T1, typename T2>
    bool operator<=(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return ((right < left) == false);
    }

    template<typename T1, typename T2>
    bool operator>=(const std::pair<T1, T2>& left, const std::pair<T1, T2>& right)
    {
      return ((left < right) == false);
    }

    template<typename T1, typename T2>
    std::pair<T1, T2> make_pair(T1 value1, T2 value2)
    {
      return std::pair<T1, T2>(value1, value2);
    }
  }

#endif // _UTILITY_IMPL_2010_02_23_H_
