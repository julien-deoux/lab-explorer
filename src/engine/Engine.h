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

public:
  Engine();
  ~Engine();
  void run();
};

} // namespace LEEngine

#endif
