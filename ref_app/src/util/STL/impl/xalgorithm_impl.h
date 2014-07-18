///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _XALGORITHM_IMPL_2010_02_23_H_
  #define _XALGORITHM_IMPL_2010_02_23_H_

  #include "xiterator_impl.h"
  #include "cstddef_impl.h"

  // Implement helper functions for <algorithm>.

  namespace xalgorithm
  {
    template<typename compare_type>
    const compare_type& xmin(const compare_type& a, const compare_type& b)
    {
      return ((a < b) ? a : b);
    }

    template<typename compare_type, typename binary_predicate>
    const compare_type& xmin(const compare_type& a, const compare_type& b, binary_predicate comp)
    {
      return (*comp)(a, b);
    }

    template<typename compare_type>
    const compare_type& xmax(const compare_type& a, const compare_type& b)
    {
      return ((a > b) ? a : b);
    }

    template<typename compare_type, typename binary_predicate>
    const compare_type& xmax(const compare_type& a, const compare_type& b, binary_predicate comp)
    {
      return (*comp)(a, b);
    }

    template <typename input_iterator1, typename input_iterator2>
    bool xlexicographical_compare (input_iterator1 first1,
                                   input_iterator1 last1,
                                   input_iterator2 first2,
                                   input_iterator2 last2)
    {
      while(first1 != last1)
      {
        if((first2 == last2) || (*first2 < *first1))
        {
          return false;
        }
        else if(*first1 < *first2)
        {
          return true;
        }

        ++first1;
        ++first2;
      }

      return (first2 != last2);
    }

    template<typename input_iterator, typename output_iterator>
    output_iterator xcopy(input_iterator first, input_iterator last, output_iterator result)
    {
      for( ; first != last; ++result, ++first)
      {
        *result = *first;
      }

      return result;
    }

    template<typename forward_iterator, typename value_type>
    void xfill(forward_iterator first, forward_iterator last, const value_type& value)
    {
      const value_type tmp = value;

      for( ; first != last; ++first)
      {
        *first = tmp;
      }
    }

    template<typename output_iterator, typename difference_type, typename value_type>
    output_iterator xfill_n(output_iterator first, difference_type count, const value_type& value)
    {
      const output_iterator last = first + count;

      xfill(first, last, value);

      return last;
    }

    template<typename input_iterator,
             typename output_iterator,
             typename unary_operation>
    output_iterator xtransform(input_iterator first, input_iterator last, output_iterator result, unary_operation unary_op)
    {
      for( ; first != last; ++first, ++result)
      {
        *result = unary_op(*first);
      }

      return result;
    }

    template<typename input_iterator1,
             typename input_iterator2,
             typename output_iterator,
             typename binary_operation>
    output_iterator xtransform(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2, output_iterator result, binary_operation binary_op)
    {
      for( ; first1 != last1; ++first1, ++first2, ++result)
      {
        *result = binary_op(*first1, *first2);
      }

      return result;
    }

    template<class input_iterator1, class input_iterator2>
    bool xequal(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
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
    bool xall_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && function(*first))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename iterator_type, typename function_type>
    bool xany_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && (!function(*first)))
      {
        ++first;
      }

      return (first != last);
    }

    template<typename iterator_type, typename function_type>
    bool xnone_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && (!function(*first)))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename iterator_type, typename function_type>
    function_type xfor_each(iterator_type first, iterator_type last, function_type function)
    {
      for( ; first != last; ++first)
      {
        function(*first);
      }

      return function;
    }

    template<typename input_iterator, typename predicate_type>
    input_iterator xfind_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      while((first != last) && (!predicate(*first)))
      {
        ++first;
      }

      return first;
    }

    template<typename input_iterator, typename predicate_type>
    input_iterator xfind_if_not(input_iterator first, input_iterator last, predicate_type predicate)
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
      typename xiterator::xiterator_traits<input_iterator>::difference_type count_value(0);

      while(first != last)
      {
        if(value == *first)
        {
          ++count_value;
        }

        ++first;
      }

      return count_value;
    }

    template<class input_iterator, class predicate_type>
    typename xiterator::xiterator_traits<input_iterator>::difference_type xcount_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      typename xiterator::xiterator_traits<input_iterator>::difference_type count_value(0);

      while(first != last)
      {
        if(predicate(*first))
        {
          ++count_value;
        }

        ++first;
      }

      return count_value;
    }

    template<typename forward_iterator,
             typename difference_type,
             typename value_type>
    forward_iterator xsearch_n(forward_iterator first,
                               forward_iterator last,
                               difference_type count_value,
                               const value_type& search_value)
    {
      forward_iterator limit = first;

      difference_type i;

      for(i = difference_type(0); i < difference_type((last - first) - count_value); ++i)
      {
        ++limit;
      }

      while(first != limit)
      {
        forward_iterator it = first;

        i = difference_type(0);

        while(*it == search_value)
        {
          ++it;
          ++i;

          if(i == count_value)
          {
            return first;
          }
        }

        ++first;
      }

      return last;
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
      forward_iterator limit = first;

      difference_type i;

      for(i = difference_type(0); i < difference_type((last - first) - count_value); ++i)
      {
        ++limit;
      }

      while(first != limit)
      {
        forward_iterator it = first;

        i = difference_type(0);

        while(pred(*it, search_value))
        {
          ++it;
          ++i;

          if(i == count_value)
          {
            return first;
          }
        }

        ++first;
      }

      return last;
    }

    template<typename swap_type>
    void xswap(swap_type left, swap_type right)
    {
      if(&left != &right)
      {
        const swap_type tmp = left;

        left = right;
        right = tmp;
      }
    }

    template<typename swap_type, std::size_t N>
    void xswap(swap_type(&left)[N], swap_type(&right)[N])
    {
      for(std::size_t i = static_cast<std::size_t>(0U); i < N; ++i)
      {
        xswap(left[i], right[i]);
      }
    }

    template<typename input_iterator1, typename input_iterator2>
    void xiter_swap(input_iterator1 left, input_iterator2 right)
    {
      xalgorithm::xswap(*left, *right);
    }

    template<typename input_iterator1, typename input_iterator2>
    input_iterator2 xswap_ranges(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
      for( ; first1 != last1; ++first1, ++first2)
      {
        xalgorithm::xiter_swap(first1, first2);
      }

      return first2;
    }
  }

#endif // _XALGORITHM_IMPL_2010_02_23_H_
