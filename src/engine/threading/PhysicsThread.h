#ifndef PHYSICSTHREAD_H
#define PHYSICSTHREAD_H

#include "Thread.h"
#include "../physics/Simulation.h"

namespace LEEngine
{

class PhysicsThread : public Thread
{
private:
  Simulation *simulation;
public:
  void callback(MessageBus &messageBus);
};

} // namespace LEEngine

#endif