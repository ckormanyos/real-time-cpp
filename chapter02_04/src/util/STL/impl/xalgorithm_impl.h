#ifndef _XALGORITHM_IMPL_2010_02_23_H_
  #define _XALGORITHM_IMPL_2010_02_23_H_

  #include "xiterator_impl.h"
  #include "cstddef_impl.h"

  // Implement helper functions for <algorithm>.

  namespace xalgorithm
  {
    template<typename T>
    inline const T& xmin(const T& a, const T& b)
    {
      return ((a < b) ? a : b);
    }

    template<typename T, typename BinaryPredicate>
    inline const T& xmin(const T& a, const T& b, BinaryPredicate comp)
    {
      return (*comp)(a, b);
    }

    template<typename T>
    inline const T& xmax(const T& a, const T& b)
    {
      return ((a > b) ? a : b);
    }

    template<typename T, typename BinaryPredicate>
    inline const T& xmax(const T& a, const T& b, BinaryPredicate comp)
    {
      return (*comp)(a, b);
    }

    template<typename input_iterator, typename output_iterator>
    inline output_iterator xcopy(input_iterator first, input_iterator last, output_iterator result)
    {
      while(first != last)
      {
        *result = typename xiterator::xiterator_traits<output_iterator>::value_type(*first);
        ++first;
        ++result;
      }

      return result;
    }

    template<typename forward_iterator, typename T>
    inline void xfill(forward_iterator first, forward_iterator last, const T& value)
    {
      while(first != last)
      {
        *first = typename xiterator::xiterator_traits<forward_iterator>::value_type(value);
        ++first;
      }
    }

    template<class input_iterator1, class input_iterator2>
    inline bool xequal(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
      while(first1 != last1)
      {
        if(!(*first1 == *first2))
        {
          return false;
        }

        ++first1;
        ++first2;
      }

      return true;
    }

    template<typename iterator_type, typename function_type>
    inline bool xall_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && function(*first))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename iterator_type, typename function_type>
    inline bool xany_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && (!function(*first)))
      {
        ++first;
      }

      return (first != last);
    }

    template<typename iterator_type, typename function_type>
    inline bool xnone_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && (!function(*first)))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename iterator_type, typename function_type>
    inline function_type xfor_each(iterator_type first, iterator_type last, function_type function)
    {
      while(first != last)
      {
        function(*first);
        ++first;
      }

      return function;
    }

    // Find the first element that satisfies the predicate.
    template<typename input_iterator, typename predicate_type>
    inline input_iterator xfind_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      while((first != last) && (!predicate(*first)))
      {
        ++first;
      }

      return first;
    }

    // Find the first element that does not satisfy the predicate.
    template<typename input_iterator, typename predicate_type>
    inline input_iterator xfind_if_not(input_iterator first, input_iterator last, predicate_type predicate)
    {
      while((first != last) && predicate(*first))
      {
        ++first;
      }

      return first;
    }

    template<typename input_iterator, typename T>
    typename xiterator::xiterator_traits<input_iterator>::difference_type xcount(input_iterator first, input_iterator last, const T& value)
    {
      typename xiterator::xiterator_traits<input_iterator>::difference_type cnt(0U);

      while(first != last)
      {
        if(value == *first) { ++cnt; }
        ++first;
      }

      return cnt;
    }

    template<class input_iterator, class predicate_type>
    typename xiterator::xiterator_traits<input_iterator>::difference_type xcount_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      typename xiterator::xiterator_traits<input_iterator>::difference_type cnt(0U);

      while(first != last)
      {
        if(predicate(*first)) { ++cnt; }
        ++first;
      }

      return cnt;
    }

    template<typename T>
    inline void xswap(T& left, T& right)
    {
      // Exchange the values stored at left and right if they are different.
      if(&left != &right)
      {
        T tmp = left;

        left = right;
        right = tmp;
      }
    }

    template<typename T, std::size_t N>
    inline void xswap(T(&left)[N], T(&right)[N])
    {
      for(std::size_t i = static_cast<std::size_t>(0U); i < N; ++i)
      {
        xswap(left[i], right[i]);
      }
    }

    template<typename Iterator1, typename Iterator2>
    inline void xiter_swap(Iterator1 left, Iterator2 right)
    {
      xalgorithm::xswap(*left, *right);
    }

    template<typename input_iterator1, typename input_iterator2>
    inline input_iterator2 xswap_ranges(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
      for(; first1 != last1; ++first1, ++first2)
      {
        xalgorithm::xiter_swap(first1, first2);
      }

      return first2;
    }
  }

#endif // _XALGORITHM_IMPL_2010_02_23_H_
