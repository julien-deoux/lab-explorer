#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "Tile.h"

namespace LEEngine
{

typedef struct
{
  std::list<Tile> *tiles;
} Level;

} // namespace LEEngine

#endif
