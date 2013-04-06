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

    template<typename T, typename binary_predicate>
    inline const T& (max)(const T& a, const T& b, binary_predicate predicate)
    {
      return predicate(a, b);
    }

    template<typename T>
    inline const T& (min)(const T& a, const T& b)
    {
      return xalgorithm::xmin(a, b);
    }

    template<typename T, typename binary_predicate>
    inline const T& (min)(const T& a, const T& b, binary_predicate predicate)
    {
      return predicate(a, b);
    }

    template<typename input_iterator, typename output_iterator>
    inline output_iterator copy(input_iterator first, input_iterator last, output_iterator result)
    {
      return xalgorithm::xcopy(first, last, result);
    }

    template<typename forward_iterator, typename T>
    inline void fill(forward_iterator first, forward_iterator last, const T& value)
    {
      xalgorithm::xfill(first, last, value);
    }

    template<typename output_iterator, typename difference_type, typename T>
    inline void fill_n(output_iterator first, difference_type n, const T& value)
    {
      xalgorithm::xfill(first, first + n, value);
    }

    template<typename input_iterator1, typename input_iterator2>
    inline bool equal(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
      return xalgorithm::xequal(first1, last1, first2);
    }

    template<typename iterator_type, typename function_type>
    inline bool all_of(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xall_of(first, last, function);
    }

    template<typename iterator_type, typename function_type>
    inline bool any_of(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xany_of(first, last, function);
    }

    template<typename iterator_type, typename function_type>
    inline bool none_of(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xnone_of(first, last, function);
    }

    template<typename iterator_type, typename function_type>
    inline function_type for_each(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xfor_each(first, last, function);
    }

    template<typename input_iterator, typename predicate_type>
    inline input_iterator find_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      return xalgorithm::xfind_if(first, last, predicate);
    }

    template<typename input_iterator, typename predicate_type>
    inline input_iterator find_if_not(input_iterator first, input_iterator last, predicate_type predicate)
    {
      return xalgorithm::xfind_if_not(first, last, predicate);
    }

    template<typename input_iterator, typename T>
    typename iterator_traits<input_iterator>::difference_type count(input_iterator first, input_iterator last, const T& value)
    {
      return xalgorithm::xcount(first, last, value);
    }

    template<class input_iterator, class predicate_type>
    typename iterator_traits<input_iterator>::difference_type count_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      return xcount_if(first, last, predicate);
    }

    template<typename forward_iterator1,
              typename difference2,
              typename value_type>
    inline forward_iterator1 xsearch_n(forward_iterator1 first1,
                                       forward_iterator1 last1,
                                       difference2 count_value,
                                       const value_type& search_value)
    {
      return xalgorithm::xsearch_n(first1, last1, count_value, search_value);
    }

    template<typename forward_iterator1,
             typename difference2,
             typename value_type,
             typename predicate_type>
    inline forward_iterator1 xsearch_n(forward_iterator1 first1,
                                       forward_iterator1 last1,
                                       difference2 count_value,
                                       const value_type& search_value,
                                       predicate_type predicate)
    {
      return xalgorithm::xsearch_n(first1, last1, count_value, search_value, predicate);
    }

    template<typename forward_iterator1, typename forward_iterator2>
    inline void iter_swap(forward_iterator1 left, forward_iterator2 right)
    {
      xalgorithm::xiter_swap(left, right);
    }

    template<typename forward_iterator1, typename forward_iterator2>
    inline forward_iterator2 swap_ranges(forward_iterator1 first1, forward_iterator1 last1, forward_iterator2 first2)
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
