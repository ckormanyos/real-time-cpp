#ifndef _UTIL_RING_ALLOCATOR_BASE_2010_02_23_H_
  #define _UTIL_RING_ALLOCATOR_BASE_2010_02_23_H_

  #include <cstddef>
  #include <cstdint>

  namespace util
  {
    class ring_allocator_base
    {
    public:
      typedef std::size_t size_type;

    protected:
      ring_allocator_base() { }

      // The ring_allocator's default buffer size.
      static constexpr size_type default_buffer_size = 32U;

      // The ring_allocator's buffer size.
      static size_type buffer_size;

      // The ring_allocator's memory allocation.
      static void* do_allocate(const size_type size);

      static std::uint8_t  default_buffer[default_buffer_size];
      static std::uint8_t* buffer;
      static std::uint8_t* get_ptr;
    };

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
  }

#endif // _UTIL_RING_ALLOCATOR_BASE_2010_02_23_H_
