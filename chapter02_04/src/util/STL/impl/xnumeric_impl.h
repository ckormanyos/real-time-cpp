#ifndef _XNUMERIC_IMPL_2010_02_23_H_
  #define _XNUMERIC_IMPL_2010_02_23_H_

  // Implement helper functions for <numeric>.

  namespace xnumeric
  {
    // Compute the sum of the elements in the range [first, last).
    template<typename InputIterator, typename value_type>
    inline value_type xaccumulate(InputIterator first, InputIterator last, value_type val)
    {
      for( ; first != last; ++first)
      {
        val = (value_type) (val + *first);
      }

      return val;
    }

    // Compute the sum of the elements in the range [first, last) using func.
    template<typename InputIterator, typename value_type, typename Function>
    inline value_type xaccumulate(InputIterator first, InputIterator last, value_type val, Function func)
    {
      for( ; first != last; ++first)
      {
        val = func(val, *first);
      }
      return val;
    }

    template<typename InputIterator1,
             typename InputIterator2,
             typename value_type>
    inline value_type xinner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, value_type val)
    {
      for( ; first1 != last1; ++first1, ++first2)
      {
        val = (value_type) (val + (*first1 * (*first2)));
      }
      return val;
    }
  }

#endif // _XNUMERIC_IMPL_2010_02_23_H_
