///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_19-001_final.cpp

class base
{
public:
  virtual ~base() { }

  base& operator=(const base&) = default;

protected:
  base() { }
};

class derived final : public base
{
public:
  derived() { }

  virtual ~derived() { }

  derived& operator=(const derived&) = default;
};

derived d;

int main()
{
}
