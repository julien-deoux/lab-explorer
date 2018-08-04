# lab-explorer
My attempt at building a 2D game engine from scratch

## Target features
* Hardware accelerated rendering with OpenGL
* Realtime 2D lightning
* Realtime shadows
* Physics
* Level management (import, edit...)

## Requirements
* GLFW 3

## Build
Until an actual build system is properly set up, just execute the following command:
```
g++ -std=c++11 src/main.cc src/engine/*.cc -lglfw
```
