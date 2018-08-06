#include <cstdlib>
#include <thread>
#include <iostream>
#include <chrono>

#include "renderer/OpenGLRenderer.h"
#include "EngineException.h"
#include "Engine.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static void renderLoop(GLFWwindow *window, LEEngine::Renderer *renderer, LEEngine::Scene *scene)
{
  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window))
  {
    renderer->render(scene);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

static void physicsLoop(GLFWwindow *window, LEEngine::Simulation *simulation)
{
  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window))
  {
    int timeStep = simulation->run();
    std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));
  }
}

LEEngine::Engine::Engine(Game *g)
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
    throw EngineException("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
  renderer = new OpenGLRenderer(window);
}

LEEngine::Engine::~Engine()
{
  glfwTerminate();
}

void LEEngine::Engine::run()
{
  scene = (Scene *)malloc(sizeof(Scene));
  scene->level = (Level *)malloc(sizeof(Level));
  scene->level->tiles = new std::list<Tile>;

  scene->player = (Player *)malloc(sizeof(Player));
  *scene->player = {4, 6};

  for (int i = 0; i < 16; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      scene->level->tiles->push_front({(float)i, (float)j, (j < 2 || j > 14 || i < 2 || i > 14) ? TERRAIN : BACKGROUND});
    }
  }

  simulation = new Simulation(scene);

  std::thread renderThread(renderLoop, window, renderer, scene);
  std::thread physicsThread(physicsLoop, window, simulation);

  while (!glfwWindowShouldClose(window))
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  }

  renderThread.join();
  physicsThread.join();

  delete simulation;
  free(scene->level);
  free(scene);
}
