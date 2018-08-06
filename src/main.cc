#include <iostream>

#include "glad/glad.h"
#include "engine/Engine.h"

int main(int argc, char const *argv[])
{
  try
  {
    LEEngine::Engine *engine = new LEEngine::Engine();

    engine->run();

    delete engine;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
