#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include "renderer/Renderer.h"
#include "physics/Simulation.h"
#include "game/Game.h"
#include "logic/Scene.h"

namespace LEEngine
{

class Engine
{
private:
  GLFWwindow *window;
  Game *game;
  Scene *scene;
  Renderer *renderer;
  Simulation *simulation;

public:
  Engine(Game *g);
  ~Engine();
  void run();
};

} // namespace LEEngine

#endif
