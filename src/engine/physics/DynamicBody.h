#ifndef DYNAMICBODY_H
#define DYNAMICBODY_H

#include <list>
#include "PhysicalBody.h"

namespace LEEngine
{

typedef struct {
  float x, y;
} Vector;

typedef enum {
  UP, DOWN, LEFT, RIGHT
} Direction;

class DynamicBody
{
private:
  float dx, dy;
  float ddx, ddy;
  std::list<Vector> forces;
  void cancelForces(Direction direction);
public:
  float mass;
  PhysicalBody body;
  DynamicBody(float x, float y, float w, float h, float m);
  ~DynamicBody();
  void applyForce(float x, float y);
  void displace(float timeStep);
  void collide(PhysicalBody staticBody);
};

} // namespace LEEngine

#endif
