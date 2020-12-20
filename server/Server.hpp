#pragma once

#include "ServerBase.hpp"

#include <truckersmp/Packets.hpp>
#include <truckersmp/Authentication.hpp>
#include <truckersmp/Player.hpp>

#include <raknet/RakString.h>

#include <vector>

namespace TruckersMP
{
    class Server : public ServerBase
    {
    public:
        Server(unsigned short port = TRUCKERSMP_DEFAULT_PORT);
        ~Server();

        void OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet);
        void OnDisconnect(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID);
        void OnConnectionLost(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID);

        uint32_t GeneratePlayerId();
        uint32_t AddPlayer(Player* player);
        Player* GetPlayer(uint32_t id);
        Player* GetPlayer(RakNet::AddressOrGUID clientId);
        bool RemovePlayer(uint32_t id);
        bool RemovePlayer(RakNet::AddressOrGUID clientId);
        bool RemovePlayer(Player* player);
        std::vector<Player*> GetPlayers();
        uint32_t GetCurrentPlayers();
        uint32_t GetMaximumPlayers();
        RakNet::RakString GetName();

        void AuthenticationAccepted(RakNet::SystemAddress clientId);
        void AuthenticationRefused(RakNet::SystemAddress clientId, AuthenticationError error);
        void SendPlayerInfo(RakNet::SystemAddress clientId);
        void SendChatMessage(RakNet::SystemAddress clientId, bool isPlayer, uint32_t playerId, uint32_t color, RakNet::RakString message);
        void Kick(RakNet::SystemAddress clientId, RakNet::RakString message);
        void SendUnknown1(RakNet::SystemAddress clientId);
        void SendAddPlayer(RakNet::SystemAddress clientId, Player* player);
        void SendPlayerStatus(RakNet::SystemAddress clientId, Player* player);
        void SendPlayerId(RakNet::SystemAddress clientId, uint32_t playerId);
        void SendTime(RakNet::SystemAddress clientId);
        void SendTollGate(RakNet::SystemAddress clientId);
        void SendCurrentTime(RakNet::SystemAddress clientId);
        void SendFixTruck(RakNet::SystemAddress clientId);
    private:
        std::vector<Player*> m_players;
    };
}