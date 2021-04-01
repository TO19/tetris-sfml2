#!/bin/sh
BUILD_DIR=build
BIN_DIR=bin
EXECUTABLE_NAME=IDVCPP4

if [ ! -d "$BUILD_DIR" ]; then
  mkdir build && cd build
  else
  cd build && cd bin
fi

if [ ! -f "$EXECUTABLE_NAME" ]; then
  echo "Vous devez créer un executable avec ./scripts/build.sh"
  else
  ./$EXECUTABLE_NAME
fi