///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <iterator>

extern "C"
{
  struct ctor_type
  {
    using function_type = void(*)(void);
  };

  extern ctor_type::function_type _ctors_end;
  extern ctor_type::function_type _ctors_begin;
}

namespace crt
{
  void init_ctors();
}

void crt::init_ctors()
{
  using local_const_reverse_iterator = std::reverse_iterator<const ctor_type::function_type*>;

  std::for_each(local_const_reverse_iterator(&_ctors_end),
                local_const_reverse_iterator(&_ctors_begin),
                [](const ctor_type::function_type pf)
                {
                  pf();
                });
}
