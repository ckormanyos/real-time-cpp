///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_RING_ALLOCATOR_2010_02_23_H
  #define UTIL_RING_ALLOCATOR_2010_02_23_H

  #include <util/utility/util_alignas.h>

  #include <cstddef>
  #include <cstdint>
  #include <memory>

  namespace util
  {
    class ring_allocator_base
    {
    public:
      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;

      virtual ~ring_allocator_base() = default;

    protected:
      ring_allocator_base() = default;

      ring_allocator_base(const ring_allocator_base&) = default;

      // The ring allocator's buffer type.
      struct buffer_type
      {
        static constexpr size_type size = 64U;

        std::uint8_t data[size];

        buffer_type() : data() { }
      };

      // The ring allocator's memory allocation.
      template<const std::uint_fast8_t buffer_alignment>
      static auto do_allocate(size_type chunk_size) -> void*
      {
        ALIGNAS(16) static buffer_type buffer;

        static std::uint8_t* get_ptr = buffer.data;

        // Get the newly allocated pointer.
        std::uint8_t* p = get_ptr;

        // Increment the get-pointer for the next allocation.
        // Be sure to handle the buffer alignment.

        const std::uint_fast8_t misaligned_amount(chunk_size % buffer_alignment);

        if(misaligned_amount != UINT8_C(0))
        {
          chunk_size += size_type(buffer_alignment - misaligned_amount);
        }

        get_ptr += chunk_size;

        // Does this attempted allocation overflow the capacity of the buffer?
        const bool is_overflow = (get_ptr >= (buffer.data + buffer_type::size));

        if(is_overflow)
        {
          // The buffer has overflowed.

          // Reset the allocated pointer to the bottom of the buffer
          // and increment the next get-pointer.
          p       = &buffer.data[0U];
          get_ptr = &buffer.data[chunk_size];
        }

        return static_cast<void*>(p);
      }
    };

    // Global comparison operators (required by the standard).
    inline auto operator==(const ring_allocator_base&,
                           const ring_allocator_base&) -> bool
    {
      return true;
    }

    inline auto operator!=(const ring_allocator_base&,
                           const ring_allocator_base&) -> bool
    {
      return false;
    }

    template<typename T,
             const std::uint_fast8_t buffer_alignment = UINT8_C(16)>
    class ring_allocator;

    template<const std::uint_fast8_t buffer_alignment>
    class ring_allocator<void, buffer_alignment> : public ring_allocator_base
    {
    public:
      using value_type    = void;
      using pointer       = value_type*;
      using const_pointer = const value_type*;

      template<typename U>
      struct rebind
      {
        using other = ring_allocator<U, buffer_alignment>;
      };
    };

    template<typename T,
             const std::uint_fast8_t buffer_alignment>
    class ring_allocator : public ring_allocator_base
    {
    public:
      static_assert(sizeof(T) <= buffer_type::size,
                    "The size of the allocation object can not exceed the buffer size.");

      using value_type      = T;
      using pointer         = value_type*;
      using const_pointer   = const value_type*;
      using reference       = value_type&;
      using const_reference = const value_type&;

      ring_allocator() = default;

      ring_allocator(const ring_allocator&) : ring_allocator_base(ring_allocator()) { }

      template <typename U>
      ring_allocator(const ring_allocator<U, buffer_alignment>&) { }

      template<typename U> 
      struct rebind
      {
        using other = ring_allocator<U, buffer_alignment>;
      };

      auto max_size() const -> size_type
      {
        return buffer_type::size / sizeof(value_type);
      }

      auto address(      reference x) const ->       pointer { return &x; }
      auto address(const_reference x) const -> const_pointer { return &x; }

      auto allocate(size_type count,
                    typename ring_allocator<void, buffer_alignment>::const_pointer = nullptr) -> pointer
      {
        const size_type chunk_size = count * sizeof(value_type);

        void* p = do_allocate<buffer_alignment>(chunk_size);

        return static_cast<pointer>(p);
      }

      auto construct(pointer p, const value_type& x) -> void
      {
        new(static_cast<void*>(p)) value_type(x);
      }

      auto destroy(pointer p) -> void { p->~value_type(); }

      auto deallocate(pointer, size_type) -> void { }
    };
  }

#endif // UTIL_RING_ALLOCATOR_2010_02_23_H
