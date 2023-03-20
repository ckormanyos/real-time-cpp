///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef DIGITAL_SIGNATURE_GENERIC_ECC_2023_02_18_H
#define DIGITAL_SIGNATURE_GENERIC_ECC_2023_02_18_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <string>

#include <math/checksums/generic_ecc/digital_signature_base.h>
#include <math/checksums/generic_ecc/ecc_elliptic_curve.h>

namespace generic_ecc
{
  template<const unsigned CurveBits,
           typename LimbType,
           const char* CurveName,
           const char* FieldCharacteristicP,
           const char* CurveCoefficientA,
           const char* CurveCoefficientB,
           const char* CoordGx,
           const char* CoordGy,
           const char* SubGroupOrderN,
           const int   SubGroupCoFactorH,
           typename HashType>
  class digital_signature_generic_ecc : public ecc_elliptic_curve<CurveBits,
                                                                  LimbType,
                                                                  CurveName,
                                                                  FieldCharacteristicP,
                                                                  CurveCoefficientA,
                                                                  CurveCoefficientB,
                                                                  CoordGx,
                                                                  CoordGy,
                                                                  SubGroupOrderN,
                                                                  SubGroupCoFactorH,
                                                                  HashType>,
                                        public digital_signature_base
  {
  private:
    using ecc_elliptic_curve_base_type = ecc_elliptic_curve<CurveBits,
                                                            LimbType,
                                                            CurveName,
                                                            FieldCharacteristicP,
                                                            CurveCoefficientA,
                                                            CurveCoefficientB,
                                                            CoordGx,
                                                            CoordGy,
                                                            SubGroupOrderN,
                                                            SubGroupCoFactorH,
                                                            HashType>;

    using hash_type = typename ecc_elliptic_curve_base_type::hash_type;

    using uint_type = typename ecc_elliptic_curve_base_type::uint_type;

  public:
    static constexpr auto my_secret_key_size() -> std::size_t { return static_cast<std::size_t>(CurveBits / static_cast<std::size_t>(UINT8_C(8))); }
    static constexpr auto my_public_key_size() -> std::size_t { return static_cast<std::size_t>(my_secret_key_size() * static_cast<std::size_t>(UINT8_C(2))); }
    static constexpr auto my_signature_size () -> std::size_t { return static_cast<std::size_t>(my_secret_key_size() * static_cast<std::size_t>(UINT8_C(2))); }

    constexpr digital_signature_generic_ecc() = default;
    constexpr digital_signature_generic_ecc(const digital_signature_generic_ecc&) = default;
    constexpr digital_signature_generic_ecc(digital_signature_generic_ecc&&) noexcept = default;

    auto operator=(const digital_signature_generic_ecc&) -> digital_signature_generic_ecc& = default;
    auto operator=(digital_signature_generic_ecc&&) noexcept -> digital_signature_generic_ecc& = default;

    ~digital_signature_generic_ecc() override = default;

    auto keypair_generate(      std::uint8_t* public_key_data,
                                std::size_t*  public_key_size_hint_pointer,
                                std::uint8_t* secret_key_data,
                                std::size_t*  secret_key_size_hint_pointer,
                          const std::uint8_t* seed_data,
                          const std::size_t   seed_size) const -> bool override
    {
      uint_type seed_keygen { };

      static_cast<void>
      (
        import_bits(seed_keygen, seed_data, seed_data + seed_size)
      );

      const auto keypair = ecc_elliptic_curve_base_type::make_keypair(&seed_keygen);

      const bool result_keygen_is_ok =
        ecc_elliptic_curve_base_type::is_on_curve
        (
          {
            keypair.second.first,
            keypair.second.second
          }
        );

      if(secret_key_size_hint_pointer != nullptr)
      {
        *secret_key_size_hint_pointer = get_secret_key_size();
      }

      if(public_key_size_hint_pointer != nullptr)
      {
        *public_key_size_hint_pointer = get_public_key_size();
      }

      constexpr auto chunk_size = static_cast<unsigned>(UINT8_C(8));

      if(secret_key_data != nullptr)
      {
        static_cast<void>
        (
          export_bits(keypair.first, secret_key_data, chunk_size)
        );
      }

      if(public_key_data != nullptr)
      {
        static_cast<void>
        (
          export_bits(keypair.second.first, public_key_data + static_cast<std::size_t>(UINT8_C(0)), chunk_size)
        );

        static_cast<void>
        (
          export_bits(keypair.second.second, public_key_data + static_cast<std::size_t>(my_public_key_size() / static_cast<std::size_t>(UINT8_C(2))), chunk_size)
        );
      }

      return result_keygen_is_ok;
    }

    auto sign_initialize() -> void override
    {
      my_hash.initialize();
    }

    auto sign_process_data  (const std::uint8_t* message_data,
                             const std::size_t   message_size) -> void override
    {
      my_hash.process(message_data, static_cast<typename hash_type::count_type>(message_size));
    }

    auto sign_finalize(      std::uint8_t* signature_data,
                             std::size_t*  signature_size,
                       const std::uint8_t* secret_key_data,
                       const std::size_t   secret_key_size,
                       const std::uint8_t* seed_data,
                       const std::size_t   seed_size) -> bool override
    {
      my_hash.finalize();

      typename hash_type::result_type hash_result { };

      my_hash.get_result(hash_result.data());

      uint_type z_msg_hash { };
      uint_type priv_value { };

      static_cast<void>
      (
        import_bits(z_msg_hash, hash_result.cbegin(), hash_result.cend())
      );

      static_cast<void>
      (
        import_bits(priv_value, secret_key_data, secret_key_data + secret_key_size)
      );

      auto sig = std::pair<uint_type, uint_type> { };

      if(seed_data == nullptr)
      {
        sig = ecc_elliptic_curve_base_type::sign_message_ph(priv_value, z_msg_hash, nullptr);
      }
      else
      {
        uint_type seed_value { };

        static_cast<void>
        (
          import_bits(seed_value, seed_data, seed_data + seed_size)
        );

        sig = ecc_elliptic_curve_base_type::sign_message_ph(priv_value, z_msg_hash, &seed_value);
      }

      if(signature_size != nullptr)
      {
        *signature_size = my_signature_size();
      }

      if(signature_data != nullptr)
      {
        constexpr auto chunk_size = static_cast<unsigned>(UINT8_C(8));

        static_cast<void>
        (
          export_bits(sig.first, signature_data + static_cast<std::size_t>(UINT8_C(0)), chunk_size)
        );

        static_cast<void>
        (
          export_bits(sig.second, signature_data + static_cast<std::size_t>(my_signature_size() / static_cast<std::size_t>(UINT8_C(2))), chunk_size)
        );
      }

      return true;
    }

    auto verify_initialize() -> void override
    {
      my_hash.initialize();
    }

    auto verify_process_data(const std::uint8_t* message_data,
                             const std::size_t   message_size) -> void override
    {
      my_hash.process(message_data, static_cast<typename hash_type::count_type>(message_size));
    }

    auto verify_finalize(const std::uint8_t* signature_data,
                         const std::size_t   signature_size,
                         const std::uint8_t* public_key_data,
                         const std::size_t   public_key_size) -> bool override
    {
      static_cast<void>(signature_size);
      static_cast<void>(public_key_size);

      auto result_verify_is_ok = false;

      if((signature_data != nullptr) && (public_key_data != nullptr))
      {
        std::pair<uint_type, uint_type> pub_values { };
        std::pair<uint_type, uint_type> sig_values { };

        static_cast<void>
        (
          import_bits(pub_values.first, public_key_data + static_cast<std::size_t>(UINT8_C(0)), public_key_data + static_cast<std::size_t>(my_public_key_size() / static_cast<std::size_t>(UINT8_C(2))))
        );

        static_cast<void>
        (
          import_bits(pub_values.second, public_key_data + static_cast<std::size_t>(my_public_key_size() / static_cast<std::size_t>(UINT8_C(2))), public_key_data + my_public_key_size())
        );

        static_cast<void>
        (
          import_bits(sig_values.first, signature_data + static_cast<std::size_t>(UINT8_C(0)), signature_data + static_cast<std::size_t>(my_signature_size() / static_cast<std::size_t>(UINT8_C(2))))
        );

        static_cast<void>
        (
          import_bits(sig_values.second, signature_data + static_cast<std::size_t>(my_signature_size() / static_cast<std::size_t>(UINT8_C(2))), signature_data + my_signature_size())
        );

        my_hash.finalize();

        typename hash_type::result_type hash_result { };

        my_hash.get_result(hash_result.data());

        uint_type z_msg_hash { };

        static_cast<void>
        (
          import_bits(z_msg_hash, hash_result.cbegin(), hash_result.cend())
        );

        result_verify_is_ok = ecc_elliptic_curve_base_type::verify_signature_ph(pub_values, z_msg_hash, sig_values);
      }

      return result_verify_is_ok;
    }

    auto get_public_key_size() const -> std::size_t override { return my_public_key_size(); }
    auto get_secret_key_size() const -> std::size_t override { return my_secret_key_size(); }
    auto get_signature_size () const -> std::size_t override { return my_signature_size(); }

  private:
    hash_type my_hash { };
  };
} // namespace generic_ecc

#endif // DIGITAL_SIGNATURE_GENERIC_ECC_2023_02_18_H
