///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _ALGORITHM_IMPL_2010_02_23_H_
  #define _ALGORITHM_IMPL_2010_02_23_H_

  #include "cstddef_impl.h"
  #include "xalgorithm_impl.h"
  #include "iterator_impl.h"

  // Implement some of <algorithm> for compilers that do not yet support it.
  // See ISO/IEC 14882:2011 Chapter 25.1.

  namespace std
  {
    template<typename compare_type>
    const compare_type& (max)(const compare_type& a, const compare_type& b)
    {
      return xalgorithm::xmax(a, b);
    }

    template<typename compare_type, typename binary_predicate>
    const compare_type& (max)(const compare_type& a, const compare_type& b, binary_predicate predicate)
    {
      return predicate(a, b);
    }

    template<typename compare_type>
    const compare_type& (min)(const compare_type& a, const compare_type& b)
    {
      return xalgorithm::xmin(a, b);
    }

    template<typename compare_type, typename binary_predicate>
    const compare_type& (min)(const compare_type& a, const compare_type& b, binary_predicate predicate)
    {
      return predicate(a, b);
    }

    template <typename input_iterator1, typename input_iterator2>
    bool lexicographical_compare(input_iterator1 first1,
                                 input_iterator1 last1,
                                 input_iterator2 first2,
                                 input_iterator2 last2)
    {
      return xalgorithm::xlexicographical_compare(first1, last1, first2, last2);
    }

    template<typename input_iterator, typename output_iterator>
    output_iterator copy(input_iterator first, input_iterator last, output_iterator result)
    {
      return xalgorithm::xcopy(first, last, result);
    }

    template<typename forward_iterator, typename value_type>
    void fill(forward_iterator first, forward_iterator last, const value_type& value)
    {
      xalgorithm::xfill(first, last, value);
    }

    template<typename output_iterator,
             typename difference_type,
             typename value_type>
    void fill_n(output_iterator first, difference_type count, const value_type& value)
    {
      xalgorithm::xfill_n(first, count, value);
    }

    template<typename input_iterator,
             typename output_iterator,
             typename binary_function_type>
    output_iterator transform(input_iterator first,
                              input_iterator last,
                              output_iterator destination,
                              binary_function_type function)
    {
      return xalgorithm::xtransform(first, last, destination, function);
    }

    template<class input_iterator1,
             class input_iterator2,
             class output_iterator,
             class binary_function_type>
    output_iterator transform(input_iterator1 first1,
                              input_iterator1 last1,
                              input_iterator2 first2,
                              output_iterator destination,
                              binary_function_type function)
    {
      return xalgorithm::xtransform(first1, last1, first2, destination, function);
    }

    template<typename input_iterator1, typename input_iterator2>
    bool equal(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
      return xalgorithm::xequal(first1, last1, first2);
    }

    template<typename iterator_type, typename function_type>
    bool all_of(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xall_of(first, last, function);
    }

    template<typename iterator_type, typename function_type>
    bool any_of(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xany_of(first, last, function);
    }

    template<typename iterator_type, typename function_type>
    bool none_of(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xnone_of(first, last, function);
    }

    template<typename iterator_type, typename function_type>
    function_type for_each(iterator_type first, iterator_type last, function_type function)
    {
      return xalgorithm::xfor_each(first, last, function);
    }

    template<typename input_iterator, typename predicate_type>
    input_iterator find_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      return xalgorithm::xfind_if(first, last, predicate);
    }

    template<typename input_iterator, typename predicate_type>
    input_iterator find_if_not(input_iterator first, input_iterator last, predicate_type predicate)
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

    template<typename forward_iterator,
             typename difference_type,
             typename value_type>
    forward_iterator xsearch_n(forward_iterator first,
                               forward_iterator last,
                               difference_type count_value,
                               const value_type& search_value)
    {
      return xalgorithm::xsearch_n(first, last, count_value, search_value);
    }

    template<typename forward_iterator,
             typename difference_type,
             typename value_type,
             typename predicate_type>
    forward_iterator xsearch_n(forward_iterator first,
                               forward_iterator last,
                               difference_type count_value,
                               const value_type& search_value,
                               predicate_type predicate)
    {
      return xalgorithm::xsearch_n(first, last, count_value, search_value, predicate);
    }

    template<typename forward_iterator1, typename forward_iterator2>
    void iter_swap(forward_iterator1 left, forward_iterator2 right)
    {
      xalgorithm::xiter_swap(left, right);
    }

    template<typename forward_iterator1, typename forward_iterator2>
    forward_iterator2 swap_ranges(forward_iterator1 first1, forward_iterator1 last1, forward_iterator2 first2)
    {
      return xalgorithm::xswap_ranges(first1, last1, first2);
    }

    template<typename T>
    void swap(T& left, T& right)
    {
      xalgorithm::xswap(left, right);
    }

    template<typename T, std::size_t N>
    void xswap(T(&left)[N], T(&right)[N])
    {
      xalgorithm::xswap(left, right);
    }
  }

#endif // _ALGORITHM_IMPL_2010_02_23_H_
