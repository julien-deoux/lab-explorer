#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>
#include "../game/Scene.h"

namespace LEEngine
{

class Renderer
{
public:
  virtual void render(Scene *s) = 0;
  virtual void initWindow(GLFWwindow *window) = 0;
};

} // namespace LEEngine

#endif
