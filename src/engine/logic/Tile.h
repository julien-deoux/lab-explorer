#ifndef TILE_H
#define TILE_H

namespace LEEngine
{

typedef enum {
  TERRAIN, BACKGROUND
} TileType;

typedef struct
{
  int x, y;
  TileType type;
} Tile;

} // namespace LEEngine

#endif
