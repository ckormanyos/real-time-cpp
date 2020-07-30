///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_FACTORY_2012_02_19_H_
  #define UTIL_FACTORY_2012_02_19_H_

  #include <memory>

  #include <util/utility/util_noncopyable.h>

  namespace util
  {
    class factory_product : private util::noncopyable
    {
    public:
      virtual ~factory_product() { }

      virtual void init() = 0;

    protected:
      factory_product() { }
    };

    template<typename T,
             typename alloc = std::allocator<T>>
    class factory
    {
    public:
      typedef T     value_type;
      typedef T*    pointer_type;
      typedef alloc allocator_type;

      static pointer_type make()
      {
        pointer_type p = new(allocate()) value_type();
        static_cast<factory_product*>(p)->init();
        return p;
      }

      template<typename... parameters>
      static pointer_type make(parameters... params)
      {
        pointer_type p = new(allocate()) value_type(params...);
        static_cast<factory_product*>(p)->init();
        return p;
      }

    private:
      static void* allocate()
      {
        return allocator_type().allocate(1U, nullptr);
      }
    };
  }

#endif // UTIL_FACTORY_2012_02_19_H_

/*
#include <util/memory/util_factory.h>

class something : public util::factory_product
{
public:
  something() { }
  virtual ~something() { }

private:
  virtual void init() { }
};

class another : public util::factory_product
{
public:
  another(const int m, const int n) : my_m(m),
                                      my_n(n) { }

  virtual ~another() { }

private:
  const int my_m;
  const int my_n;

  virtual void init() { }
};

something* p_something = util::factory<something>::make();
another*   p_another   = util::factory<another  >::make(123, 456);
*/
