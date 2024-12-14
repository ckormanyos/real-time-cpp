///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_FACTORY_2012_02_19_H
  #define UTIL_FACTORY_2012_02_19_H

  #include <cstddef>
  #include <cstdint>
  #include <memory>

  namespace util
  {
    class factory_product
    {
    public:
      virtual ~factory_product() { }

      virtual auto init() -> void = 0;

    protected:
      factory_product() { }
    };

    template<typename T,
             typename AllocatorType = std::allocator<T>>
    class factory
    {
    public:
      using value_type     = T;
      using pointer_type   = T*;
      using allocator_type = AllocatorType;

      static auto make() -> pointer_type
      {
        pointer_type p = new(allocate()) value_type();

        static_cast<factory_product*>(p)->init();

        return p;
      }

      template<typename... parameters>
      static auto make(parameters... params) -> pointer_type
      {
        pointer_type p = new(allocate()) value_type(params...);

        static_cast<factory_product*>(p)->init();

        return p;
      }

    private:
      static auto allocate() -> void*
      {
        return allocator_type().allocate( std::size_t { UINT8_C(1) } );
      }
    };
  }

#endif // UTIL_FACTORY_2012_02_19_H

/*

// See also link at GodBolt: https://godbolt.org/z/WrTTa8Eq9

#include <util/memory/util_factory.h>

#include <iostream>

class something : public util::factory_product
{
public:
  something() = default;
  virtual ~something() = default;

private:
  virtual void init() { }
};

class another : public util::factory_product
{
public:
  explicit another(const int m = 0, const int n = 0)
    : my_m(m),
      my_n(n) { }

  ~another() override = default;

  auto get_m() const -> int { return my_m; }
  auto get_n() const -> int { return my_n; }

private:
  const int my_m { };
  const int my_n { };

  auto init() -> void override { }
};

auto main() -> int
{
  something* p_something = util::factory<something>::make();
  another*   p_another   = util::factory<another  >::make(123, 456);

  std::cout << p_another->get_n() << '\n';
  std::cout << p_another->get_m() << std::endl;

  delete p_something;
  delete p_another;
}
*/
