#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>

#include "game/Game.h"

class Engine
{
private:
  GLFWwindow *window;
  Game *game;

public:
  Engine(Game *g);
  ~Engine();
  void run();
};

#endif