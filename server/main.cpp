#include "ServerQueue.hpp"
#include "Server.hpp"
#include "ChatCommands.hpp"

#include <thread>
#include <iostream>

void listenServerQueue(TruckersMP::ServerQueue serverQueue)
{
    serverQueue.Listen();
}

void listenServer(TruckersMP::Server server)
{
    server.Listen();
}

int main()
{
    std::cout << "[Server] Initialize" << std::endl;

    TruckersMP::ChatCommands::Initialize();

    TruckersMP::ServerQueue serverQueue = TruckersMP::ServerQueue(TRUCKERSMP_DEFAULT_PORT + 1);
    TruckersMP::Server server = TruckersMP::Server(TRUCKERSMP_DEFAULT_PORT);

    std::thread serverQueueListenThread(listenServerQueue, serverQueue);
    std::thread serverListenThread(listenServer, server);

    serverQueueListenThread.join();
    serverListenThread.join();

    return 0;
}