#include "CommandHandeler.h"
#include <string>
#include <iostream>
#include <cstdio>

CommandHandeler::CommandHandeler()
{
    timer = NULL;
}

CommandHandeler::~CommandHandeler()
{
}
void CommandHandeler::HandleCommand(std::string command)
{
    if (timer != NULL)
    {
        std::cout << "CommandHandeler::HandleCommand input: " << command << std::endl
                  << "Of length: " << command.length() << std::endl;
        if (command.find("pause") != std::string::npos)
            timer->Pause();
        else if (command.find("start") != std::string::npos)
            timer->Start();
        else if (command.find("settime") != std::string::npos)
        {
            int h, m, s;
            std::string time = command.erase(0, 7);
            std::cout << "Time: " << time;
            if (std::sscanf(time.c_str(), "%d:%d:%d", &h, &m, &s) == 3)
            {
                int seconds = h * 3600 + m * 60 + s;
                timer->SetTime(seconds);
            }
            else if (std::sscanf(time.c_str(), "%d:%d", &m, &s) == 2)
            {
                int seconds = m * 60 + s;
                timer->SetTime(seconds);
            }
            else if (std::sscanf(time.c_str(), "%d", &s) == 1)
            {
                timer->SetTime(s);
            }
            else
                timer->SetTime(0);
        }
    }
    else
        std::cout << "Error: Target timer for commandHandeler not set" << std::endl;
}

void CommandHandeler::SetTimer(Timer *t)
{
    timer = t;
}