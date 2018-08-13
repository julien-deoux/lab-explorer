#include "Simulation.h"

#define GRAVITY 10
#define TIME_STEP 0.001
#define WALK_FORCE 100000.0f
#define JUMP_FORCE 300000.0f

LEEngine::Simulation::Simulation(Scene *s)
{
  scene = s;
  Player *simplePlayer = scene->player;
  player = new DynamicBody(simplePlayer->x, simplePlayer->y, 1.0f, 2.0f, 50.0f);

  for (Tile tile : *scene->level->tiles)
  {
    if (tile.type == TERRAIN)
    {
      PhysicalBody body = {tile.x, tile.y, 1.0f, 1.0f, 70.0f};
      physicalBodies.push_front(body);
    }
  }
}

LEEngine::Simulation::~Simulation()
{
  delete player;
}

int LEEngine::Simulation::run()
{
  player->onGround = false;
  player->applyForce(0, -GRAVITY * player->mass);

  for (PhysicalBody body : physicalBodies)
  {
    player->collide(body, TIME_STEP);
  }

  player->displace(TIME_STEP);

  return (int)(TIME_STEP * 1000);
}

LEEngine::Vector LEEngine::Simulation::getPlayerPosition()
{
  return {player->body.x, player->body.y};
}

void LEEngine::Simulation::walk(Direction direction)
{
  float intensity = direction == RIGHT ? WALK_FORCE : -WALK_FORCE;
  if (player->onGround)
    player->applyForce(intensity, 0.0f);
}

void LEEngine::Simulation::jump()
{
  if (player->onGround)
    player->applyForce(0.0f, JUMP_FORCE);
}
