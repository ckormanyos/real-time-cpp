///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_14-001_regex_basics.cpp

#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main()
{
  const std::regex rx(  std::string("([_0-9a-zA-Z]+)")
                      + std::string("[[:space:]]+")
                      + std::string("([0-9a-fA-F]+)")
                      + std::string("[[:space:]]+")
                      + std::string("([0-9]+)"));

  const std::string str =
    "_My_Variable123    03FFB004    4";

  std::match_results<std::string::const_iterator> mr;

  if(std::regex_match(str, mr, rx))
  {
    std::copy(mr.begin(),
              mr.end(),
              std::ostream_iterator
                <std::string>(std::cout, "\n"));
  }
}
