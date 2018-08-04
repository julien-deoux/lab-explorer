#include <GLFW/glfw3.h>

#include "EngineException.h"
#include "game/Game.h"
#include "Engine.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Engine::Engine(Game *g)
{
  game = g;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, game->getName(), NULL, NULL);
  if (window == NULL)
  {
    glfwTerminate();
    throw new EngineException("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
}

Engine::~Engine()
{
  glfwTerminate();
}

void Engine::run() {
  while (!glfwWindowShouldClose(window))
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
