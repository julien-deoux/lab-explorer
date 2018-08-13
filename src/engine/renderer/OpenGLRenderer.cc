#include <list>
#include "../../glm/gtc/type_ptr.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include <iostream>

#include "OpenGLRenderer.h"
#include "RendererException.h"

void handleResize(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void LEEngine::OpenGLRenderer::initWindow(GLFWwindow *win)
{
  window = win;

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, handleResize);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    throw RendererException("Failed to initialize GLAD");
  }

  int width, height;
  glfwGetWindowSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glEnable(GL_DEPTH_TEST);

  flatShader = new Shader("data/shaders/v_flat.glsl", "data/shaders/f_single_color.glsl");

  initTileObjects();
}

LEEngine::OpenGLRenderer::OpenGLRenderer(GLFWwindow *win)
{
  initWindow(win);
}

LEEngine::OpenGLRenderer::OpenGLRenderer() {}

LEEngine::OpenGLRenderer::~OpenGLRenderer()
{
  delete flatShader;
}

void LEEngine::OpenGLRenderer::initTileObjects()
{
  const float tileVertices[18] = {
      0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f};
  glGenVertexArrays(1, &tileVAO);
  glGenBuffers(1, &tileVBO);

  glBindBuffer(GL_ARRAY_BUFFER, tileVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tileVertices), tileVertices, GL_STATIC_DRAW);

  glBindVertexArray(tileVAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

void LEEngine::OpenGLRenderer::render(Scene *scene)
{
  glClearColor(0.05f, 0.08f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  flatShader->use();

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(-8.0f, -8.0f, -2.0f));
  flatShader->setMat4("view", view);

  float viewportDimensions[4];
  glGetFloatv(GL_VIEWPORT, viewportDimensions);
  float tileSize = 32.0f;
  float height = viewportDimensions[3] / tileSize;
  float width = viewportDimensions[2] / tileSize;
  glm::mat4 projection = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, 1.0f, 5.0f);
  flatShader->setMat4("projection", projection);

  for (Tile tile : *scene->level->tiles)
  {
    render(tile);
  }

  render(*scene->player);
}

void LEEngine::OpenGLRenderer::render(Player player)
{
  flatShader->setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(player.x, player.y, 1.0f));
  model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
  flatShader->setMat4("model", model);

  glBindVertexArray(tileVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void LEEngine::OpenGLRenderer::render(Tile tile)
{
  float greyShade = tile.type == TERRAIN ? 0.5f : 0.8f;
  flatShader->setVec3("color", glm::vec3(greyShade));

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(tile.x, tile.y, 0.0f));
  flatShader->setMat4("model", model);

  glBindVertexArray(tileVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
