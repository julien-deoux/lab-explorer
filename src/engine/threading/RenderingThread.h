#ifndef RENDERERTHREAD_H
#define RENDERERTHREAD_H

#include "Thread.h"
#include "../renderer/OpenGLRenderer.h"

namespace LEEngine
{

class RenderingThread : public Thread
{
private:
  OpenGLRenderer *renderer;
public:
  void callback(MessageBus &messageBus);
};

} // namespace LEEngine

#endif
