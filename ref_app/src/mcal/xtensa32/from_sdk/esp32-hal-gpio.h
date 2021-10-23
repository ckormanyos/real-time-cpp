///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

///////////////////////////////////////////////////////////////////////////////
// Original copyright:
//

// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MAIN_ESP32_HAL_GPIO_H_
  #define MAIN_ESP32_HAL_GPIO_H_

  #include <stdint.h>

  #ifdef __cplusplus
  extern "C"
  {
  #endif

  #define LOW               0x0
  #define HIGH              0x1

  #define INPUT             0x01
  #define OUTPUT            0x02
  #define PULLUP            0x04
  #define INPUT_PULLUP      0x05
  #define PULLDOWN          0x08
  #define INPUT_PULLDOWN    0x09
  #define OPEN_DRAIN        0x10
  #define OUTPUT_OPEN_DRAIN 0x12
  #define SPECIAL           0xF0
  #define FUNCTION_1        0x00
  #define FUNCTION_2        0x20
  #define FUNCTION_3        0x40
  #define FUNCTION_4        0x60
  #define FUNCTION_5        0x80
  #define FUNCTION_6        0xA0
  #define ANALOG            0xC0

  //Interrupt Modes
  //#define DISABLED  0x00
  //#define RISING    0x01
  //#define FALLING   0x02
  //#define CHANGE    0x03
  //#define ONLOW     0x04
  //#define ONHIGH    0x05
  //#define ONLOW_WE  0x0C
  //#define ONHIGH_WE 0x0D

  void pinMode     (const uint8_t pin, const uint8_t mode);
  void digitalWrite(const uint8_t pin, const uint8_t val);
  int  digitalRead (const uint8_t pin);

  #ifdef __cplusplus
  }
  #endif

#endif /* MAIN_ESP32_HAL_GPIO_H_ */
