#pragma once

#include "ClientBase.hpp"

#include <raknet/RakString.h>

namespace TruckersMP
{
    class Client : public ClientBase
    {
    public:
        Client(uint32_t appId, uint64_t steamId, uint32_t accountId, RakNet::RakString sessionId, uint32_t ticket);
        ~Client();

        void OnConnectionRequestAccepted(RakNet::SystemAddress serverAddress);
        void OnConnectionAttemptFailed(RakNet::SystemAddress serverAddress);
        void OnMessage(RakNet::MessageID packetId, RakNet::BitStream* messageData, RakNet::Packet* packet);
        void SendAuthentication(RakNet::SystemAddress serverAddress);
        void SendPlayerInfo(RakNet::SystemAddress serverAddress, RakNet::RakString playerName, RakNet::RakString playerTag, uint32_t playerTagColor, uint64_t playerSteamId, uint32_t timestamp);
        void SendUnknown(RakNet::SystemAddress serverAddress);
        void SendUpdateSettings(RakNet::SystemAddress serverAddress);
        void SendUnknown4(RakNet::SystemAddress serverAddress);
        void SendChatMessage(RakNet::SystemAddress serverAddress, RakNet::RakString message);
    private:
        uint32_t m_appId;
        uint64_t m_steamId;
        uint32_t m_accountId;
        RakNet::RakString m_sessionId;
        uint32_t m_ticket;
    };
}