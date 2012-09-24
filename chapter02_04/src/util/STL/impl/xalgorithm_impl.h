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

    template<typename InputIterator, typename OutputIterator>
    inline OutputIterator xcopy(InputIterator first, InputIterator last, OutputIterator result)
    {
      while(first != last)
      {
        *result = typename xiterator::xiterator_traits<OutputIterator>::value_type(*first);
        ++first;
        ++result;
      }

      return result;
    }

    template<typename ForwardIterator, typename T>
    inline void xfill(ForwardIterator first, ForwardIterator last, const T& value)
    {
      while(first != last)
      {
        *first = typename xiterator::xiterator_traits<ForwardIterator>::value_type(value);
        ++first;
      }
    }

    template<class InputIterator1, class InputIterator2>
    inline bool xequal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
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

    template<typename Iterator, typename Func>
    inline bool xall_of(Iterator first, Iterator last, Func func)
    {
      while((first != last) && func(*first))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename Iterator, typename Func>
    inline bool xany_of(Iterator first, Iterator last, Func func)
    {
      while((first != last) && (!func(*first)))
      {
        ++first;
      }

      return (first != last);
    }

    template<typename Iterator, typename Func>
    inline bool xnone_of(Iterator first, Iterator last, Func func)
    {
      while((first != last) && (!func(*first)))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename Iterator, typename Func>
    inline Func xfor_each(Iterator first, Iterator last, Func func)
    {
      while(first != last)
      {
        func(*first);
        ++first;
      }

      return func;
    }

    // Find the first element that satisfies the predicate.
    template<typename InputIterator, typename Predicate>
    inline InputIterator xfind_if(InputIterator first, InputIterator last, Predicate pred)
    {
      while((first != last) && (!pred(*first)))
      {
        ++first;
      }

      return first;
    }

    // Find the first element that does not satisfy the predicate.
    template<typename InputIterator, typename Predicate>
    inline InputIterator xfind_if_not(InputIterator first, InputIterator last, Predicate pred)
    {
      while((first != last) && pred(*first))
      {
        ++first;
      }

      return first;
    }

    template<typename InputIterator, typename T>
    typename xiterator::xiterator_traits<InputIterator>::difference_type xcount(InputIterator first, InputIterator last, const T& value)
    {
      typename xiterator::xiterator_traits<InputIterator>::difference_type cnt(0U);

      while(first != last)
      {
        if(value == *first) { ++cnt; }
        ++first;
      }

      return cnt;
    }

    template<class InputIterator, class Predicate>
    typename xiterator::xiterator_traits<InputIterator>::difference_type xcount_if(InputIterator first, InputIterator last, Predicate pred)
    {
      typename xiterator::xiterator_traits<InputIterator>::difference_type cnt(0U);

      while(first != last)
      {
        if(pred(*first)) { ++cnt; }
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

    template<typename InputIterator1, typename InputIterator2>
    inline InputIterator2 xswap_ranges(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
      for(; first1 != last1; ++first1, ++first2)
      {
        xalgorithm::xiter_swap(first1, first2);
      }

      return first2;
    }
  }

#endif // _XALGORITHM_IMPL_2010_02_23_H_
