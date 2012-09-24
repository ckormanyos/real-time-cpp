#ifndef _MCAL_GPT_2011_10_20_H_
  #define _MCAL_GPT_2011_10_20_H_

  #include <util/utility/util_type.h>

  namespace mcal
  {
    namespace gpt
    {
      typedef void          config_type;
      typedef std::uint16_t value_type;

      void init(const config_type* config);

      value_type get_time_elapsed(void);

      template<typename T>
      inline T my_msec(const T& t) { return static_cast<T>(static_cast<T>(2UL) * t); }
    }
  }

#endif // _MCAL_GPT_2011_10_20_H_
