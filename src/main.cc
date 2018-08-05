#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/Engine.h"
#include "LabExplorer.h"

int main(int argc, char const *argv[])
{
  try
  {
    LEEngine::Game *labExplorer = new LabExplorer();
    LEEngine::Engine *engine = new LEEngine::Engine(labExplorer);

    engine->run();

    delete engine;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
