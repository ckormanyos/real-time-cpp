///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_PLACED_PTR_2010_02_23_H_
  #define UTIL_PLACED_PTR_2010_02_23_H_

  #include <cstdint>
  #include <memory>

  #include <util/utility/util_noncopyable.h>

  namespace util
  {
    template<typename T>
    class placed_ptr : private util::noncopyable
    {
    public:
      typedef T           value_type;
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
      pointer get()              { return my_ptr(); }

    private:
      std::uint8_t my_buf[sizeof(T)];

      pointer my_ptr() const
      {
        return reinterpret_cast<pointer>(const_cast<void*>(static_cast<const void*>(my_buf)));
      }
    };
  }

#endif // UTIL_PLACED_PTR_2010_02_23_H_
