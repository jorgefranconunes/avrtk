AVR Toolkit - Setting up the Development Environment
====================================================





This document describes the steps for setting up the development
environment for the AVR Toolkit project.





== Requirements

You will need the software listed below for the development
environment.

* GNU Make 3.81+.

* GCC C and C++ compilers 4.4+ -- Required for compiling and running
  the unit tests on the development host.

* Toolchain for the Atmel AVR Microcontroller. This toolchain includes
  the following:

** GCC 4.4+ cross compiler for the AVR platform. Home:
   http://gcc.gnu.org/wiki/avr-gcc

** GNU binutils 2.20+ package (as, ld, objcopy and friends) for the AVR
   platform.

** AVR Libc 1.6.7+ -- Libc implementation for the AVR platform. It
   also includes very usefull functions and macros to interact
   directly with the hardware. Home: http://www.nongnu.org/avr-libc/

* Cpputest 3.5+ -- Unit testing framework. Home:
  http://cpputest.github.io/

* Avrdude 5.10+ -- Utility for uploading AVR compiled programs to an
  actual, real, there-in-front-of-you, Atmel microcontroller connected
  to your workstation.

* Doxygen 1.8.0+ -- Utility for generating the API documentation.

If you are developing under Fedora or CentOS you can install the
required development tools as following:

----
sudo yum install -y make
sudo yum install -y gcc g++
sudo yum install -y avr-gcc avr-bintutils avr-libc
sudo yum install -y avrdude
sudo yum install -y doxygen
----

For other distributions, you will have to guess how to install the
appropriate packages from the above example.

To install the Cpputest library you can do the following as a
suggestion.

----
mkdir ~/local
wget 'https://github.com/cpputest/cpputest.github.io/blob/master/releases/cpputest-3.5.tar.gz?raw=true'
tar xfz ./cpputest-3.5.tar.gz
cd ./cpputest-3.5
./configure --prefix=$HOME/local
make
make install
----

And after that the Cpputest installation base directory will be at
+$HOME/local/cpputest-3.5+





== Configure the development tree

In order to use the build system you will need to create a
configuration file named +Makfile.conf+ in the root of the source
tree. See an example below and adapt it to you specific environment:

----
AVRTK_CPPUTEST = $(HOME)/local/cpputest-3.5
----






== Building and running unit tests

To perform a full build without running the unit tests:

----
make
----

The unit tests are run on the development host. To compile and run the
unit tests:

----
make check
----

As currently the unit tests are all concentrated in the +avrtk-test+
module you can run them with a less verbose output like this:

----
make -C ./avrtk-test check
----





== Uploading a program to Arduino

TBD...





== Additional documentation

Datasheets for the Atmel ATmega48A/PA/88A/PA/168A/PA/328/P
microcontrollers: http://www.atmel.com/devices/atmega328p.aspx

Mapping between Arduino pins and ATMega328p pins:
http://arduino.cc/en/Hacking/PinMapping168

AVR Libc: http://www.nongnu.org/avr-libc/user-manual/index.html

