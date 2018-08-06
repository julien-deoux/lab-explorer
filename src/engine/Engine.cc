#include <cstdlib>
#include <thread>
#include <iostream>
#include <chrono>

#include "renderer/OpenGLRenderer.h"
#include "EngineException.h"
#include "Engine.h"
#include "threading/MessageBus.h"
#include "threading/RenderingThread.h"
#include "threading/PhysicsThread.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

LEEngine::Engine::Engine()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LabExplorer", NULL, NULL);
  if (window == NULL)
  {
    glfwTerminate();
    throw EngineException("Failed to create GLFW window");
  }
}

LEEngine::Engine::~Engine()
{
  glfwTerminate();
}

void LEEngine::Engine::run()
{
  Scene *scene = (Scene *)malloc(sizeof(Scene));
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

  MessageBus messageBus;

  RenderingThread renderingThread;
  PhysicsThread physicsThread;

  std::thread rThread([&]() { renderingThread.callback(messageBus); });
  std::thread pThread([&]() { physicsThread.callback(messageBus); });

  messageBus.physicsQueue.push({P_SET_WINDOW, window});
  messageBus.physicsQueue.push({P_SET_SCENE, scene});
  messageBus.renderingQueue.push({R_SET_WINDOW, window});
  messageBus.renderingQueue.push({R_SET_SCENE, scene});

  while (!glfwWindowShouldClose(window))
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
    if (!messageBus.mainQueue.empty())
    {
      Message<MainHead> message = messageBus.mainQueue.front();
      if (message.head == G_PLAYER_POSITION)
      {
        float *playerPosition = (float *)message.data;
        scene->player->x = playerPosition[0];
        scene->player->y = playerPosition[1];
      }
      messageBus.mainQueue.pop();
    }
  }

  rThread.join();
  pThread.join();

  free(scene->level);
  free(scene);
}
