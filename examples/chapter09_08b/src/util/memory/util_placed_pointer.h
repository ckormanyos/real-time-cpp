///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_PLACED_PTR_2010_02_23_H
  #define UTIL_PLACED_PTR_2010_02_23_H

  #include <util/utility/util_noncopyable.h>

  #include <cstdint>
  #include <memory>

  namespace util
  {
    template<typename T>
    class placed_ptr : private util::noncopyable
    {
    public:
      using value_type = T;
      using pointer = value_type*;

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

      auto operator->() const -> pointer { return my_ptr(); }
      auto get() -> pointer { return my_ptr(); }

    private:
      std::uint8_t my_buf[sizeof(T)];

      auto my_ptr() const -> pointer
      {
        return reinterpret_cast<pointer>(const_cast<void*>(static_cast<const void*>(my_buf)));
      }
    };
  }

#endif // UTIL_PLACED_PTR_2010_02_23_H
