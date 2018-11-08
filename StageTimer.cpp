#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <thread>

#include "TimeDisplay.h"
#include "Timer.h"
#include "CommandServer.h"
#include "CommandHandeler.h"

void eventloop(Timer *timer);

int main(int argc, char **argv)
{
    TimeDisplay *timeDisplay = new TimeDisplay();
    Timer *timer = new Timer();
    timer->SetTimeDisplay(timeDisplay);
    CommandServer *commandServer = new CommandServer();
    CommandHandeler *commandHandeler = new CommandHandeler();
    commandHandeler->SetTimer(timer);
    commandServer->SetCommandHandeler(commandHandeler);

    std::thread commandThread(CommandServer::ListenStarter, commandServer);

    commandThread.join();
    delete timeDisplay;
    delete timer;
    delete commandServer;

    return 0;
}