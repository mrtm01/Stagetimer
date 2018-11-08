#pragma once
#include <SDL2/SDL_net.h>
#include "CommandHandeler.h"

class CommandServer
{
  public:
    CommandServer();
    ~CommandServer();
    void Listen();
    void SetCommandHandeler(CommandHandeler *cs);

    static void ListenStarter(CommandServer *cs);

  private:
    void AcceptConnection(TCPsocket serverSocket);
    void CloseClientSocket(TCPsocket socket);
    void HandleConnection(TCPsocket socket);
    void Shutdown();
    void SetupServerSocket();

    static void ThreadStarter(TCPsocket socket, CommandServer *cs);

    const int maxClients = 1;
    const Uint16 serverPort = 11000;
    const int serverWaitTimeout = 100; //in ms
    TCPsocket communicationSocket;
    SDLNet_SocketSet socketSet;
    IPaddress serverIP;
    bool listening;
    bool busy;
    CommandHandeler *commandHandeler;
    TCPsocket serverSocket;
};