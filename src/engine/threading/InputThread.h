#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include "Thread.h"

namespace LEEngine
{

class InputThread : public Thread
{
public:
  void callback(MessageBus &messageBus);
};

} // namespace LEEngine

#endif
