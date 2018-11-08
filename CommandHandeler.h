#pragma once
#include <string>
#include "Timer.h"

class CommandHandeler
{
  public:
    CommandHandeler();
    ~CommandHandeler();
    void SetTimer(Timer *t);
    void HandleCommand(std::string command);

  private:
    Timer *timer;
};