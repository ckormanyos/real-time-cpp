///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_11-001_tuple_things_simple.cpp

#include <iostream>
#include <tuple>

class apple
{
public:
  apple() = default;
  ~apple() = default;

  auto setup() const -> void
  {
    std::cout << "In apple::setup()" << std::endl;
  }
};

class car
{
public:
  car() = default;
  ~car() = default;

  auto setup() const -> void
  {
    std::cout << "In car::setup()" << std::endl;
  }
};

class tiger
{
public:
  tiger() = default;
  ~tiger() = default;

  auto setup() const -> void
  {
    std::cout << "In tiger::setup()" << std::endl;
  }
};

auto do_something() -> void;

auto do_something() -> void
{
  // Create the tuple of things.
  std::tuple<apple, car, tiger> things;

  // Setup the things.
  std::get<0>(things).setup();
  std::get<1>(things).setup();
  std::get<2>(things).setup();
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
