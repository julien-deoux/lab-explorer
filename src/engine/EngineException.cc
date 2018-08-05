#include <cstring>
#include <string>

#include "EngineException.h"

LEEngine::EngineException::EngineException(const char *msg)
{
  message = msg;
}

const char *LEEngine::EngineException::what() const throw()
{
  std::string fullMsg = std::string("Engine exception: ") + message;
  char *result = new char[fullMsg.length() + 1];
  std::strcpy(result, fullMsg.c_str());
  return result;
}
