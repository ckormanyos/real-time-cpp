#ifndef _NUMERIC_IMPL_2010_02_23_H_
  #define _NUMERIC_IMPL_2010_02_23_H_

  #include "xnumeric_impl.h"

  // Implement some of <numeric> for compilers that do not yet support it.

  namespace std
  {
    template<typename InputIterator, typename T>
    T accumulate(InputIterator first, InputIterator last, T val)
    {
      return xnumeric::xaccumulate(first, last, val);
    }

    template<typename InputIterator, typename T, typename Function>
    T accumulate(InputIterator first, InputIterator last, T val, Function func)
    {
      return xnumeric::xaccumulate(first, last, val, func);
    }
  }

#endif // _NUMERIC_IMPL_2010_02_23_H_
