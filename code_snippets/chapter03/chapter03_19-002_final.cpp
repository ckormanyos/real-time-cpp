///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_19-002_final.cpp

class base
{
public:
  virtual ~base() { }

  auto operator=(const base&) -> base& = default;

protected:
  base() = default;
};

class derived final : public base
{
public:
  derived() = default;

  ~derived() override = default;

  auto operator=(const derived&) -> derived& = default;
};

/*
class derived_another : public derived
{
  // This class should result in an error.
};
*/

derived d { };

auto main() -> int
{
}
