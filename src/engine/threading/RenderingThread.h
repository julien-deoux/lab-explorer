#ifndef RENDERERTHREAD_H
#define RENDERERTHREAD_H

#include "Thread.h"
#include "../renderer/Renderer.h"

namespace LEEngine
{

class RenderingThread : public Thread
{
private:
  Renderer *renderer;
public:
  void callback(MessageBus &messageBus);
};

} // namespace LEEngine

#endif
