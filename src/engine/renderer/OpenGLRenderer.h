#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "../threading/Thread.h"

namespace LEEngine
{

class OpenGLRenderer : public Renderer
{
private:
  unsigned int tileVAO, tileVBO;
  GLFWwindow *window;
  void render(Player player);
  void render(Tile tile);
  void initTileObjects();
  Shader *flatShader;
public:
  OpenGLRenderer(GLFWwindow *win);
  OpenGLRenderer();
  ~OpenGLRenderer();
  void initWindow(GLFWwindow *win);
  void render(Scene *scene);
};

} // namespace LEEngine

#endif
