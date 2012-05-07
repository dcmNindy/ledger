#!/bin/sh

# This build script is for OS X Lion users who have compiled openmpi and
# clang-3.1 from MacPorts.  I build my own Boost instead of using MacPorts'
# Boost in order to get better debugging support, and to link with libc++.

export PATH=$PATH:/opt/local/lib/openmpi/bin

make CXX=icc LD=icc CC=icc OPTJ=-j20     \
     BOOST_TOOLSET=intel-darwin DIR_SUFFIX=intel                             \
     BOOST_DEFINES="-sICU_PATH=/opt/local cxxflags=\"-fast -I/opt/local/include\" linkflags=\"-fast -L/opt/local/lib\""
