#ifndef RENDERER_H
#define RENDERER_H

#include "../logic/Scene.h"

namespace LEEngine
{

class Renderer
{
public:
  virtual void render(Scene *s) = 0;
};

} // namespace LEEngine

#endif
