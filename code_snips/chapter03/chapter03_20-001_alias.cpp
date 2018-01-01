///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_20-001_alias.cpp

// Traditional typedef.
typedef unsigned int uint_type;

// C++11 alias.
using uint_type_alias = unsigned int;

uint_type       ui( 1U);
uint_type_alias ua(42U);

int main()
{
}
