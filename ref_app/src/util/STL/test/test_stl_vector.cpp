///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <utility>
#include <vector>

auto test_stl_sanity_vector() -> bool;

auto test_stl_sanity_vector() -> bool
{
  std::vector<std::uint8_t> empty;
  if((!empty.empty()) || (empty.size() != 0U) || (empty.capacity() != 0U) || (empty.data() != nullptr))
  {
    return false;
  }

  std::vector<std::uint8_t> values { 1U, 2U, 3U };

  const std::vector<std::uint8_t> filled(2U, std::uint8_t { 9U });
  const std::vector<std::uint8_t> copied(values);
  const std::vector<std::uint8_t> ranged(values.begin(), values.end());

  if(   (values.size() != 3U)
     || (values.front() != 1U)
     || (values.back() != 3U)
     || (values[1U] != 2U)
     || (values.at(2U) != 3U))
  {
    return false;
  }

  if((filled.size() != 2U) || (filled.front() != 9U) || (filled.back() != 9U))
  {
    return false;
  }

  if((copied != values) || (ranged != values) || (filled == values) || !(values < filled))
  {
    return false;
  }

  std::vector<std::uint8_t> assigned;
  assigned = values;
  if(assigned != values)
  {
    return false;
  }

  values.reserve(6U);
  if((values.capacity() < 6U) || (values != copied))
  {
    return false;
  }

  values.resize(2U);
  if((values.size() != 2U) || (values.back() != 2U))
  {
    return false;
  }

  values.resize(3U, 3U);
  values.push_back(std::uint8_t { 4U });
  if((values.size() != 4U) || (values.back() != 4U))
  {
    return false;
  }

  values.pop_back();
  if((values.size() != 3U) || (values.back() != 3U))
  {
    return false;
  }

  assigned.assign(3U, std::uint8_t { 7U });
  if((assigned.size() != 3U) || (assigned[0U] != 7U) || (assigned[2U] != 7U))
  {
    return false;
  }

  values.clear();
  if((!values.empty()) || (values.capacity() < 6U))
  {
    return false;
  }

  std::vector<std::uint8_t> growing;
  growing.push_back(std::uint8_t { 1U });
  growing.push_back(std::uint8_t { 2U });
  growing.push_back(std::uint8_t { 3U });
  growing.push_back(std::uint8_t { 4U });
  growing.push_back(std::uint8_t { 5U });
  if((growing.size() != 5U) || (growing.capacity() < growing.size()) || (growing.back() != 5U))
  {
    return false;
  }

  std::vector<std::uint8_t> move_source { 4U, 5U };
  std::vector<std::uint8_t> moved(std::move(move_source));
  if((moved.size() != 2U) || (moved[0U] != 4U) || (moved[1U] != 5U) || (!move_source.empty()))
  {
    return false;
  }

  return true;
}
