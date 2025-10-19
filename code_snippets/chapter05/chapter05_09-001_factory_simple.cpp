///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_09-001_factory_simple.cpp

#include <cstddef>
#include <cstdint>
#include <iostream>

template<typename type_to_make>
type_to_make* factory(void* mem)
{
  // Construct a new pointer of kind type_to_make
  // with the placement-new operator.

  type_to_make* p = new(mem) type_to_make;

  return p;
}

class something
{
public:
  something() = default;

  ~something() = default;

  void do_something() const
  {
    std::cout << "In member function do_something(...)" << std::endl;
  }
};

extern void* pool;

something* ps = factory<something>(pool);

auto main() -> int;

auto main() -> int
{
  ps->do_something();
}

// Consider the buffer and pool pointer to be in another file.
std::uint8_t buffer[std::size_t { UINT16_C(256) }];

void* pool { reinterpret_cast<void*>(&buffer[0U]) };
