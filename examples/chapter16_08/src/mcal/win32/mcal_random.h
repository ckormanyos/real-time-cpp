///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_RANDOM_2020_06_11_H_
  #define MCAL_RANDOM_2020_06_11_H_

  #include <random>

  namespace mcal { namespace random {

  using default_random_engine = std::independent_bits_engine<std::default_random_engine, std::size_t(32U), std::uint32_t>;

  } }

#endif // MCAL_RANDOM_2020_06_11_H_
