#include <sstream>
#include "EngineException.h"

EngineException::EngineException(const char *msg)
{
  message = msg;
}

const char *EngineException::what() const throw()
{
  std::stringstream result;
  result << "Engine exception: " << message;
  return result.str().c_str();
}
