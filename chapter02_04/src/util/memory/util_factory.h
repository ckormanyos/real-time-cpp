#ifndef _UTIL_FACTORY_2012_02_19_H_
  #define _UTIL_FACTORY_2012_02_19_H_

  #include <cstdint>
  #include <memory>
  #include <util/utility/util_noncopyable.h>

  namespace util
  {
    class factory_product : private util::noncopyable
    {
    public:
      virtual ~factory_product() { }

      virtual void init() { }

    protected:
      factory_product() { }
    };

    template<typename T,
             typename Alloc = std::allocator<T>>
    class factory
    {
    public:
      typedef T     value_type;
      typedef T*    pointer_type;
      typedef Alloc allocator_type;

      template<typename function_type>
      static pointer_type make(function_type function)
      {
        pointer_type p = new(allocate()) value_type;
        function(p);
        return p;
      }

      template<typename function_type,
               typename... parameters>
      static pointer_type make(function_type function, parameters... params)
      {
        pointer_type p = new(allocate()) value_type(params...);
        function(p);
        return p;
      }

    private:
      static void* allocate()
      {
        return allocator_type().allocate(1U);
      }
    };
  }

#endif // _UTIL_FACTORY_2012_02_19_H_

/*
#include <util/memory/util_factory.h>

class something : public util::factory_product
{
public:
  something() { }
  virtual ~something() { }
};

class another : public util::factory_product
{
public:
  another(const int N) : n(N) { }
  virtual ~another() { }

private:
  int n;
};

something* p_something = util::factory<something>::make([](something* ps){ ps->init(); });
another*   p_another   = util::factory<another>::make([](another* pa){ pa->init(); }, 123);
*/
