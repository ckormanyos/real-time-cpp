///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_STATIC_ALLOCATOR_2010_02_23_H
  #define UTIL_STATIC_ALLOCATOR_2010_02_23_H

  #include <util/utility/util_alignas.h>

  #include <cstddef>
  #include <cstdint>
  #include <memory>

  namespace util
  {
    class static_allocator_base
    {
    public:
      using size_type = std::size_t;

      virtual ~static_allocator_base() = default;

    protected:
      static_allocator_base() = default;

      static_allocator_base(const static_allocator_base&) = default;

      // The static allocator's buffer type.
      struct buffer_type
      {
        static constexpr size_type size { UINT16_C(640) };

        std::uint8_t data[size];

        buffer_type() : data() { }
      };

      // The static allocator's memory allocation.
      template<const std::uint_fast8_t buffer_alignment>
      static auto do_allocate(size_type chunk_size,
                              size_type& remaining,
                              bool& is_overflow) -> void*
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
        is_overflow = (get_ptr >= (buffer.data + buffer_type::size));

        if(is_overflow)
        {
          // The buffer has overflowed.

          // Reset the allocated pointer to the bottom of the buffer
          // and increment the next get-pointer, even though this is
          // the wrong behavior.
          p         = &buffer.data[0U];
          get_ptr   = &buffer.data[chunk_size];
          remaining = 0U;
        }
        else
        {
          // Calculate the remaining memory in the buffer based on
          // the value of the newly calculated get-pointer.
          remaining = size_type(&buffer.data[buffer_type::size] - get_ptr);
        }

        return static_cast<void*>(p);
      }
    };

    // Global comparison operators (required by the standard).
    inline auto operator==(const static_allocator_base&,
                           const static_allocator_base&) -> bool
    {
      return true;
    }

    inline auto operator!=(const static_allocator_base&,
                           const static_allocator_base&) -> bool
    {
      return false;
    }

    template<typename T,
             const std::uint_fast8_t buffer_alignment = UINT8_C(16)>
    class static_allocator;

    template<const std::uint_fast8_t buffer_alignment>
    class static_allocator<void, buffer_alignment> : public static_allocator_base
    {
    public:
      using value_type = void;
      using pointer = value_type*;
      using const_pointer = const value_type*;

      template<typename U>
      struct rebind
      {
        using other = static_allocator<U, buffer_alignment>;
      };
    };

    template<typename T,
             const std::uint_fast8_t buffer_alignment>
    class static_allocator : public static_allocator_base
    {
    public:
      static_assert(sizeof(T) <= buffer_type::size,
                    "The size of the allocation object can not exceed the buffer size.");

      using value_type       = T;
      using pointer          = value_type*;
      using const_pointer    = const value_type*;
      using reference        = value_type&;
      using const_reference  = const value_type&;

      static_allocator() = default;

      static_allocator(const static_allocator&) : static_allocator_base(static_allocator()) { }

      template <typename U>
      static_allocator(const static_allocator<U, buffer_alignment>&) { }

      template<typename U> 
      struct rebind
      {
        using other = static_allocator<U, buffer_alignment>;
      };

      auto max_size() const -> size_type
      {
        size_type remaining;
        bool      is_overflow;

        void* p = do_allocate<buffer_alignment>(size_type(0U),
                                                remaining,
                                                is_overflow);

        static_cast<void>(p);
        static_cast<void>(is_overflow);

        return remaining / sizeof(value_type);
      }

      auto address(      reference x) const ->       pointer { return &x; }
      auto address(const_reference x) const -> const_pointer { return &x; }

      auto allocate(size_type count,
                    typename static_allocator<void, buffer_alignment>::const_pointer = nullptr) -> pointer
      {
        const size_type chunk_size = count * sizeof(value_type);

        size_type remaining;
        bool      is_overflow;

        void* p = do_allocate<buffer_alignment>(chunk_size,
                                                remaining,
                                                is_overflow);

        static_cast<void>(remaining);
        static_cast<void>(is_overflow);

        return static_cast<pointer>(p);
      }

      auto construct(pointer p, const value_type& x) -> void
      {
        new(static_cast<void*>(p)) value_type(x);
      }

      auto destroy(pointer p) -> void { p->~value_type(); }

      void deallocate(pointer, size_type) { }
    };
  }

#endif // UTIL_STATIC_ALLOCATOR_2010_02_23_H
