/*
 IPv6Address.cpp - Base class that provides IPv6Address
 Copyright (c) 2011 Adrian McEwen.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Arduino.h>
#include <IPv6Address.h>
#include <Print.h>

IPv6Address::IPv6Address()
{
    memset(_address.bytes, 0, sizeof(_address.bytes));
}

IPv6Address::IPv6Address(const uint8_t *address)
{
    memcpy(_address.bytes, address, sizeof(_address.bytes));
}

IPv6Address::IPv6Address(const uint32_t *address)
{
    memcpy(_address.bytes, (const uint8_t *)address, sizeof(_address.bytes));
}

IPv6Address& IPv6Address::operator=(const uint8_t *address)
{
    memcpy(_address.bytes, address, sizeof(_address.bytes));
    return *this;
}

bool IPv6Address::operator==(const uint8_t* addr) const
{
    return memcmp(addr, _address.bytes, sizeof(_address.bytes)) == 0;
}

size_t IPv6Address::printTo(Print& p) const
{
    size_t n = 0;
    for(int i = 0; i < 16; i+=2) {
        if(i){
            n += p.print(':');
        }
        n += p.printf("%02x", _address.bytes[i]);
        n += p.printf("%02x", _address.bytes[i+1]);

    }
    return n;
}

bool IPv6Address::fromString(const char *address)
{
    //format 0011:2233:4455:6677:8899:aabb:ccdd:eeff
    if(strlen(address) != 39){
        return false;
    }
    char * pos = (char *)address;
    size_t i = 0;
    for(i = 0; i < 16; i+=2) {
        if(!sscanf(pos, "%2hhx", &_address.bytes[i]) || !sscanf(pos+2, "%2hhx", &_address.bytes[i+1])){
            return false;
        }
        pos += 5;
    }
    return true;
}
