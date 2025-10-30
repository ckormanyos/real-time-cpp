#ifndef MCAL_GPT_2025_10_30_H
  #define MCAL_GPT_2025_10_30_H

  #include <cstdint>

  namespace mcal
  {
    namespace gpt
    {
      using config_type = void;
      using value_type = std::uint64_t;

      auto init(const config_type*) -> void;

      struct secure final
      {
        static auto get_time_elapsed() -> value_type;
      };
    }
  }

#endif // MCAL_GPT_2025_10_30_H
