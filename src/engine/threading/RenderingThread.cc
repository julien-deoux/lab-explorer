#include "RenderingThread.h"
#include "../game/Scene.h"
#include <GLFW/glfw3.h>
#include "RenderingHead.h"

void LEEngine::RenderingThread::callback(MessageBus &messageBus)
{
  Scene *scene;
  GLFWwindow *window;
  renderer = new OpenGLRenderer();

  auto handleMessages = [&]() {
    if (!messageBus.renderingQueue.empty())
    {
      Message<RenderingHead> message = messageBus.renderingQueue.front();
      switch (message.head)
      {
      case R_SET_WINDOW:
        window = (GLFWwindow *)message.data;
        renderer->initWindow(window);
        break;
      case R_SET_SCENE:
        scene = (Scene *)message.data;
        break;
      default:
        break;
      }
      messageBus.renderingQueue.pop();
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
      renderer->render(scene);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete renderer;
}
