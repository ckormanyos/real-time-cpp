#ifndef _ALGORITHM_IMPL_2010_02_23_H_
  #define _ALGORITHM_IMPL_2010_02_23_H_

  #include "cstddef_impl.h"
  #include "xalgorithm_impl.h"
  #include "iterator_impl.h"

  // Implement some of <algorithm> for compilers that do not yet support it.

  namespace std
  {
    template<typename T>
    inline const T& (max)(const T& a, const T& b)
    {
      return xalgorithm::xmax(a, b);
    }

    template<typename T, typename BinaryPredicate>
    inline const T& (max)(const T& a, const T& b, BinaryPredicate pred)
    {
      return pred(a, b);
    }

    template<typename T>
    inline const T& (min)(const T& a, const T& b)
    {
      return xalgorithm::xmin(a, b);
    }

    template<typename T, typename BinaryPredicate>
    inline const T& (min)(const T& a, const T& b, BinaryPredicate pred)
    {
      return pred(a, b);
    }

    template<typename InputIterator, typename OutputIterator>
    inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
    {
      return xalgorithm::xcopy(first, last, result);
    }

    template<typename ForwardIterator, typename T>
    inline void fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
      xalgorithm::xfill(first, last, value);
    }

    template<typename OutputIterator, typename Size, typename T>
    inline void fill_n(OutputIterator first, Size n, const T& value)
    {
      xalgorithm::xfill(first, first + n, value);
    }

    template<typename InputIterator1, typename InputIterator2>
    inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
      return xalgorithm::xequal(first1, last1, first2);
    }

    template<typename Iterator, typename Func>
    inline bool all_of(Iterator first, Iterator last, Func func)
    {
      return xalgorithm::xall_of(first, last, func);
    }

    template<typename Iterator, typename Func>
    inline bool any_of(Iterator first, Iterator last, Func func)
    {
      return xalgorithm::xany_of(first, last, func);
    }

    template<typename Iterator, typename Func>
    inline bool none_of(Iterator first, Iterator last, Func func)
    {
      return xalgorithm::xnone_of(first, last, func);
    }

    template<typename Iterator, typename Func>
    inline Func for_each(Iterator first, Iterator last, Func func)
    {
      return xalgorithm::xfor_each(first, last, func);
    }

    template<typename InputIterator, typename Predicate>
    inline InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
    {
      return xalgorithm::xfind_if(first, last, pred);
    }

    template<typename InputIterator, typename Predicate>
    inline InputIterator find_if_not(InputIterator first, InputIterator last, Predicate pred)
    {
      return xalgorithm::xfind_if_not(first, last, pred);
    }

    template<typename InputIterator, typename T>
    typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T& value)
    {
      return xalgorithm::xcount(first, last, value);
    }

    template<class InputIterator, class Predicate>
    typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, Predicate pred)
    {
      return xcount_if(first, last, pred);
    }

    template<typename ForwardIterator1, typename ForwardIterator2>
    inline void iter_swap(ForwardIterator1 left, ForwardIterator2 right)
    {
      xalgorithm::xiter_swap(left, right);
    }

    template<typename ForwardIterator1, typename ForwardIterator2>
    inline ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
    {
      return xalgorithm::xswap_ranges(first1, last1, first2);
    }

    template<typename T>
    inline void swap(T& left, T& right)
    {
      xalgorithm::xswap(left, right);
    }

    template<typename T, std::size_t N>
    inline void xswap(T(&left)[N], T(&right)[N])
    {
      xalgorithm::xswap(left, right);
    }
  }

#endif // _ALGORITHM_IMPL_2010_02_23_H_
