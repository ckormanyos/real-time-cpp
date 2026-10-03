///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_RING_ALLOCATOR_2010_02_23_H
  #define UTIL_RING_ALLOCATOR_2010_02_23_H

  #include <algorithm>
  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <limits>

  namespace util
  {
    template <const std::size_t ArenaSize,
              const std::size_t BufferAlignment = alignof(std::max_align_t)>
    struct ring_arena
    {
      static_assert(ArenaSize != 0U, "The ring arena must not be empty.");

      static_assert((BufferAlignment != 0U) && ((BufferAlignment & (BufferAlignment - 1U)) == 0U),
                    "The ring arena alignment must be a power of two.");

      alignas(BufferAlignment) std::array<std::uint8_t, ArenaSize> buffer { };

      std::size_t head { };

      // A rebound allocator must use the same storage as its original type.
      static ring_arena instance;
    };

    template <const std::size_t ArenaSize, const std::size_t BufferAlignment>
    ring_arena<ArenaSize, BufferAlignment> ring_arena<ArenaSize, BufferAlignment>::instance { };

    // Access must be externally serialized. This allocator is not interrupt- or
    // thread-safe, and it does not provide its own critical section.
    template <class T,
              const std::size_t ArenaSize,
              const std::size_t BufferAlignment = alignof(std::max_align_t)>
    class ring_allocator
    {
    public:
      using value_type = T;
      using size_type = std::size_t;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using const_pointer = const pointer;
      using reference = T&;
      using const_reference = const reference;

      static_assert(alignof(T) <= BufferAlignment,
                    "The ring allocator buffer is insufficiently aligned for T");

      ring_allocator() noexcept = default;

      template <class U>
      ring_allocator(const ring_allocator<U, ArenaSize, BufferAlignment>&) noexcept { }

      template<typename U> 
      struct rebind
      {
        using other = ring_allocator<U, ArenaSize, BufferAlignment>;
      };

      auto allocate(const std::size_t n) noexcept -> T*
      {
        if(n > (std::numeric_limits<std::size_t>::max)() / sizeof(T))
        {
          return nullptr;
        }

        ring_arena<ArenaSize, BufferAlignment>*
          arena_ptr
          {
            &ring_arena<ArenaSize, BufferAlignment>::instance
          };

        const std::size_t bytes = n * sizeof(T);
        std::size_t at = arena_ptr->head;
        const std::size_t remainder = at % alignof(T);

        if(remainder != 0U)
        {
          at += alignof(T) - remainder;
        }

        // This is an overwrite-style ring allocator: when the remaining
        // tail is too small, start again at the beginning regardless of
        // outstanding allocations.
        if(at > arena_ptr->buffer.size() || (bytes > (arena_ptr->buffer.size() - at)))
        {
          at = 0U;

          if(bytes > arena_ptr->buffer.size())
          {
            return nullptr;
          }
        }

        arena_ptr->head = at + bytes;

        return static_cast<T*>(static_cast<void*>(arena_ptr->buffer.data() + at));
      }

      auto deallocate(T*, const std::size_t) noexcept -> void { }

      void construct(pointer p, const value_type& x) noexcept
      {
        new(static_cast<void*>(p)) value_type(x);
      }

      void destroy(pointer p) noexcept { p->~value_type(); }

      static constexpr auto max_size() noexcept -> std::size_t
      {
        return ArenaSize / sizeof(T);
      }

    private:
      friend auto operator==(const ring_allocator&, const ring_allocator&) noexcept -> bool
      {
        return true;
      }

      friend auto operator!=(const ring_allocator&, const ring_allocator&) noexcept -> bool
      {
        return false;
      }
    };
  }

#endif // UTIL_RING_ALLOCATOR_2010_02_23_H
