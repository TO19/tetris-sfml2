#!/bin/sh
BUILD_DIR=build

if [ ! -d "$BUILD_DIR" ]; then
  mkdir build && cd build
  else
  cd build
fi

conan install .. --build=sfml --build=flac --build=missing
