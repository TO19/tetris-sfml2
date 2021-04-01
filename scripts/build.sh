#!/bin/sh
BUILD_DIR=build

if [ ! -d "$BUILD_DIR" ]; then
  mkdir build && cd build
  else
  cd build
fi

CXX=clang++ CC=clang cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build .