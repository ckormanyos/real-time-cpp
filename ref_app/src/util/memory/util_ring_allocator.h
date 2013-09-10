///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_RING_ALLOCATOR_2010_02_23_H_
  #define _UTIL_RING_ALLOCATOR_2010_02_23_H_

  #include <memory>

  namespace util
  {
    class ring_allocator_base
    {
    public:
      typedef std::size_t size_type;

    protected:
      ring_allocator_base() { }

      // The ring_allocator's default buffer size.
      static const size_type buffer_size = 256U;

      // The ring_allocator's memory allocation.
      static void* do_allocate(const size_type size);
    };

    // Global comparison operators (required in the standard).
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

    template<typename T, const std::size_t alignment = 4U>
    class ring_allocator;

    template<const std::size_t alignment>
    class ring_allocator<void, alignment> : public ring_allocator_base
    {
    public:
      typedef void              value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;

      template <class U>
      struct rebind { typedef ring_allocator<U, alignment> other; };
    };

    template<typename T, const std::size_t alignment>
    class ring_allocator : public ring_allocator_base
    {
    public:
      typedef T                 value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;
      typedef value_type&       reference;
      typedef const value_type& const_reference;
      typedef std::ptrdiff_t    difference_type;

      ring_allocator() throw() { }

      ring_allocator(const ring_allocator&) throw() { }

      template <class U>
      ring_allocator(const ring_allocator<U, alignment>&) throw() { }

      template<class U> 
      struct rebind { typedef ring_allocator<U, alignment> other; };

      size_type max_size() const throw()
      {
        return buffer_size / sizeof(size_type);
      }

            pointer address(      reference x) const { return &x; }
      const_pointer address(const_reference x) const { return &x; }

      pointer allocate(size_type num,
                       ring_allocator<void>::const_pointer = 0U)
      {
        std::size_t chunk_size = num * sizeof(value_type);

        const std::size_t misalignment = static_cast<std::size_t>(chunk_size % alignment);

        if(misalignment != static_cast<std::size_t>(0U))
        {
          chunk_size += static_cast<std::size_t>(alignment - misalignment);
        }

        void* p = do_allocate(chunk_size);

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

#endif // _UTIL_RING_ALLOCATOR_2010_02_23_H_
