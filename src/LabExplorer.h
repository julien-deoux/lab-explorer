#ifndef LAB_EXPLORER_H
#define LAB_EXPLORER_H

#include "engine/game/Game.h"

class LabExplorer : public LEEngine::Game
{
public:
  const char *getName()
  {
    return "LabExplorer";
  }
};

#endif
