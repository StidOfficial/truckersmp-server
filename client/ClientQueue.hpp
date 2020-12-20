#pragma once

#include "ClientBase.hpp"

namespace TruckersMP
{
    class ClientQueue : public ClientBase
    {
    public:
        ClientQueue(uint32_t appId, uint32_t accountId);
        ~ClientQueue();

        void OnConnectionRequestAccepted(RakNet::SystemAddress serverAddress);
        void OnConnectionAttemptFailed(RakNet::SystemAddress serverAddress);
        void OnMessage(RakNet::MessageID packetId, RakNet::BitStream* messageData, RakNet::Packet* packet);

        uint32_t GetPosition();
        uint32_t GetTicket();
        void SetAppId(uint32_t appId);
        uint32_t GetAppId();
        void SetAccountId(uint32_t accountId);
        uint32_t GetAccountId();
    private:
        uint32_t m_position;
        uint32_t m_ticket;
        uint32_t m_appId;
        uint32_t m_accountId;
    };
}