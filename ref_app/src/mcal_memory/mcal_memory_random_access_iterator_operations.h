///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_RANDOM_ACCESS_ITERATOR_OPERATIONS_2026_01_01_H
  #define MCAL_MEMORY_RANDOM_ACCESS_ITERATOR_OPERATIONS_2026_01_01_H

  namespace mcal { namespace memory {

  template<typename PointerType>
  struct random_access_iterator_operations
  {
    using pointer         = PointerType;
    using difference_type = typename pointer::difference_type;

    static auto increment(pointer& current, difference_type n) noexcept -> pointer&
    {
      current += n;
      return current;
    }

    static auto add(const pointer& current, difference_type n) noexcept -> pointer
    {
      return current + n;
    }

    static auto subtract(const pointer& current, difference_type n) noexcept -> pointer
    {
      return current - n;
    }

    static auto less(const pointer& left, const pointer& right) noexcept -> bool { return left < right; }
    static auto less_equal(const pointer& left, const pointer& right) noexcept -> bool { return left <= right; }
    static auto equal(const pointer& left, const pointer& right) noexcept -> bool { return left == right; }
    static auto not_equal(const pointer& left, const pointer& right) noexcept -> bool { return left != right; }
    static auto greater_equal(const pointer& left, const pointer& right) noexcept -> bool { return left >= right; }
    static auto greater(const pointer& left, const pointer& right) noexcept -> bool { return left > right; }
    static auto distance(const pointer& left, const pointer& right) noexcept -> difference_type { return left - right; }
  };

  } } // namespace mcal::memory

#endif // MCAL_MEMORY_RANDOM_ACCESS_ITERATOR_OPERATIONS_2026_01_01_H
