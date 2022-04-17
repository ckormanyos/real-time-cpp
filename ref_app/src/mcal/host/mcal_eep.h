#ifndef MCAL_EEP_2018_12_15_H_
  #define MCAL_EEP_2018_12_15_H_

  #include <cstdint>

  namespace mcal
  {
    namespace eep
    {
      using config_type  = void;
      using address_type = std::uint64_t;

      inline auto init(const config_type*) -> void { }

      auto write(const address_type addr, const std::uint8_t data) -> void;
      auto read (const address_type addr) -> std::uint8_t;
    }
  }

#endif // MCAL_EEP_2018_12_15_H_
