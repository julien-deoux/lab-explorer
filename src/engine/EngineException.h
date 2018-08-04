#ifndef ENGINE_EXCEPTION_H
#define ENGINE_EXCEPTION_H

#include <exception>

class EngineException : public std::exception
{
private:
  const char *message;

public:
  EngineException(const char *msg);
  virtual const char *what() const throw();
};

#endif
