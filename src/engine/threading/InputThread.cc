#include "InputThread.h"
#include <GLFW/glfw3.h>
#include <thread>

#define INPUT_LATENCY 50

void LEEngine::InputThread::callback(MessageBus &messageBus)
{
  GLFWwindow *window;

  auto handleMessages = [&]() {
    if (!messageBus.inputQueue.empty())
    {
      Message<InputHead> message = messageBus.inputQueue.front();
      switch (message.head)
      {
      case I_SET_WINDOW:
        window = (GLFWwindow *)message.data;
        break;
      default:
        break;
      }
      messageBus.inputQueue.pop();
    }
  };

  auto handleInput = [&]() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      messageBus.physicsQueue.push({P_WALK_LEFT, nullptr});
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      messageBus.physicsQueue.push({P_WALK_RIGHT, nullptr});
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      messageBus.physicsQueue.push({P_JUMP, nullptr});

    std::this_thread::sleep_for(std::chrono::milliseconds(INPUT_LATENCY));
  };

  while (window == nullptr)
  {
    handleMessages();
  }

  while (!glfwWindowShouldClose(window))
  {
    handleMessages();
    handleInput();
  }
}
