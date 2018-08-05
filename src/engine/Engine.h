#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include "renderer/Renderer.h"
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

public:
  Engine(Game *g);
  ~Engine();
  void run();
};

} // namespace LEEngine

#endif
