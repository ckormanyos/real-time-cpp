#ifndef _UTIL_NONCOPYABLE_2008_12_16_H_
  #define _UTIL_NONCOPYABLE_2008_12_16_H_

  // A non-copyable base class, taken from boost::noncopyable.

  namespace util
  {
    namespace noncopyable_space // protection from unintended ADL
    {
      class noncopyable
      {
      protected:
        noncopyable() {}
        ~noncopyable() {}

     private:  // emphasize the following members are private
        noncopyable( const noncopyable& );
        const noncopyable& operator=( const noncopyable& );
      };
    }

    typedef noncopyable_space::noncopyable noncopyable;
  }

#endif // _UTIL_NONCOPYABLE_2008_12_16_H_
