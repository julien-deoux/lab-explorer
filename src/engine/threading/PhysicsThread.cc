#include "PhysicsThread.h"
#include <thread>
#include <GLFW/glfw3.h>
#include "../physics/Simulation.h"
#include "../game/Scene.h"

void LEEngine::PhysicsThread::callback(MessageBus &messageBus)
{
  GLFWwindow *window;
  Simulation *simulation;
  Scene *scene;
  float playerPosition[2];

  auto handleMessages = [&]() {
    if (!messageBus.physicsQueue.empty())
    {
      Message<PhysicsHead> message = messageBus.physicsQueue.front();
      switch (message.head)
      {
      case P_SET_WINDOW:
        window = (GLFWwindow *)message.data;
        break;
      case P_WALK_LEFT:
        simulation->walk(LEFT);
        break;
      case P_WALK_RIGHT:
        simulation->walk(RIGHT);
        break;
      case P_JUMP:
        simulation->jump();
        break;
      case P_SET_SCENE:
        if (simulation != nullptr)
          delete simulation;
        scene = (Scene *)message.data;
        simulation = new Simulation(scene);
        break;
      default:
        break;
      }
      messageBus.physicsQueue.pop();
    }
  };

  while (window == nullptr)
  {
    handleMessages();
  }

  while (!glfwWindowShouldClose(window))
  {
    handleMessages();

    if (scene != nullptr)
    {
      int timeStep = simulation->run();
      Vector pos = simulation->getPlayerPosition();
      playerPosition[0] = pos.x;
      playerPosition[1] = pos.y;
      messageBus.mainQueue.push({G_PLAYER_POSITION, (void *)playerPosition});
      std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));
    }
  }

  if (simulation != nullptr)
    delete simulation;
}
