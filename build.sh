#!/bin/sh

LOPTS='-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl'
COPTS='-std=c++11 -Iinclude'

g++ $COPTS $LOPTS src/main.cc src/engine/*.cc src/engine/renderer/*.cc
