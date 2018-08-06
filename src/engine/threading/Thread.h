#ifndef THREAD_H
#define THREAD_H

#include "MessageBus.h"

namespace LEEngine
{

class Thread
{
public:
  virtual void callback(MessageBus &messageBus) = 0;
};

} // namespace LEEngine

#endif
