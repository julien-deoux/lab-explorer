#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include "renderer/Renderer.h"
#include "physics/Simulation.h"
#include "game/Scene.h"

namespace LEEngine
{

class Engine
{
private:
  GLFWwindow *window;
  Scene *scene;
  Renderer *renderer;
  Simulation *simulation;

public:
  Engine();
  ~Engine();
  void run();
};

} // namespace LEEngine

#endif
