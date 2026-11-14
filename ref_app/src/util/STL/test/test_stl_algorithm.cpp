///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <vector>

auto test_stl_sanity_algorithm() -> bool;

auto test_stl_sanity_algorithm() -> bool
{
  std::vector<int> values { 4, 1, 3, 1, 5, 2 };
  std::vector<int> scratch(6U, 0);

  values[0U] = 4;
  values[1U] = 1;
  values[2U] = 3;
  values[3U] = 1;
  values[4U] = 5;
  values[5U] = 2;

  if(   ((std::min)(4, 2) != 2)
     || ((std::max)(4, 2) != 4)
     || ((std::min)(3, 3) != 3)
     || ((std::max)(3, 3) != 3)
     || (std::min_element(values.begin(), values.end()) != values.begin() + 1)
     || (std::max_element(values.begin(), values.end()) != values.begin() + 4)
     || (std::min_element(values.begin(), values.begin()) != values.begin()))
  {
    return false;
  }

  std::reverse(values.begin(), values.begin());
  std::reverse(values.begin(), values.begin() + 1);
  if(   (std::max_element(values.cbegin(), values.cbegin()) != values.cbegin())
     || (!std::all_of(values.cbegin(), values.cbegin(), [](int value) { return value > 0; }))
     || std::any_of(values.cbegin(), values.cbegin(), [](int value) { return value > 0; })
     || (!std::none_of(values.cbegin(), values.cbegin(), [](int value) { return value > 0; }))
     || (std::find_if(values.cbegin(), values.cbegin(), [](int value) { return value > 0; }) != values.cbegin())
     || (!std::all_of(values.cbegin(), values.cbegin() + 1, [](int value) { return value > 0; }))
     || (!std::any_of(values.cbegin(), values.cbegin() + 1, [](int value) { return value == 4; }))
     || (!std::none_of(values.cbegin(), values.cbegin() + 1, [](int value) { return value < 0; }))
     || (std::find_if_not(values.cbegin(), values.cbegin() + 1,
                          [](int value) { return value > 0; }) != values.cbegin() + 1)
     || (std::count(values.cbegin(), values.cbegin(), 1) != 0)
     || (!std::equal(values.cbegin(), values.cbegin(), values.cbegin(), values.cbegin())))
  {
    return false;
  }

  const int minmax_left = 4;
  const int minmax_right = 2;
  const auto minimum = std::minmax(minmax_left, minmax_right);
  const auto minimum_with_order = std::minmax(minmax_left, minmax_right,
                                              [](int left, int right) { return left > right; });
  if(   ((std::min)(4, 2, [](int left, int right) { return left > right; }) != 4)
     || ((std::max)(4, 2, [](int left, int right) { return left > right; }) != 2)
     || ((std::min)({ 3, 1, 2 }) != 1)
     || ((std::min)({ 3, 1, 2 }, [](int left, int right) { return left < right; }) != 1)
     || ((std::max)({ 3, 1, 2 }) != 3)
     || ((std::max)({ 3, 1, 2 }, [](int left, int right) { return left < right; }) != 3)
     || (minimum.first != 2) || (minimum.second != 4)
     || (minimum_with_order.first != 4) || (minimum_with_order.second != 2)
     || (std::min_element(values.begin(), values.end(), [](int left, int right) { return left > right; }) != values.begin() + 4)
     || (std::max_element(values.begin(), values.end(), [](int left, int right) { return left > right; }) != values.begin() + 1))
  {
    return false;
  }

  if(   (!std::lexicographical_compare(values.begin() + 1, values.begin() + 3,
                                       values.begin() + 3, values.begin() + 5))
     || (!std::lexicographical_compare(values.begin() + 1, values.begin() + 2,
                                       values.begin() + 3, values.begin() + 5,
                                       [](int left, int right) { return left < right; })))
  {
    return false;
  }

  if((std::copy(values.begin(), values.end(), scratch.begin()) != scratch.end()) || (scratch != values))
  {
    return false;
  }

  const auto even_end = std::copy_if(values.begin(), values.end(), scratch.begin(),
                                     [](int value) { return (value % 2) == 0; });

  if((even_end != scratch.begin() + 2) || (scratch[0U] != 4) || (scratch[1U] != 2))
  {
    return false;
  }

  const auto no_even_end = std::copy_if(values.begin(), values.end(), scratch.begin(),
                                        [](int value) { return value < 0; });

  if(no_even_end != scratch.begin())
  {
    return false;
  }

  std::copy(values.begin(), values.end(), scratch.begin());
  if(   (std::copy_backward(scratch.begin(), scratch.begin() + 4, scratch.end()) != scratch.begin() + 2)
     || (scratch[0U] != 4)
     || (scratch[1U] != 1)
     || (scratch[2U] != 4)
     || (scratch[3U] != 1)
     || (scratch[4U] != 3)
     || (scratch[5U] != 1))
  {
    return false;
  }

  std::fill(scratch.begin(), scratch.end(), 7);
  if(   (std::fill_n(scratch.begin() + 1, 2, 3) != scratch.begin() + 3)
     || (scratch[0U] != 7)
     || (scratch[1U] != 3)
     || (scratch[2U] != 3)
     || (scratch[3U] != 7))
  {
    return false;
  }
  if(std::fill_n(scratch.begin(), 0, 9) != scratch.begin())
  {
    return false;
  }

  int generated = 0;
  std::generate(scratch.begin(), scratch.begin() + 3, [&generated]() { return ++generated; });
  const auto generated_end = std::generate_n(scratch.begin() + 3, 3, [&generated]() { return ++generated; });

  if(   (generated_end != scratch.end())
     || (scratch[0U] != 1)
     || (scratch[2U] != 3)
     || (scratch[3U] != 4)
     || (scratch[5U] != 6))
  {
    return false;
  }

  std::copy(values.begin(), values.end(), scratch.begin());
  std::reverse(scratch.begin(), scratch.end());

  if((scratch[0U] != 2) || (scratch[5U] != 4))
  {
    return false;
  }

  scratch[0U] = 1;
  scratch[1U] = 2;
  scratch[2U] = 3;

  if((std::transform(values.begin(), values.begin() + 3, scratch.begin(), scratch.begin() + 3,
                     [](int left, int right) { return left + right; }) != scratch.end())
     || (scratch[3U] != 5) || (scratch[4U] != 3) || (scratch[5U] != 6))
  {
    return false;
  }

  if((std::transform(values.begin(), values.end(), scratch.begin(),
                     [](int value) { return value * 2; }) != scratch.end())
     || (scratch[0U] != 8)
     || (scratch[4U] != 10))
  {
    return false;
  }

  if(   (!std::equal(values.begin(), values.end(), values.begin()))
     || std::equal(values.begin(), values.end() - 1, values.begin() + 1)
     || (!std::equal(values.begin(), values.begin() + 2, values.begin(), values.begin() + 2))
     || std::equal(values.begin(), values.begin() + 2, values.begin(), values.begin() + 1)
     || (!std::equal(values.begin(), values.end(), values.begin(),
                     [](int left, int right) { return left == right; }))
     || (!std::equal(values.begin(), values.end(), values.begin(), values.end(),
                     [](int left, int right) { return left == right; })))
  {
    return false;
  }

  std::copy(values.begin(), values.end(), scratch.begin());
  scratch[2U] = 9;
  const auto mismatch = std::mismatch(values.begin(), values.end(), scratch.begin());
  const auto mismatch_with_ranges = std::mismatch(values.begin(), values.end(), scratch.begin(), scratch.end());
  const auto mismatch_with_predicate = std::mismatch(values.begin(), values.end(), scratch.begin(),
                                                     [](int left, int right) { return left == right; });
  const auto mismatch_with_ranges_and_predicate = std::mismatch(values.begin(), values.end(),
                                                                scratch.begin(), scratch.end(),
                                                                [](int left, int right) { return left == right; });
  if(   (mismatch.first != values.begin() + 2) || (mismatch.second != scratch.begin() + 2)
     || (mismatch_with_ranges.first != values.begin() + 2) || (mismatch_with_ranges.second != scratch.begin() + 2)
     || (mismatch_with_predicate.first != values.begin() + 2) || (mismatch_with_predicate.second != scratch.begin() + 2)
     || (mismatch_with_ranges_and_predicate.first != values.begin() + 2)
     || (mismatch_with_ranges_and_predicate.second != scratch.begin() + 2))
  {
    return false;
  }

  if(   (!std::all_of(values.begin(), values.end(), [](int value) { return value > 0; }))
     || (!std::any_of(values.begin(), values.end(), [](int value) { return value == 5; }))
     || (!std::none_of(values.begin(), values.end(), [](int value) { return value < 0; }))
     || (std::find_if(values.begin(), values.end(), [](int value) { return value > 4; }) != values.begin() + 4)
     || (std::find_if_not(values.begin(), values.end(), [](int value) { return value > 0; }) != values.end())
     || (std::count(values.begin(), values.end(), 1) != 2)
     || (std::count_if(values.begin(), values.end(), [](int value) { return (value % 2) == 0; }) != 2))
  {
    return false;
  }

  scratch[0U] = 1;
  scratch[1U] = 2;
  scratch[2U] = 2;
  scratch[3U] = 3;
  scratch[4U] = 4;
  scratch[5U] = 5;
  if(   (std::lower_bound(scratch.begin(), scratch.end(), 2) != scratch.begin() + 1)
     || (std::lower_bound(scratch.begin(), scratch.end(), 0) != scratch.begin())
     || (std::lower_bound(scratch.begin(), scratch.end(), 6) != scratch.end())
     || (!std::binary_search(scratch.begin(), scratch.end(), 4))
     || std::binary_search(scratch.begin(), scratch.end(), 6)
     || (std::search_n(scratch.begin(), scratch.end(), 2, 2) != scratch.begin() + 1)
     || (std::search_n(scratch.begin(), scratch.end(), 0, 9) != scratch.begin()))
  {
    return false;
  }

  scratch[0U] = 5;
  scratch[1U] = 4;
  scratch[2U] = 3;
  scratch[3U] = 2;
  scratch[4U] = 2;
  scratch[5U] = 1;
  if(   (std::lower_bound(scratch.begin(), scratch.end(), 2,
                          [](int left, int right) { return left > right; }) != scratch.begin() + 3)
     || (std::lower_bound(scratch.begin(), scratch.end(), 6,
                          [](int left, int right) { return left > right; }) != scratch.begin())
     || (!std::binary_search(scratch.begin(), scratch.end(), 4,
                             [](int left, int right) { return left > right; }))
     || std::binary_search(scratch.begin(), scratch.end(), 6,
                           [](int left, int right) { return left > right; })
     || (std::search_n(scratch.begin(), scratch.end(), 2, 2,
                       [](int left, int right) { return left == right; }) != scratch.begin() + 3)
     || (std::search_n(scratch.begin(), scratch.end(), 3, 2) != scratch.end())
     || (std::search_n(scratch.begin(), scratch.end(), 7, 2) != scratch.end()))
  {
    return false;
  }

  if((std::partition(values.begin(), values.begin(), [](int value) { return value > 0; }) != values.begin())
     || (std::partition(values.begin(), values.begin() + 1,
                        [](int value) { return value > 0; }) != values.begin() + 1)
     || (std::partition(values.begin(), values.begin() + 3, [](int value) { return value > 0; }) != values.begin() + 3)
     || (std::partition(values.begin(), values.begin() + 3, [](int value) { return value < 0; }) != values.begin()))
  {
    return false;
  }

  int sum = 0;
  const auto for_each_n_end = std::for_each_n(values.begin(), 3U, [&sum](int value) { sum += value; });
  if((for_each_n_end != values.begin() + 3) || (sum != 8))
  {
    return false;
  }

  sum = 0;
  std::for_each(values.begin(), values.end(), [&sum](int value) { sum += value; });
  if(sum != 16)
  {
    return false;
  }

  int swap_left = 1;
  int swap_right = 2;
  std::swap(swap_left, swap_right);
  if((swap_left != 2) || (swap_right != 1))
  {
    return false;
  }

  scratch[0U] = 3;
  scratch[1U] = 4;
  std::iter_swap(scratch.begin(), scratch.begin() + 1);
  if((scratch[0U] != 4) || (scratch[1U] != 3))
  {
    return false;
  }

  values[0U] = 1;
  values[1U] = 2;
  values[2U] = 3;
  scratch[0U] = 4;
  scratch[1U] = 5;
  scratch[2U] = 6;
  if((std::swap_ranges(values.begin(), values.begin() + 3, scratch.begin()) != scratch.begin() + 3)
     || (values[0U] != 4) || (values[2U] != 6) || (scratch[0U] != 1) || (scratch[2U] != 3))
  {
    return false;
  }

  const auto partition_point = std::partition(values.begin(), values.begin() + 3,
                                              [](int value) { return value < 6; });
  if((partition_point != values.begin() + 2) || (values[0U] >= 6) || (values[1U] >= 6) || (values[2U] != 6))
  {
    return false;
  }

  static int raw_left[2U]  { 1, 2 };
  static int raw_right[2U] { 3, 4 };
  raw_left[0U] = 1;
  raw_left[1U] = 2;
  raw_right[0U] = 3;
  raw_right[1U] = 4;
  std::swap(raw_left, raw_right);
  if((raw_left[0U] != 3) || (raw_left[1U] != 4) || (raw_right[0U] != 1) || (raw_right[1U] != 2))
  {
    return false;
  }

  return true;
}
