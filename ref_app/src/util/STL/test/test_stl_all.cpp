///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

bool test_stl_sanity_all();

auto test_stl_sanity_all() -> bool
{
  extern auto test_stl_sanity_algorithm() -> bool;
  extern auto test_stl_sanity_functional() -> bool;
  extern auto test_stl_sanity_string() -> bool;
  extern auto test_stl_sanity_vector() -> bool;

  const bool algorithm_tests_pass  = test_stl_sanity_algorithm();
  const bool functional_tests_pass = test_stl_sanity_functional();
  const bool string_tests_pass     = test_stl_sanity_string();
  const bool vector_tests_pass     = test_stl_sanity_vector();

  const bool
    all_tests_pass
    {
         algorithm_tests_pass
      && functional_tests_pass
      && string_tests_pass
      && vector_tests_pass
    };

  return all_tests_pass;
}
