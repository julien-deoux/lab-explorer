#include "DynamicBody.h"
#include <algorithm>

#define EPSILON 0.001f

bool willCollide(float pos, float displacement, float border)
{
  return (pos <= border + EPSILON && pos + displacement >= border - EPSILON) ||
  (pos >= border - EPSILON && pos + displacement <= border + EPSILON);
}

bool overlap(float start, float width, float min, float range)
{
  return !(start >= min + range || start + width <= min);
}

LEEngine::DynamicBody::DynamicBody(float x, float y, float w, float h, float m)
{
  body = {x, y, w, h};
  onGround = false;
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

void LEEngine::DynamicBody::collide(PhysicalBody staticBody, float timeStep)
{
  if (overlap(body.x, body.w, staticBody.x, staticBody.w))
  {
    if (std::abs(staticBody.y + staticBody.h - body.y) <= EPSILON)
    {
      onGround = true;
      applyForce(-staticBody.friction*dx, 0.0f);
    }
    if (willCollide(body.y, dy * timeStep, staticBody.y + staticBody.h))
    {
      body.y = staticBody.y + staticBody.h;
      dy = std::max(dy, 0.0f);
      cancelForces(DOWN);
    }
    if (willCollide(body.y + body.h, dy * timeStep, staticBody.y))
    {
      body.y = staticBody.y - body.h;
      dy = std::min(dy, 0.0f);
      cancelForces(UP);
    }
  }
  if (overlap(body.y, body.h, staticBody.y, staticBody.h))
  {
    if (willCollide(body.x, dx * timeStep, staticBody.x + staticBody.w))
    {
      body.x = staticBody.x + staticBody.w;
      dx = std::max(dx, 0.0f);
      cancelForces(LEFT);
    }
    if (willCollide(body.x + body.w, dx * timeStep, staticBody.x))
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
