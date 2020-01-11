# Linux

apt-get install gcc-avr avr-libc
./build.sh "$(dirname $(which avr-g++))" avr    ## bash will typically the dirname command, such this it is equivalent to:  ./build.sh /usr/bin avr
