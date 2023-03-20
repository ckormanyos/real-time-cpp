///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef DIGITAL_SIGNATURE_BASE_2023_02_18_H
#define DIGITAL_SIGNATURE_BASE_2023_02_18_H

#include <cstddef>
#include <cstdint>

namespace generic_ecc
{
  class digital_signature_base
  {
  public:
    virtual ~digital_signature_base() = default;

    virtual auto keypair_generate   (      std::uint8_t*,                       // public_key_data
                                           std::size_t*,                        // public_key_size_hint_pointer
                                           std::uint8_t*,                       // secret_key_data
                                           std::size_t*,                        // secret_key_size_hint_pointer
                                     const std::uint8_t*,                       // seed_data
                                     const std::size_t) const -> bool = 0;      // seed_size

    virtual auto sign_initialize    () -> void = 0;

    virtual auto sign_process_data  (const std::uint8_t*,                       // message_data
                                     const std::size_t) -> void = 0;            // message_size

    virtual auto sign_finalize      (      std::uint8_t*,                       // signature_data
                                           std::size_t*,                        // signature_size
                                     const std::uint8_t*,                       // secret_key_data
                                     const std::size_t,                         // secret_key_size
                                     const std::uint8_t*,                       // seed_data
                                     const std::size_t) -> bool = 0;            // seed_size

    virtual auto verify_initialize  () -> void = 0;

    virtual auto verify_process_data(const std::uint8_t*,                       // message_data
                                     const std::size_t) -> void = 0;            // message_size

    virtual auto verify_finalize    (const std::uint8_t*,                       // signature_data
                                     const std::size_t,                         // signature_size
                                     const std::uint8_t*,                       // public_key_data
                                     const std::size_t) -> bool = 0;            // public_key_size

    virtual auto get_public_key_size() const -> std::size_t = 0;
    virtual auto get_secret_key_size() const -> std::size_t = 0;
    virtual auto get_signature_size () const -> std::size_t = 0;

    auto sign(const std::uint8_t* message_data,
              const std::size_t   message_size,
              const std::uint8_t* secret_key_data,
              const std::size_t   secret_key_size,
                    std::uint8_t* signature_data,
                    std::size_t*  signature_size,
              const std::uint8_t* seed_data,
              const std::size_t   seed_size) -> bool
    {
      this->sign_initialize();
      this->sign_process_data(message_data, message_size);

      const bool sign_is_ok = this->sign_finalize(signature_data,
                                                  signature_size,
                                                  secret_key_data,
                                                  secret_key_size,
                                                  seed_data,
                                                  seed_size);

      return sign_is_ok;
    }

    auto verify(const std::uint8_t* message_data,
                const std::size_t   message_size,
                const std::uint8_t* signature_data,
                const std::size_t   signature_size,
                const std::uint8_t* public_key_data,
                const std::size_t   public_key_size) -> bool
    {
      this->verify_initialize();
      this->verify_process_data(message_data, message_size);

      const bool verify_is_ok = this->verify_finalize(signature_data,
                                                      signature_size,
                                                      public_key_data,
                                                      public_key_size);

      return verify_is_ok;
    }


  protected:
    constexpr digital_signature_base() = default;
    constexpr digital_signature_base(const digital_signature_base&) = default;
    constexpr digital_signature_base(digital_signature_base&&) noexcept = default;

    auto operator=(const digital_signature_base&) -> digital_signature_base& = default;
    auto operator=(digital_signature_base&&) noexcept -> digital_signature_base& = default;
  };

} // namespace generic_ecc

#endif // DIGITAL_SIGNATURE_BASE_2023_02_18_H
