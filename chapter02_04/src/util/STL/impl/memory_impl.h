#ifndef _MEMORY_IMPL_2010_02_23_H_
  #define _MEMORY_IMPL_2010_02_23_H_

  #include "cstddef_impl.h"
  #include "cstdint_impl.h"

  // Default placement versions of operator new.
  inline void* operator new  (size_t, void* my_p) throw() { return my_p; }
  inline void* operator new[](size_t, void* my_p) throw() { return my_p; }

  namespace std
  {
    class allocator_base
    {
    public:
      typedef std::size_t size_type;

    protected:
      allocator_base() { }

      // The allocator's buffer size.
      static constexpr size_type buffer_size = 32U;

      // The allocator's memory allocation.
      static void* do_allocate(const size_type size);

      static std::uint8_t  buffer[buffer_size];
      static std::uint8_t* get_ptr;
    };

    inline bool operator==(const allocator_base&,
                           const allocator_base&) throw()
    {
      return true;
    }

    inline bool operator!=(const allocator_base&,
                           const allocator_base&) throw()
    {
      return false;
    }

    template<typename T>
    class allocator;

    template<>
    class allocator<void> : public allocator_base
    {
    public:
      typedef void              value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;

      template <class U>
      struct rebind { typedef allocator<U> other; };
    };

    template<typename T>
    class allocator : public allocator_base
    {
    public:
      typedef T                 value_type;
      typedef value_type*       pointer;
      typedef const value_type* const_pointer;
      typedef value_type&       reference;
      typedef const value_type& const_reference;
      typedef std::ptrdiff_t    difference_type;

      allocator() throw() { }

      allocator(const allocator&) throw() { }

      template <class U>
      allocator(const allocator<U>&) throw() { }

      template<class U> 
      struct rebind { typedef allocator<U> other; };

      size_type max_size(void) const throw()
      {
        return buffer_size / sizeof(value_type);
      }

            pointer address(      reference x) const { return &x; }
      const_pointer address(const_reference x) const { return &x; }

      pointer allocate(size_type num,
                       allocator<void>::const_pointer = 0U) const
      {
        void* p = do_allocate(num * sizeof(value_type));
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

#endif // _MEMORY_IMPL_2010_02_23_H_
