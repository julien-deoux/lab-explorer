#!/bin/sh

LOPTS='-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lBox2D'
COPTS='-std=c++11 -Iinclude'

g++ $COPTS $LOPTS src/main.cc src/glad/glad.cc src/engine/*.cc src/engine/renderer/*.cc src/engine/physics/*.cc src/engine/threading/*.cc
