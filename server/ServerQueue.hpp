#pragma once

#include "ServerBase.hpp"

#include <truckersmp/Packets.hpp>
#include <truckersmp/Authentication.hpp>

namespace TruckersMP
{
    class ServerQueue : public ServerBase
    {
    public:
        ServerQueue(unsigned short port = TRUCKERSMP_DEFAULT_PORT + 1);
        ~ServerQueue();

        void OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet);

        void SendPosition(RakNet::SystemAddress clientId, uint32_t position);
        void SendFinish(RakNet::SystemAddress clientId);
        void SendAuthenticationRefused(RakNet::SystemAddress clientId, AuthenticationError error);
    };
}