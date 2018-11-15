#include "CommandServer.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_net.h>
#include <thread>
#include "Utility.h"

CommandServer::CommandServer()
{
    socketSet = NULL;
    busy = false;
    if (SDLNet_Init() < 0)
    {
        std::cout << "Network init failed";
        exit(1);
    }
}

CommandServer::~CommandServer()
{
    Shutdown();
}

void CommandServer::SetupServerSocket()
{
    socketSet = SDLNet_AllocSocketSet(maxClients + 1);
    if (socketSet == NULL)
    {
        std::cout << "Could not create socket set: " << SDLNet_GetError();
        exit(1);
    }
    SDLNet_ResolveHost(&serverIP, NULL, serverPort);
    std::cout << "Server IP: " << Utility::IPToString(serverIP.host) << ":" << serverPort << std::endl;
    serverSocket = SDLNet_TCP_Open(&serverIP);
    if (serverSocket == NULL)
    {
        std::cout << "Could not create server socket." << SDLNet_GetError() << std::endl;
        exit(1);
    }
    SDLNet_TCP_AddSocket(socketSet, serverSocket);
}
void CommandServer::Listen()
{
    SetupServerSocket();
    std::cout << "Listening... " << std::endl;

    listening = true;
    while (listening)
    {
        SDLNet_CheckSockets(socketSet, serverWaitTimeout);
        if (SDLNet_SocketReady(serverSocket))
        {
            if (busy)
            {
                std::cout << "Busy!" << std::endl;
                SDLNet_TCP_Close(serverSocket);
                serverSocket = SDLNet_TCP_Open(&serverIP);
            }
            else
            {
                AcceptConnection(serverSocket);
                std::thread connectionThread(CommandServer::ThreadStarter, serverSocket, this);
                connectionThread.detach();
            }
        }
    }
}

void CommandServer::AcceptConnection(TCPsocket serverSocket)
{

    busy = true;
    communicationSocket = SDLNet_TCP_Accept(serverSocket);
    if (!communicationSocket)
    {
        std::cout << "Failed to accept socket: " << SDLNet_GetError() << std::endl;
    }
    else
    {
        IPaddress *remote = SDLNet_TCP_GetPeerAddress(communicationSocket);
        if (!remote)
        {
            std::cout << "Failed to get remote ip" << SDLNet_GetError() << std::endl;
            exit(1);
        }
        else
            std::cout << "Got connection from: " << Utility::IPToString(remote->host) << std::endl;
    }
}

void CommandServer::HandleConnection(TCPsocket socket)
{
    std::string data = "";
    char buffer[1];
    while (SDLNet_TCP_Recv(communicationSocket, &buffer, 1) > 0)
    {
        data += buffer;
        if (buffer[0] == '\n')
            break;
    }
    if (data.find("quit") == 0)
    {
        std::cout << "Got the quit command!" << std::endl;
        listening = false;
    }
    else
        commandHandeler->HandleCommand(data);
}
void CommandServer::CloseClientSocket(TCPsocket socket)
{
    std::cout << "Closing socket and setting busy to false" << std::endl;
    SDLNet_TCP_Close(socket);
    busy = false;
}

void CommandServer::ThreadStarter(TCPsocket socket, CommandServer *cs)
{
    cs->HandleConnection(socket);
    cs->CloseClientSocket(cs->communicationSocket);
}
void CommandServer::ListenStarter(CommandServer *cs)
{
    cs->Listen();
}
void CommandServer::SetCommandHandeler(CommandHandeler *cs)
{
    commandHandeler = cs;
}
void CommandServer::Shutdown()
{
    listening = false;
}