///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2009 - 2020.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UTIL_NUMERIC_CAST_2009_11_24_H_
  #define UTIL_NUMERIC_CAST_2009_11_24_H_

  #include <sstream>
  #include <string>

  namespace Util
  {
    template<typename T>
    inline T numeric_cast(const std::string& str)
    {
      // This could be done with a variation of "baselexical_cast".
      std::stringstream ss;
      ss << str;
      T t;
      ss >> t;
      return t;
    }
  }

#endif // UTIL_NUMERIC_CAST_2009_11_24_H_
