///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_CONSTEXPR_ALGORITHM_UNSAFE_2023_11_23_H // NOLINT(llvm-header-guard)
  #define UTIL_CONSTEXPR_ALGORITHM_UNSAFE_2023_11_23_H

  #include <cstddef>
  #include <cstdint>
  #include <iterator>
  #include <utility>

  namespace util {

  // Use a local, constexpr, unsafe implementation of the abs-function.
  template<typename ArithmeticType>
  constexpr auto abs_unsafe(ArithmeticType val) -> ArithmeticType
  {
    return ((val > static_cast<int>(INT8_C(0))) ? val : -val);
  }

  // Use a local, constexpr, unsafe implementation of the fill-function.
  template<typename DestinationIterator,
           typename ValueType>
  constexpr auto fill_unsafe(DestinationIterator first, DestinationIterator last, ValueType val) -> void
  {
    while(first != last)
    {
      using local_destination_value_type = typename std::iterator_traits<DestinationIterator>::value_type;

      *first++ = static_cast<local_destination_value_type>(val);
    }
  }

  // Use a local, constexpr, unsafe implementation of the copy-function.
  template<typename InputIterator,
           typename DestinationIterator>
  constexpr auto copy_unsafe(InputIterator first, InputIterator last, DestinationIterator dest) -> DestinationIterator
  {
    while(first != last)
    {
      using local_destination_value_type = typename std::iterator_traits<DestinationIterator>::value_type;

      #if (defined(__GNUC__) && (__GNUC__ > 9))
      #pragma GCC diagnostic ignored "-Wstringop-overflow"
      #endif
      *dest++ = static_cast<local_destination_value_type>(*first++);
      #if (defined(__GNUC__) && (__GNUC__ > 9))
      #pragma GCC diagnostic pop
      #endif
    }

    return dest;
  }

  // Use a local, constexpr, unsafe implementation of the copy-backward-function.
  template<typename InputIterator,
           typename DestinationIterator>
  constexpr auto copy_backward_unsafe(InputIterator first, InputIterator last, DestinationIterator dest) -> DestinationIterator
  {
    using local_destination_value_type = typename std::iterator_traits<DestinationIterator>::value_type;

    while(first != last)
    {
      *(--dest) = static_cast<local_destination_value_type>(*(--last));
    }

    return dest;
  }

  // Use a local, constexpr, unsafe implementation of the max-function.
  template<typename ArithmeticType>
  constexpr auto max_unsafe(const ArithmeticType& left, const ArithmeticType& right) -> ArithmeticType
  {
    return ((left < right) ? right : left);
  }

  // Use a local, constexpr, unsafe implementation of the max-function.
  template<typename ArithmeticType>
  constexpr auto min_unsafe(const ArithmeticType& left, const ArithmeticType& right) -> ArithmeticType
  {
    return ((right < left) ? right : left);
  }

  template<typename ForwardIt, typename T>
  constexpr auto lower_bound_unsafe(ForwardIt first, ForwardIt last, const T& value) -> ForwardIt
  {
    using local_iterator_type = ForwardIt;

    using local_difference_type = typename std::iterator_traits<ForwardIt>::difference_type;

    local_difference_type step { };

    auto count = static_cast<local_difference_type>(last - first); // NOLINT(altera-id-dependent-backward-branch)

    local_iterator_type itr { };

    while(count > static_cast<local_difference_type>(INT8_C(0))) // NOLINT(altera-id-dependent-backward-branch)
    {
      itr = first;

      step = static_cast<local_difference_type>(count / static_cast<local_difference_type>(INT8_C(2)));

      itr += step;
 
      if (*itr < value)
      {
        first = ++itr;

        count -= static_cast<local_difference_type>(step + static_cast<local_difference_type>(INT8_C(1)));
      }
      else
      {
        count = step;
      }
    }

    return first;
  }

  template<typename T>
  constexpr auto swap_unsafe(T& left, T& right) -> void
  {
    auto tmp = static_cast<T&&>(left);

    left  = static_cast<T&&>(right);
    right = static_cast<T&&>(tmp);
  }

  template<typename T>
  constexpr auto swap_unsafe(T&& left, T&& right) -> void
  {
    auto tmp = static_cast<T&&>(left);

    left  = static_cast<T&&>(right);
    right = static_cast<T&&>(tmp);
  }

  template<typename InputIt, typename UnaryPredicate>
  constexpr auto find_if_unsafe(InputIt first, InputIt last, UnaryPredicate p) -> InputIt
  {
    for( ; first != last; ++first)
    {
      if (p(*first))
      {
        return first;
      }
    }

    return last;
  }

  template<typename InputIt, typename UnaryPredicate>
  constexpr auto find_if_not_unsafe(InputIt first, InputIt last, UnaryPredicate q) -> InputIt
  {
    for( ; first != last; ++first)
    {
      if (!q(*first))
      {
        return first;
      }
    }

    return last;
  }

  template<typename InputIt, typename UnaryPredicate>
  constexpr auto all_of_unsafe(InputIt first, InputIt last, UnaryPredicate p) -> bool
  {
    return (find_if_not_unsafe(first, last, p) == last);
  }

  template<typename IteratorType>
  constexpr auto iter_swap_unsafe(IteratorType a, IteratorType b) -> void
  {
    // Non-standard behavior:
    // The (dereferenced) left/right value-types are the same.

    using local_value_type = typename std::iterator_traits<IteratorType>::value_type;

    swap_unsafe(static_cast<local_value_type&&>(*a), static_cast<local_value_type&&>(*b));
  }

  template<typename BiDirectionalIterator>
  constexpr auto reverse_unsafe(BiDirectionalIterator first, BiDirectionalIterator last) -> void
  {
    // Ensure that the type of the iterator provided is actually bidirectional.

    for( ; ((first != last) && (first != --last)); ++first)
    {
      iter_swap_unsafe(first, last);
    }
  }

  } // namespace util

#endif // UTIL_CONSTEXPR_ALGORITHM_UNSAFE_2023_11_23_H
