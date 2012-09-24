#ifndef _INITIALIZER_LIST_IMPL_2012_02_14_H_
  #define _INITIALIZER_LIST_IMPL_2012_02_14_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include "cstddef_impl.h"

  // Implement std::initializer_list for compilers that do not yet support it.
  // See ISO/IEC Chapter 18.9.

  namespace std
  {
    template<class T>
    class initializer_list
    {
    public:
      typedef T           value_type;
      typedef const T&    reference;
      typedef const T&    const_reference;
      typedef std::size_t size_type;
      typedef const T*    iterator;
      typedef const T*    const_iterator;

      constexpr initializer_list() : my_array(0),
                                     my_length(0) { }

      constexpr size_type size(void) { return my_length; }

      constexpr const_iterator begin(void) { return my_array; }

      constexpr const_iterator end(void) { return begin() + my_length; }

    private:
      iterator my_array;
      const size_type my_length;

      constexpr initializer_list(const_iterator it,
                                 size_type sz) : my_array(it),
                                                 my_length(sz) { }
    };

    // Global begin/end pointers.
    template<typename T>
    constexpr const T* begin(initializer_list<T> lst) { return lst.begin(); }

    template<typename T>
    constexpr const T* end(initializer_list<T> lst) { return lst.end(); }
  }

#endif // _INITIALIZER_LIST_IMPL_2012_02_14_H_
