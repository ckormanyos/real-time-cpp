@rem
@rem  Copyright Christopher Kormanyos 2007 - 2013.
@rem  Distributed under the Boost Software License,
@rem  Version 1.0. (See accompanying file LICENSE_1_0.txt
@rem  or copy at http://www.boost.org/LICENSE_1_0.txt)
@rem

@rem
@rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

@Set build_command=tools\Util\MinGW\msys\1.0\bin\make.exe -f target/app/make/app_make.gmk %2 TGT=%1

@echo Executing Command: %build_command%

@%build_command%
