#ifndef _UTIL_PLACED_PTR_2010_02_23_H_
  #define _UTIL_PLACED_PTR_2010_02_23_H_

  #include <cstdint>
  #include <memory>

  namespace util
  {
    template<typename T>
    class placed_ptr
    {
    public:
      typedef T value_type;
      typedef value_type* pointer;

      placed_ptr()
      {
        new(static_cast<void*>(my_ptr())) value_type();
      }

      template<typename... parameters>
      placed_ptr(parameters... params)
      {
        new(my_ptr()) value_type(params...);
      }

      ~placed_ptr()
      {
        my_ptr()->~value_type();
      }

      pointer operator->() const { return my_ptr(); }
      pointer get(void) { return my_ptr(); }

    private:
      std::uint8_t my_buf[sizeof(T)];

      pointer my_ptr(void) const
      {
        return reinterpret_cast<pointer>(const_cast<void*>(static_cast<const void*>(my_buf)));
      }

      placed_ptr(const placed_ptr&);
      const placed_ptr& operator=(const placed_ptr&);
    };
  }

#endif // _UTIL_PLACED_PTR_2010_02_23_H_
