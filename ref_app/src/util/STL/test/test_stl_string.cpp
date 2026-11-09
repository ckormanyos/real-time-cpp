///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <string>
#include <utility>

auto test_stl_sanity_string() -> bool;

auto test_stl_sanity_string() -> bool
{
  std::string empty;
  if((!empty.empty()) || (empty.size() != 0U) || (empty.c_str()[0] != '\0'))
  {
    return false;
  }

  const std::string literal("abc");
  const std::string repeated(3U, 'x');
  const std::string counted("a\0b", 3U);

  if((literal.size() != 3U) || (literal[1U] != 'b') || (literal.c_str()[3U] != '\0'))
  {
    return false;
  }

  if((repeated.size() != 3U) || (repeated[0U] != 'x') || (repeated[2U] != 'x'))
  {
    return false;
  }

  if(   (counted.size() != 3U)
     || (counted[0U] != 'a')
     || (counted[1U] != '\0')
     || (counted[2U] != 'b')
     || (counted.c_str()[3U] != '\0'))
  {
    return false;
  }

  const std::string copied(literal);
  std::string assigned;
  assigned = literal;

  if((copied != literal) || (assigned.compare(literal) != 0) || !(literal < repeated))
  {
    return false;
  }

  std::string growing("abc");
  growing.append("d", 1U);
  growing.push_back('e');

  if(   (growing.size() != 5U)
     || (growing.capacity() < growing.size())
     || (growing != std::string("abcde")))
  {
    return false;
  }

  std::string self_appended("xy");
  self_appended.append(self_appended);

  if((self_appended.size() != 4U) || (self_appended != std::string("xyxy")))
  {
    return false;
  }

  std::string moved(std::move(assigned));

  if((moved != literal) || (!assigned.empty()) || (assigned.c_str()[0] != '\0'))
  {
    return false;
  }

  std::string move_assigned;
  move_assigned = std::move(moved);

  if((move_assigned != literal) || (!moved.empty()) || (moved.c_str()[0] != '\0'))
  {
    return false;
  }

  return true;
}
