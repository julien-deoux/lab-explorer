#include <iostream>
#include <GLFW/glfw3.h>

#include "engine/Engine.h"
#include "LabExplorer.h"

int main(int argc, char const *argv[])
{
  Game *labExplorer;
  Engine *engine;
  try
  {
    labExplorer = new LabExplorer();
    engine = new Engine(labExplorer);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  engine->run();

  return 0;
}
