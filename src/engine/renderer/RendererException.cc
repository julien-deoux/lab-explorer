#include <cstring>
#include <string>

#include "RendererException.h"

LEEngine::RendererException::RendererException(const char *msg)
{
  message = msg;
}

const char *LEEngine::RendererException::what() const throw()
{
  std::string fullMsg = std::string("Engine exception: ") + message;
  char *result = new char[fullMsg.length() + 1];
  std::strcpy(result, fullMsg.c_str());
  return result;
}
