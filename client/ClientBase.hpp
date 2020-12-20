#pragma once

#include <raknet/RakPeerInterface.h>

namespace TruckersMP
{
    class ClientBase
    {
    public:
        ClientBase();
        ~ClientBase();

        bool Connect(const char ip[64], unsigned short port);
        virtual void OnRemoteNewIncomingConnection(RakNet::SystemAddress serverAddress);
        virtual void OnAlreadyConnected(RakNet::SystemAddress serverAddress);
        virtual void OnIncompatibleProtocolVersion(RakNet::SystemAddress serverAddress);
        virtual void OnDisconnection(RakNet::SystemAddress serverAddress, bool remote);
        virtual void OnConnectionLost(RakNet::SystemAddress serverAddress, bool remote);
        virtual void OnBanned(RakNet::SystemAddress serverAddress);
        virtual void OnConnectionAttemptFailed(RakNet::SystemAddress serverAddress);
        virtual void OnNoFreeIncomingConnections(RakNet::SystemAddress serverAddress);
        virtual void OnInvalidPassword(RakNet::SystemAddress serverAddress);
        virtual void OnConnectionRequestAccepted(RakNet::SystemAddress serverAddress);
        virtual void OnPing(RakNet::SystemAddress serverAddress, bool connected);
        virtual void OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet);
        void SendMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream = nullptr, PacketPriority priority = LOW_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED,
                            char orderingChannel = 0, const RakNet::AddressOrGUID systemIdentifier = RakNet::UNASSIGNED_SYSTEM_ADDRESS, bool broadcast = true, uint32_t forceReceiptNumber = -1);
        void Listen();
    protected:
        RakNet::RakPeerInterface* m_client;
    };
}