#ifndef _MCAL_WDT_2010_04_10_H_
  #define _MCAL_WDT_2010_04_10_H_

  extern "C" void mcal_wdg_trigger();

  namespace mcal
  {
    namespace wdg
    {
      typedef void config_type;

      void init(const config_type*);

      inline void trigger() { ::mcal_wdg_trigger(); }
    }
  }

#endif // _MCAL_WDT_2010_04_10_H_
