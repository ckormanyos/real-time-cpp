///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2017.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_RING_ALLOCATOR_2010_02_23_H_
  #define UTIL_RING_ALLOCATOR_2010_02_23_H_

  #include <cstddef>
  #include <cstdint>
  #include <memory>

  #include <util/utility/util_alignas.h>

  namespace util
  {
    class ring_allocator_base
    {
    public:
      typedef std::size_t    size_type;
      typedef std::ptrdiff_t difference_type;

      virtual ~ring_allocator_base();

    protected:
      ring_allocator_base() throw() { }

      ring_allocator_base(const ring_allocator_base&) throw() { }

      // The ring allocator's buffer type.
      struct buffer_type
      {
        static const size_type size = 2048U;

        std::uint8_t data[size];

        buffer_type() : data() { }
      };

      // The ring allocator's memory allocation.
      template<const std::uint_fast8_t buffer_alignment>
      static void* do_allocate(size_type chunk_size)
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

    inline ring_allocator_base::~ring_allocator_base() { }

    // Global comparison operators (required by the standard).
    inline bool operator==(const ring_allocator_base&,
                           const ring_allocator_base&) throw()
    {
      return true;
    }

    inline bool operator!=(const ring_allocator_base&,
                           const ring_allocator_base&) throw()
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
      typedef void              value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;

      template<typename U>
      struct rebind { typedef ring_allocator<U, buffer_alignment> other; };
    };

    template<typename T,
             const std::uint_fast8_t buffer_alignment>
    class ring_allocator : public ring_allocator_base
    {
    public:
      static_assert(sizeof(T) <= buffer_type::size,
                    "The size of the allocation object can not exceed the buffer size.");

      typedef T                 value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;
      typedef value_type&       reference;
      typedef const value_type& const_reference;

      ring_allocator() throw() { }

      ring_allocator(const ring_allocator&) throw() : ring_allocator_base(ring_allocator()) { }

      template <typename U>
      ring_allocator(const ring_allocator<U, buffer_alignment>&) throw() { }

      template<typename U> 
      struct rebind { typedef ring_allocator<U, buffer_alignment> other; };

      size_type max_size() const throw()
      {
        return buffer_type::size / sizeof(value_type);
      }

            pointer address(      reference x) const { return &x; }
      const_pointer address(const_reference x) const { return &x; }

      pointer allocate(size_type count,
                       typename ring_allocator<void, buffer_alignment>::const_pointer = nullptr)
      {
        const size_type chunk_size = count * sizeof(value_type);

        void* p = do_allocate<buffer_alignment>(chunk_size);

        return static_cast<pointer>(p);
      }

      void construct(pointer p, const value_type& x)
      {
        new(static_cast<void*>(p)) value_type(x);
      }

      void destroy(pointer p) { p->~value_type(); }

      void deallocate(pointer, size_type) { }
    };
  }

#endif // UTIL_RING_ALLOCATOR_2010_02_23_H_
