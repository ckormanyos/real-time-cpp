///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_STATIC_ALLOCATOR_2010_02_23_H_
  #define _UTIL_STATIC_ALLOCATOR_2010_02_23_H_

  #include <cstddef>
  #include <cstdint>
  #include <memory>
  #include <util/utility/util_alignas.h>

  namespace util
  {
    class static_allocator_base
    {
    public:
      typedef std::size_t size_type;

      virtual ~static_allocator_base();

    protected:
      static_allocator_base() throw() { }

      static_allocator_base(const static_allocator_base&) throw() { }

      // The static allocator's default buffer size.
      static const size_type buffer_size = 32U;

      // The static allocator's buffer type.
      struct buffer_type
      {
        std::uint8_t data[buffer_size];
      };

      // The static allocator's memory allocation.
      template<const std::uint_fast8_t inner_buffer_alignment>
      static void* do_allocate(const size_type size,
                               size_type& remaining,
                               bool& is_overflow)
      {
        ALIGNAS(16) static buffer_type buffer;
        static std::uint8_t* get_ptr = buffer.data;

        // Get the newly allocated pointer.
        std::uint8_t* p = get_ptr;

        // Increment the get-pointer for the next allocation.
        // Be sure to handle the inner-buffer alignment.
        const std::uint_fast8_t align_increment  = inner_buffer_alignment - std::uint_fast8_t(size % inner_buffer_alignment);
        const size_type         buffer_increment = size + align_increment;

        get_ptr += buffer_increment;

        // Does this attempted allocation overflow the capacity of the buffer?
        is_overflow = (get_ptr >= (buffer.data + buffer_size));

        if(is_overflow)
        {
          // The requested size exceeds the capacity of the buffer.
          // In this design, however, there is no sensible error reaction.

          // Set the return value of the failed allocation to nullptr
          // and reset the get-pointer to its value before the allocation
          // attempt.
          p       = nullptr;
          get_ptr = get_ptr - buffer_increment;
        }

        // Calculate the remaining memory in the buffer based on
        // the value of the newly calculated get-pointer.
        remaining = size_type(&buffer.data[buffer_size] - get_ptr);

        return static_cast<void*>(p);
      }

    private:
      static_allocator_base& operator=(const static_allocator_base&);
    };

    static_allocator_base::~static_allocator_base() { }

    // Global comparison operators (required by the standard).
    inline bool operator==(const static_allocator_base&,
                           const static_allocator_base&) throw()
    {
      return true;
    }

    inline bool operator!=(const static_allocator_base&,
                           const static_allocator_base&) throw()
    {
      return false;
    }

    template<typename T,
             const std::uint_fast8_t inner_buffer_alignment = UINT8_C(4)>
    class static_allocator;

    template<const std::uint_fast8_t inner_buffer_alignment>
    class static_allocator<void, inner_buffer_alignment> : public static_allocator_base
    {
    public:
      static_assert(sizeof(T) <= buffer_size,
                    "The size of the allocation object can not exceed the buffer size.");

      static_assert(inner_buffer_alignment <= buffer_size,
                    "The granularity of the inner-buffer alignment can not exceed the buffer size.");

      typedef void              value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;

      template<typename U>
      struct rebind { typedef static_allocator<U, inner_buffer_alignment> other; };
    };

    template<typename T,
             const std::uint_fast8_t inner_buffer_alignment>
    class static_allocator : public static_allocator_base
    {
    public:
      typedef T                 value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;
      typedef value_type&       reference;
      typedef const value_type& const_reference;
      typedef std::ptrdiff_t    difference_type;

      static_allocator() throw() { }

      static_allocator(const static_allocator&) throw() : static_allocator_base(static_allocator()) { }

      template <typename U>
      static_allocator(const static_allocator<U, inner_buffer_alignment>&) throw() { }

      template<typename U> 
      struct rebind { typedef static_allocator<U, inner_buffer_alignment> other; };

      size_type max_size() const throw()
      {
        size_type remaining;
        bool      is_overflow;

        void* p = do_allocate<inner_buffer_alignment>(size_type(0U),
                                                      remaining,
                                                      is_overflow);

        static_cast<void>(is_overflow);

        return remaining / sizeof(value_type);
      }

            pointer address(      reference x) const { return &x; }
      const_pointer address(const_reference x) const { return &x; }

      pointer allocate(size_type count,
                       typename static_allocator<void, inner_buffer_alignment>::const_pointer = nullptr)
      {
        const size_type chunk_size = count * sizeof(value_type);

        size_type remaining;
        bool      is_overflow;

        void* p = do_allocate<inner_buffer_alignment>(chunk_size,
                                                      remaining,
                                                      is_overflow);

        static_cast<void>(remaining);
        static_cast<void>(is_overflow);

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

#endif // _UTIL_STATIC_ALLOCATOR_2010_02_23_H_
