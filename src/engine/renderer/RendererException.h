#ifndef RENDERER_EXCEPTION_H
#define RENDERER_EXCEPTION_H

#include <exception>

namespace LEEngine
{

class RendererException : public std::exception
{
private:
  const char *message;

public:
  RendererException(const char *msg);
  virtual const char *what() const throw();
};

} // namespace LEEngine

#endif
