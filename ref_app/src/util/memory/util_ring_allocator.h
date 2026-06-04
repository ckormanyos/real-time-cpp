///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_RING_ALLOCATOR_2010_02_23_H
  #define UTIL_RING_ALLOCATOR_2010_02_23_H

  #include <cstddef>
  #include <cstdint>
  #include <memory>

  namespace util
  {
    // Forward declaration of ring_allocator_base.
    template<const std::uint_fast32_t buffer_size>
    class ring_allocator_base;

    // Global comparison operators (required by the standard).
    template<const std::uint_fast32_t buffer_size>
    auto operator==(const ring_allocator_base<buffer_size>&, const ring_allocator_base<buffer_size>&) noexcept -> bool;

    template<const std::uint_fast32_t buffer_size>
    auto operator!=(const ring_allocator_base<buffer_size>&, const ring_allocator_base<buffer_size>&) noexcept -> bool;

    template<const std::uint_fast32_t buffer_size>
    class ring_allocator_base
    {
    private:
      static constexpr std::uint_fast8_t buffer_alignment { UINT8_C(16) };

    public:
      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;

      virtual ~ring_allocator_base() = default;

    protected:
      static constexpr std::uint_fast8_t bufffer_alignment { UINT8_C(16) };

      ring_allocator_base() noexcept = default;

      ring_allocator_base(const ring_allocator_base&) noexcept = default;

      ring_allocator_base(ring_allocator_base&&) noexcept = default;

      auto operator=(const ring_allocator_base&) noexcept -> ring_allocator_base& = default;
      auto operator=(ring_allocator_base&&) noexcept -> ring_allocator_base& = default;

      // The ring allocator's buffer type.
      struct buffer_type
      {
        static constexpr size_type local_buf_size { static_cast<size_type>(buffer_size) };

        std::uint8_t data[local_buf_size];

        buffer_type() noexcept : data { } { }
      };

      // The ring allocator's memory allocation.
      static auto do_allocate(size_type chunk_size) -> void*
      {
        alignas(bufffer_alignment) static buffer_type buffer { };

        static std::uint8_t* get_ptr { buffer.data };

        // Get the newly allocated pointer.
        std::uint8_t* p { get_ptr };

        // Increment the get-pointer for the next allocation.
        // Be sure to handle the buffer alignment.

        const std::uint_fast8_t misaligned_amount(chunk_size % buffer_alignment);

        if(misaligned_amount != UINT8_C(0))
        {
          chunk_size += size_type(buffer_alignment - misaligned_amount);
        }

        get_ptr += chunk_size;

        // Does this attempted allocation overflow the capacity of the buffer?
        const bool is_overflow { (get_ptr >= (buffer.data + buffer_type::local_buf_size)) };

        if(is_overflow)
        {
          // The buffer has overflowed.

          #if (defined(__GNUC__) && !defined(__clang__))
          #if(__GNUC__ >= 12)
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Warray-bounds"
          #endif
          #endif

          // Reset the allocated pointer to the bottom of the buffer
          // and increment the next get-pointer.
          p       = &buffer.data[std::size_t { UINT8_C(0) }];
          get_ptr = &buffer.data[chunk_size];

          #if (defined(__GNUC__) && !defined(__clang__))
          #if(__GNUC__ >= 12)
          #pragma GCC diagnostic pop
          #endif
          #endif
        }

        return static_cast<void*>(p);
      }

      // Global comparison operators (required by the standard).
      friend auto operator==(const ring_allocator_base&, const ring_allocator_base&) noexcept -> bool { return true; }
      friend auto operator!=(const ring_allocator_base&, const ring_allocator_base&) noexcept -> bool { return false; }
    };

    template<typename T,
             const std::uint_fast32_t buffer_size>
    class ring_allocator;

    template<const std::uint_fast32_t buffer_size>
    class ring_allocator<void, buffer_size> : public ring_allocator_base<buffer_size>
    {
    public:
      using value_type    = void;
      using pointer       = value_type*;
      using const_pointer = const value_type*;

      template<typename U>
      struct rebind
      {
        using other = ring_allocator<U, buffer_size>;
      };
    };

    template<typename T,
             const std::uint_fast32_t buffer_size>
    class ring_allocator : public ring_allocator_base<buffer_size>
    {
    public:
      static_assert(sizeof(T) <= ring_allocator_base<buffer_size>::buffer_type::local_buf_size,
                    "The size of the allocation object can not exceed the buffer size.");

      using value_type      = T;
      using pointer         = value_type*;
      using const_pointer   = const value_type*;
      using reference       = value_type&;
      using const_reference = const value_type&;

      ring_allocator() noexcept = default;

      ring_allocator(const ring_allocator&) noexcept : ring_allocator_base<buffer_size>(ring_allocator()) { }
      ring_allocator(ring_allocator&&) noexcept : ring_allocator_base<buffer_size>(std::move(ring_allocator())) { }

      auto operator=(const ring_allocator&) noexcept -> ring_allocator& = default;
      auto operator=(ring_allocator&&) noexcept -> ring_allocator& = default;

      template <typename U>
      ring_allocator(const ring_allocator<U, buffer_size>&) noexcept { }

      ~ring_allocator() override = default;

      template<typename U> 
      struct rebind
      {
        using other = ring_allocator<U, buffer_size>;
      };

      auto max_size() const noexcept -> typename ring_allocator<void, buffer_size>::size_type
      {
        return ring_allocator_base<buffer_size>::buffer_type::size / sizeof(value_type);
      }

      auto address(      reference x) const ->       pointer { return &x; }
      auto address(const_reference x) const -> const_pointer { return &x; }

      auto allocate(typename ring_allocator<void, buffer_size>::size_type count,
                    typename ring_allocator<void, buffer_size>::const_pointer = nullptr) -> pointer
      {
        const typename ring_allocator<void, buffer_size>::size_type chunk_size = count * sizeof(value_type);

        void* p = ring_allocator<void, buffer_size>::do_allocate(chunk_size);

        return static_cast<pointer>(p);
      }

      auto construct(pointer p, const value_type& x) noexcept -> void
      {
        new(static_cast<void*>(p)) value_type(x);
      }

      auto destroy(pointer p) noexcept -> void { p->~value_type(); }

      auto deallocate(pointer, typename ring_allocator<void, buffer_size>::size_type) noexcept -> void { }
    };
  }

#endif // UTIL_RING_ALLOCATOR_2010_02_23_H
