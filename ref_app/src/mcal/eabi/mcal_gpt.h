#ifndef _MCAL_GPT_2011_10_20_H_
  #define _MCAL_GPT_2011_10_20_H_

  #include <util/utility/util_type.h>

  namespace mcal
  {
    namespace gpt
    {
      typedef void          config_type;
      typedef std::uint64_t value_type;

      void init(const config_type*);

      // Elapsed time in microseconds.
      value_type get_time_elapsed();
    }
  }

#endif // _MCAL_GPT_2011_10_20_H_
