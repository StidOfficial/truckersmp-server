#pragma once

#include <truckersmp/TruckersMP.hpp>

#include <raknet/RakPeerInterface.h>

namespace TruckersMP
{
    class ServerBase
    {
    public:
        ServerBase(unsigned int maxPlayers, unsigned short port);
        ~ServerBase();

        void Listen();
        virtual void OnNewIncomingConnection(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID);
        virtual void OnIncompatibleProtocolVersion(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID);
        virtual void OnPing(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID, bool connected);
        virtual void OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet);
        virtual void OnDisconnection(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID);
        virtual void OnConnectionLost(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID);
        void SendMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, PacketPriority priority, PacketReliability reliability,
                            char orderingChannel = 0, const RakNet::AddressOrGUID systemIdentifier = RakNet::UNASSIGNED_SYSTEM_ADDRESS, bool broadcast = true, uint32_t forceReceiptNumber = -1);
    protected:
        RakNet::RakPeerInterface* m_server;
    };
}