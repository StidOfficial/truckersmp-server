#include "ClientQueue.hpp"
#include "Client.hpp"

#include <truckersmp/TruckersMP.hpp>
#include <truckersmp/Authentication.hpp>

#include <iostream>

// ETS2 Low server
//#define CLIENT_SERVER_IP    "139.99.90.70"
//#define CLIENT_SERVER_PORT  42850

// ETS2 High server
//#define CLIENT_SERVER_IP    "145.239.131.35"
//#define CLIENT_SERVER_PORT  42700

// dev localhost
#define CLIENT_SERVER_IP    "localhost"
#define CLIENT_SERVER_PORT  42700

#define CLIENT_APPID        ETS2_APP_ID
#define CLIENT_STEAMID      0
#define CLIENT_ACCOUNTID    0
#define CLIENT_SESSIONID    ""

int main()
{
#ifndef NDEBUG
    std::cout << "[Client] Build with debug mode" << std::endl;
#endif
    std::cout << "[Client] Initialize" << std::endl;

    TruckersMP::ClientQueue clientQueue = TruckersMP::ClientQueue(CLIENT_APPID, CLIENT_ACCOUNTID);
    clientQueue.Connect(CLIENT_SERVER_IP, CLIENT_SERVER_PORT + 1);
    clientQueue.Listen();

    std::cout << "[Client] Queue ticket : " << clientQueue.GetTicket() << std::endl;

    TruckersMP::Client client = TruckersMP::Client(CLIENT_APPID, CLIENT_STEAMID, CLIENT_ACCOUNTID, CLIENT_SESSIONID, clientQueue.GetTicket());
    client.Connect(CLIENT_SERVER_IP, CLIENT_SERVER_PORT);
    client.Listen();

    return 0;
}