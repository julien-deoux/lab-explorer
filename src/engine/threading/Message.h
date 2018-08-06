#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

namespace LEEngine
{

template <typename T>
class Message
{
public:
  T head;
  void *data;
};

} // namespace LEEngine

#endif
