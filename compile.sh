#! /bin/bash

make clean
rm -rf bin*
rm -rf Makefile game.make
premake5 gmake2
make
./bin/arm64/game
