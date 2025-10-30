#ifndef MCAL_WDG_2025_10_30_H
  #define MCAL_WDG_2025_10_30_H

  namespace mcal
  {
    namespace wdg
    {
      using config_type = void;

      inline auto init(const config_type*) -> void { }

      struct secure final
      {
        static auto trigger() -> void { }
      };
    }
  }

#endif // MCAL_WDG_2025_10_30_H
