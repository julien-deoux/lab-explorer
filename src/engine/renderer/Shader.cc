#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

unsigned int LEEngine::Shader::compileShader(const char **source, const GLenum type)
{
  unsigned int result;
  result = glCreateShader(type);
  glShaderSource(result, 1, source, NULL);
  glCompileShader(result);

  int success;
  char infoLog[512];
  glGetShaderiv(result, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(result, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  return result;
}

unsigned int LEEngine::Shader::createShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader)
{
  unsigned int result;
  result = glCreateProgram();
  glAttachShader(result, vertexShader);
  glAttachShader(result, fragmentShader);
  glLinkProgram(result);

  int success;
  char infoLog[512];
  glGetProgramiv(result, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(result, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  return result;
}

std::string LEEngine::Shader::readFile(const char *path)
{
  std::string code;
  std::ifstream file;

  // ensure ifstream objects can throw exceptions:
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    // open files
    file.open(path);

    std::stringstream stream;

    // read file's buffer contents into streams
    stream << file.rdbuf();

    // close file handlers
    file.close();

    // convert stream into string
    code = stream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  return code;
}

LEEngine::Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
  std::string vShaderString = readFile(vertexPath);
  std::string fShaderString = readFile(fragmentPath);
  const char *vShaderCode = vShaderString.c_str();
  const char *fShaderCode = fShaderString.c_str();

  unsigned int vertex, fragment;

  // vertex Shader
  vertex = compileShader(&vShaderCode, GL_VERTEX_SHADER);
  fragment = compileShader(&fShaderCode, GL_FRAGMENT_SHADER);

  ID = createShaderProgram(vertex, fragment);

  // delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void LEEngine::Shader::use()
{
  glUseProgram(ID);
}

void LEEngine::Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void LEEngine::Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void LEEngine::Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void LEEngine::Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void LEEngine::Shader::setVec2(const std::string &name, float x, float y) const
{
  glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void LEEngine::Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void LEEngine::Shader::setVec3(const std::string &name, float x, float y, float z) const
{
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void LEEngine::Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
  glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void LEEngine::Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
  glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void LEEngine::Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
  glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void LEEngine::Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
  glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void LEEngine::Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
