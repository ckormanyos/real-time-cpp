///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HASH_STREAM_BASE_2023_04_30_H
  #define HASH_STREAM_BASE_2023_04_30_H

  #include <limits>

  #include <math/checksums/hash/hash_detail.h>

  namespace math { namespace checksums { namespace hash {

  class hash_stream_base
  {
  public:
    using count_type = std::uint32_t;

    hash_stream_base() = default;
    virtual ~hash_stream_base() = default;

    virtual auto initialize() -> void = 0;

    virtual auto process(const std::uint8_t* message, const count_type count) -> void = 0;

    virtual auto finalize() -> void = 0;

    auto hash(const std::uint8_t* message, const count_type count) -> void
    {
      this->initialize();
      this->process(message, count);
      this->finalize();
    }
  };

  } } } // namespace math::checksums::hash

#endif // HASH_STREAM_BASE_2023_04_30_H
