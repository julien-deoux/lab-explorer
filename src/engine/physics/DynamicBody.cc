#include "DynamicBody.h"
#include <iostream>
#include <algorithm>

bool inRange(float x, float min, float range)
{
  return x > min && min + range > x;
}

bool overlap(float start, float width, float min, float range)
{
  return !(start > min + range || start + width < min);
}

LEEngine::DynamicBody::DynamicBody(float x, float y, float w, float h, float m)
{
  body = {x, y, w, h};
  mass = m;
  dx = 0.0;
  dy = 0.0;
  ddx = 0.0;
  ddy = 0.0;
}

LEEngine::DynamicBody::~DynamicBody()
{
}

void LEEngine::DynamicBody::applyForce(float x, float y)
{
  forces.push_front({x, y});
}

void LEEngine::DynamicBody::cancelForces(Direction direction)
{
  for (Vector &force : forces)
  {
    switch (direction)
    {
    case UP:
      force.y = std::min(force.y, 0.0f);
      break;
    case DOWN:
      force.y = std::max(force.y, 0.0f);
      break;
    case RIGHT:
      force.x = std::min(force.x, 0.0f);
      break;
    case LEFT:
      force.x = std::max(force.x, 0.0f);
      break;
    default:
      break;
    }
  }
}

void LEEngine::DynamicBody::collide(PhysicalBody staticBody)
{
  if (overlap(body.x, body.w, staticBody.x, staticBody.w))
  {
    if (inRange(body.y, staticBody.y, staticBody.h))
    {
      body.y = staticBody.y + staticBody.h;
      dy = std::max(dy, 0.0f);
      cancelForces(DOWN);
    }
    if (inRange(staticBody.y, body.y, body.h))
    {
      body.y = staticBody.y - body.h;
      dy = std::min(dy, 0.0f);
      cancelForces(UP);
    }
  }
  if (overlap(body.y, body.h, staticBody.y, staticBody.h))
  {
    if (inRange(body.x, staticBody.x, staticBody.w))
    {
      body.x = staticBody.x + staticBody.w;
      dx = std::max(dx, 0.0f);
      cancelForces(LEFT);
    }
    if (inRange(staticBody.x, body.x, body.w))
    {
      body.x = staticBody.x - body.w;
      dx = std::min(dx, 0.0f);
      cancelForces(RIGHT);
    }
  }
}

void LEEngine::DynamicBody::displace(float timeStep)
{
  ddx = 0;
  ddy = 0;
  while (!forces.empty())
  {
    Vector force = forces.front();
    ddx += force.x / mass;
    ddy += force.y / mass;
    forces.pop_front();
  }
  dx += ddx * timeStep;
  dy += ddy * timeStep;
  body.x += dx * timeStep;
  body.y += dy * timeStep;
}
