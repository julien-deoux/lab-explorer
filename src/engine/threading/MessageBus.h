#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <queue>
#include "Message.h"
#include "PhysicsHead.h"
#include "RenderingHead.h"
#include "InputHead.h"
#include "MainHead.h"

namespace LEEngine
{

typedef struct
{
  std::queue<Message<PhysicsHead>> physicsQueue;
  std::queue<Message<RenderingHead>> renderingQueue;
  std::queue<Message<InputHead>> inputQueue;
  std::queue<Message<MainHead>> mainQueue;
} MessageBus;

} // namespace LEEngine

#endif
