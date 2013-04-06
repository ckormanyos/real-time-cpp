#ifndef _UTIL_FACTORY_2012_02_19_H_
  #define _UTIL_FACTORY_2012_02_19_H_

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
             typename Alloc = std::allocator<T>>
    class factory
    {
    public:
      typedef T     value_type;
      typedef T*    pointer_type;
      typedef Alloc allocator_type;

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

private:
  virtual void init() { }
};

class another : public util::factory_product
{
public:
  another(const int m_, const int n_) : m(m_),
                                        n(n_) { }
  virtual ~another() { }

private:
  const int m;
  const int n;

  virtual void init() { }
};

something* p_something = util::factory<something>::make();
another*   p_another   = util::factory<another>::make(123, 456);
*/
