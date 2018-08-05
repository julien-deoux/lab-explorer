#ifndef SCENE
#define SCENE

#include "Player.h"
#include "Level.h"

namespace LEEngine
{

typedef struct
{
  Player *player;
  Level *level;
} Scene;

} // namespace LEEngine

#endif
