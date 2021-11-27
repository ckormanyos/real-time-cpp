@rem
@rem  Copyright Christopher Kormanyos 2007 - 2018.
@rem  Distributed under the Boost Software License,
@rem  Version 1.0. (See accompanying file LICENSE_1_0.txt
@rem  or copy at http://www.boost.org/LICENSE_1_0.txt)
@rem

@rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
@rem
@rem Description of the build options used in the build command below.
@rem
@rem %1: target
@rem       avr              : ATMEL(R) AVR(R) ATmega328P i.e., Arduino compatible
@rem
@rem %2: buildtype
@rem                        : None. Build the project. Compile and link outdated files only.
@rem       rebuild          : Rebuild the project. Clean the project. Compile and link all files.
@rem       clean_all        : Clean the project only.
@rem
@rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

@Set build_command=tools\Util\msys64\usr\bin\make.exe -f target/app/make/app_make.gmk %2 TGT=%1

@echo Executing Command: %build_command%

@%build_command%
