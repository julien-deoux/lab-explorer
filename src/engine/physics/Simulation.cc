#include "Simulation.h"
#include <iostream>

#define GRAVITY 10
#define TIME_STEP 0.001

LEEngine::Simulation::Simulation(Scene *s)
{
  scene = s;
  Player *simplePlayer = scene->player;
  player = new DynamicBody(simplePlayer->x, simplePlayer->y, 1.0f, 1.0f, 50.0f);

  for (Tile tile : *scene->level->tiles)
    if (tile.type == TERRAIN)
    {
      PhysicalBody body = {tile.x, tile.y, 1.0f, 1.0f};
      physicalBodies.push_front(body);
    }
}

LEEngine::Simulation::~Simulation()
{
  delete player;
}

int LEEngine::Simulation::run()
{
  player->applyForce(0, -GRAVITY * player->mass);

  for (PhysicalBody body : physicalBodies)
  {
    player->collide(body);
  }

  player->displace(TIME_STEP);

  scene->player->x = player->body.x;
  scene->player->y = player->body.y;

  return (int)(TIME_STEP * 1000);
}
