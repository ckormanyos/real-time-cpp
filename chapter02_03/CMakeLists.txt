cmake_minimum_required(VERSION 2.8)
project(Go)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

if ("${CROSS_COMPILE}" STREQUAL "")
  set (CROSS_COMPILE "avr-")
endif()

set (CMAKE_C_COMPILER   "${CROSS_COMPILE}gcc")
set (CMAKE_CXX_COMPILER "${CROSS_COMPILE}g++")
set (CMAKE_ASM_COMPILER "${CROSS_COMPILE}as")
#set (CMAKE_MAKE_PROGRAM "make") # "mingw32-make" "mingw64-make"



###########
# Debug or Release
###########
if (NOT CMAKE_BUILD_TYPE)
  ## set default to Release
  set(CMAKE_BUILD_TYPE Release)  # override with -DCMAKE_BUILD_TYPE=Debug
  message("==> CMAKE_BUILD_TYPE empty. Changing it to Release.")
else()
  message("==> CMAKE_BUILD_TYPE == ${CMAKE_BUILD_TYPE}.")
endif()


###########
# Warnings
###########
if (CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable")  # suppress
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations") # suppress
endif ()



##############
# C++ Standard
##############
if (NOT    CMAKE_VERSION VERSION_LESS 3.1)
  set(CMAKE_CXX_STANDARD   14)
  set(CMAKE_CXX_EXTENSIONS OFF)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()



# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)





###############
# Flags
###############
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmcu=atmega328p -fsigned-char -O2 -fno-exceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fstrict-enums -fno-use-cxa-atexit -fno-use-cxa-get-exception-ptr -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs")
# get rid of -rdynamic
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)



macro(replace_flag list flag repl_flag)
  string(REPLACE "${flag}" "${repl_flag}" ${list} "${${list}}")
endmacro()

# When cmake'ing with -DCMAKE_BUILD_TYPE=Release then
# by default "${CMAKE_CXX_FLAGS_RELEASE}" is "-O3 -DNDEBUG"
replace_flag(CMAKE_CXX_FLAGS_RELEASE "-O3" "-O2") ## change to -O2


##############
# Build
##############
set(target chapter02_03)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(src
  src/mcal/mcal.cpp
  src/mcal/mcal_gcc_cxx_completion.cpp
  src/mcal/avr/mcal_cpu.cpp
  src/mcal/avr/mcal_gpt.cpp
  src/mcal/avr/mcal_irq.cpp
  src/mcal/avr/mcal_led.cpp
  src/sys/start/sys_start.cpp
  target/micros/avr/startup/crt0.cpp
  target/micros/avr/startup/crt0_init_ram.cpp
  target/micros/avr/startup/crt1.cpp
  target/micros/avr/startup/int_vect.cpp
  )



include_directories(
  src
  src/mcal/avr
  src/util/STL
  src/util/STL_C++11_Compatibility
  src/util/STL_C++17_Compatibility
  )




add_executable(${target} ${src})
set_target_properties (${target}
  PROPERTIES LINK_FLAGS "-x none -mrelax -nostartfiles -Wl,--gc-sections -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/target/micros/avr/make/avr.ld,-Map,${CMAKE_BINARY_DIR}/${target}.map")




set(target_with_suffix "${target}${CMAKE_EXECUTABLE_SUFFIX}")

add_custom_command (TARGET ${target}  POST_BUILD
  COMMENT "Extract  : executable hex file : from ${target_with_suffix}"
  COMMAND ${CROSS_COMPILE}objcopy -O ihex                $<TARGET_FILE:${target}>    $<TARGET_FILE_DIR:${target}>/${target}.hex
  )

add_custom_command (TARGET ${target}  POST_BUILD
  COMMENT "Extract  : assembly list file  : from ${target_with_suffix}"
  COMMAND ${CROSS_COMPILE}objdump -h -S                  $<TARGET_FILE:${target}>  > $<TARGET_FILE_DIR:${target}>/${target}.lss
  )

add_custom_command (TARGET ${target}  POST_BUILD
  COMMENT "Extract  : size information    : from ${target_with_suffix}"
  COMMAND ${CROSS_COMPILE}size -A -t                     $<TARGET_FILE:${target}>  > $<TARGET_FILE_DIR:${target}>/${target}_size.txt
  )

add_custom_command (TARGET ${target}  POST_BUILD
  COMMENT "Extract  : name information    : from ${target_with_suffix}"
  COMMAND ${CROSS_COMPILE}nm --numeric-sort --print-size $<TARGET_FILE:${target}>  > $<TARGET_FILE_DIR:${target}>/${target}_nm.txt
  )

add_custom_command (TARGET ${target}  POST_BUILD
  COMMENT "Extract  : demangled names     : from ${target_with_suffix}"
  COMMAND ${CROSS_COMPILE}nm --numeric-sort --print-size $<TARGET_FILE:${target}>  | ${CROSS_COMPILE}c++filt  > $<TARGET_FILE_DIR:${target}>/${target}_cppfilt.txt
)
