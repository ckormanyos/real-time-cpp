///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _NUMERIC_IMPL_2010_02_23_H_
  #define _NUMERIC_IMPL_2010_02_23_H_

  #include "xnumeric_impl.h"

  // Implement some of <numeric> for compilers that do not yet support it.

  namespace std
  {
    template<typename input_iterator,
             typename T>
    T accumulate(input_iterator first, input_iterator last, T val)
    {
      return xnumeric::xaccumulate(first, last, val);
    }

    template<typename input_iterator,
             typename T,
             typename function_type>
    T accumulate(input_iterator first, input_iterator last, T val, function_type function)
    {
      return xnumeric::xaccumulate(first, last, val, function);
    }

    template<typename input_iterator1,
             typename input_iterator2,
             typename T>
    inline T inner_product(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2, T val)
    {
      return xnumeric::xinner_product(first1, last1, first2, val);
    }

    template<typename input_iterator,
             typename output_iterator>
    output_iterator partial_sum(input_iterator first, input_iterator last, output_iterator result)
    {
      return xnumeric::xpartial_sum(first, last, result);
    }

    template<typename input_iterator,
             typename output_iterator,
             typename function_type>
    output_iterator partial_sum(input_iterator first, input_iterator last, output_iterator result, function_type binary_function)
    {
      return xnumeric::xpartial_sum(first, last, result, binary_function);
    }
  }

#endif // _NUMERIC_IMPL_2010_02_23_H_
