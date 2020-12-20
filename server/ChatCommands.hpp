#pragma once

#include "Server.hpp"

#include <raknet/RakNetTypes.h>
#include <raknet/RakString.h>

#include <functional>
#include <vector>

namespace TruckersMP
{
    struct ChatCommand
    {
        RakNet::RakString command;
        RakNet::RakString shortCommand;
        RakNet::RakString description;
        std::function<void(Server*, RakNet::SystemAddress, RakNet::RakString)> callback;
    };

    class ChatCommands
    {
    public:
        static void Initialize();
        static bool Process(Server* server, RakNet::SystemAddress clientId, RakNet::RakString message);
        static void Register(RakNet::RakString command, RakNet::RakString shortCommand, RakNet::RakString description, std::function<void(Server*, RakNet::SystemAddress, RakNet::RakString)> callback);

        static void PM(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void BlockPM(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void Reply(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void Channel(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void PlayerInfo(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void Time(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void Players(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void ServerInfo(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void Fix(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void Search(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void SearchTag(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void Help(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void ToggleGroup(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void TFMDJ(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void TFMRequest(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void TFMShoutout(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void TFMTraffic(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void TFMCurrentSong(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
        static void TFMLastSong(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args);
    private:
        static std::vector<ChatCommand> m_commands;
    };
}