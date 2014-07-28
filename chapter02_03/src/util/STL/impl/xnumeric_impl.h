///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _XNUMERIC_IMPL_2010_02_23_H_
  #define _XNUMERIC_IMPL_2010_02_23_H_

  // Implement helper functions for some of <numeric>.

  namespace xnumeric
  {
    // Compute the sum of the elements in the range [first, last).
    template<typename input_iterator, typename value_type>
    inline value_type xaccumulate(input_iterator first, input_iterator last, value_type val)
    {
      while(first != last)
      {
        val += *first;
        ++first;
      }

      return val;
    }

    // Compute the sum of the elements in the range [first, last) using function.
    template<typename input_iterator, typename value_type, typename function_type>
    inline value_type xaccumulate(input_iterator first, input_iterator last, value_type val, function_type function)
    {
      while(first != last)
      {
        val = function(val, *first);
        ++first;
      }

      return val;
    }

    template<typename input_iterator1,
             typename input_iterator2,
             typename value_type>
    inline value_type xinner_product(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2, value_type val)
    {
      while(first1 != last1)
      {
        val += (*first1 * (*first2));
        ++first1;
        ++first2;
      }

      return val;
    }
  }

#endif // _XNUMERIC_IMPL_2010_02_23_H_
