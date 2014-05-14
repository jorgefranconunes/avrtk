





== Seting up the development environment

Download CppUTest from http://cpputest.github.io/ and install it
somewhere.


Install GNU autotools and the AVR toolchain:

----
yum install \
    autoconf \
    automake \
    avr-gcc \
    avr-libc \
    avrdude
----


Build evevryting:

----
autoreconf --install
mkdir build
cd ./build
../configure --with-cpputest=PATH_TO_CPPUTEST_HOME
make
----


Run unit tests in the host:

----
make check
----





== Miscellanea

Usefull tips on using autotools:
http://www.clearchain.com/blog/posts/autotools

