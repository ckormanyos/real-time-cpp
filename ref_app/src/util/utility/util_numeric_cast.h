///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2009 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UTIL_NUMERIC_CAST_2009_11_24_H_
  #define UTIL_NUMERIC_CAST_2009_11_24_H_

  #include <sstream>
  #include <string>
  #include <type_traits>

  namespace Util
  {
    template<typename T>
    inline T numeric_cast(const std::string& str)
    {
      constexpr bool numeric_cast_is_signed = (std::numeric_limits<T>::is_signed == true);

      constexpr bool numeric_cast_is_small_type =
        (   ((numeric_cast_is_signed == true)  && (std::numeric_limits<T>::digits <= 31))
         || ((numeric_cast_is_signed == false) && (std::numeric_limits<T>::digits <= 32)));

      using value_type = typename std::conditional<(numeric_cast_is_small_type == true),
                                                    typename std::conditional<(numeric_cast_is_signed == true),
                                                                               std::int32_t,
                                                                               std::uint32_t>::type, T
                                                  >::type;

      // This could be done with a variation of "baselexical_cast".
      std::stringstream ss;
      ss << str;
      value_type t;
      ss >> t;
      return (T) t;
    }
  }

#endif // UTIL_NUMERIC_CAST_2009_11_24_H_
