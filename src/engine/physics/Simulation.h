#ifndef SIMULATION_H
#define SIMULATION_H

#include <Box2D/Box2D.h>
#include <list>
#include "PhysicalBody.h"
#include "DynamicBody.h"
#include "../logic/Scene.h"

namespace LEEngine
{

class Simulation
{
private:
  Scene *scene;
  std::list<PhysicalBody> physicalBodies;
  DynamicBody *player;

public:
  Simulation(Scene *scene);
  ~Simulation();
  int run();
};

} // namespace LEEngine

#endif
