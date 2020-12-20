#include "ChatCommands.hpp"

#include <truckersmp/Utils.hpp>

#include <iostream>
#include <algorithm>
#include <functional>
#include <cinttypes>

namespace TruckersMP
{
    std::vector<ChatCommand> ChatCommands::m_commands;

    void ChatCommands::Initialize()
    {
        Register("pm", "", "/pm <id> <message> - private message to player with <id>", PM);
        Register("blockpm", "", "/blockpm - blocks/unblocks private messages", BlockPM);
        Register("reply", "r", "/(r)eply <message> - reply to the last private message", Reply);
        Register("channel", "", "/channel <id> - 0 => disabled, <1, x> => channels.", Channel);
        Register("pinfo", "", "/pinfo <id> - show information about player with <id>", PlayerInfo);
        Register("time", "", "/time - show current server time (UTC)", Time);
        Register("cest-time", "", "/cest-time current server time (CEST)", Time);
        Register("players", "", "/(p)layers - show count of players on the server", Players);
        Register("server", "", "/server - display information about the current server", ServerInfo);
        Register("fix", "", "/fix - fix your own vehicle", Fix);
        Register("search", "", "/search <name> - find players by <name>", Search);
        Register("searchtag", "st", "/(s)earch(t)ag <tag> - find players by <tag>", SearchTag);
        Register("help", "h", "/(h)elp - display this help", Help);
        Register("toggle-group", "", "/toggle-group - toggle your current group (the color and the name of your group)", ToggleGroup);
        Register("tfm-dj", "", "/tfm-dj - get the current presenter/DJ on TruckersFM", TFMDJ);
        Register("tfm-request", "", "/tfm-request <message> - send a song request to TruckersFM", TFMRequest);
        Register("tfm-shoutout", "", "/tfm-shoutout <message> - send a shoutout message to TruckersFM", TFMShoutout);
        Register("tfm-traffic", "", "/tfm-traffic <message> - let the DJ on TruckersMP known of any traffic in your area", TFMTraffic);
        Register("tfm-currentsong", "", "/tfm-currentsong - check the current song that is being played on TruckersFM", TFMCurrentSong);
        Register("tfm-lastsong", "", "/tfm-lastsong - check the last song that was played on TruckersFM", TFMLastSong);
    }

    bool ChatCommands::Process(Server* server, RakNet::SystemAddress clientId, RakNet::RakString message)
    {
        if(message.Find("/") == 0)
        {
            size_t separatorPos = message.Find(" ");
            RakNet::RakString command;
            RakNet::RakString commandArgs;

            if(separatorPos == -1)
            {
                command = message.SubStr(1, message.GetLength() - 1);
                commandArgs = "";
            }
            else
            {
                command = message.SubStr(1, separatorPos - 1);
                commandArgs = message.SubStr(separatorPos + 1, message.GetLength() - separatorPos);
            }

            for(auto &chatCommand : m_commands)
                if (command == chatCommand.command || (chatCommand.shortCommand != "" && command == chatCommand.shortCommand))
                {
                    chatCommand.callback(server, clientId, commandArgs);
                    return true;
                }

            server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] Unknown command /" + command + ". Type /help or /h to show commands list.");

            return true;
        }
        else
            return false;
    }

    void ChatCommands::Register(RakNet::RakString command, RakNet::RakString shortCommand, RakNet::RakString description, std::function<void(Server*, RakNet::SystemAddress, RakNet::RakString)> callback)
    {
        ChatCommand chatCommand;
        chatCommand.command = command;
        chatCommand.shortCommand = shortCommand;
        chatCommand.description = description;
        chatCommand.callback = callback;

        m_commands.push_back(chatCommand);
    }

    void ChatCommands::PM(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {

    }

    void ChatCommands::BlockPM(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        server->SendChatMessage(clientId, false, 0, 0xff818180, "[System] You have disabled private messages.");
        server->SendChatMessage(clientId, false, 0, 0xff818180, "[System] You have enabled private messages.");
    }

    void ChatCommands::Reply(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] You haven't received any private message yet.");
    }

    void ChatCommands::Channel(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] CB Radio channel changed");
        //server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] Usage: /channel 19");
    }

    void ChatCommands::PlayerInfo(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        uint32_t playerId = std::atoi(args.C_String());
        if(playerId < 0)
        {
            server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] Usage: /pinfo 101");
            return;
        }

        Player* player = server->GetPlayer(playerId);
        if(player)
            server->SendChatMessage(clientId, false, 0, 0xffffffff, Utils::Format("[System] Player: %s (%d) Tag: %s SteamId64: %" PRIu64 " TruckersMPID: %d", player->name.C_String(), player->id, player->tag.C_String(), player->steamId, player->accountId));
        else
            server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] Sorry, but we cannot find that player");
    }

    void ChatCommands::Time(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        server->SendCurrentTime(clientId);
    }

    void ChatCommands::Players(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        RakNet::RakString message;
        message.Set("[System] The are %d players on the server.", server->GetPlayers().size());

        server->SendChatMessage(clientId, false, 0, 0xff0000ff, message);
    }

    void ChatCommands::ServerInfo(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        server->SendChatMessage(clientId, false, 0, 0xff4292ff, Utils::Format("[System] Server information for: %s", server->GetName().C_String()));
        server->SendChatMessage(clientId, false, 0, 0xff4292ff, Utils::Format("> Online players: %d/%d (%d waiting in queue)", server->GetCurrentPlayers(), server->GetMaximumPlayers(), 0));
        server->SendChatMessage(clientId, false, 0, 0xff4292ff, "> AFK kick (10 minutes): enabled");
        server->SendChatMessage(clientId, false, 0, 0xff4292ff, "> Collisions: enabled");
        server->SendChatMessage(clientId, false, 0, 0xff4292ff, "> Cars for players: enabled");
        server->SendChatMessage(clientId, false, 0, 0xff4292ff, "> Police cars for players: disabled");
    }

    void ChatCommands::Fix(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] You do not have attached trailer!");
        server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] You have to wait 536 seconds to use this commands!");
        server->SendChatMessage(clientId, false, 0, 0xff4292ff, "[System] Your vehicle has been fixed.");

        server->SendFixTruck(clientId);
    }

    void ChatCommands::Search(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        if(args.GetLength() < 4)
        {
            server->SendChatMessage(clientId, false, 0, 0xff00ff00, "[System] There should be at least 4 characters.");
            return;
        }

        server->SendChatMessage(clientId, false, 0, 0xff00ff00, "[System] Results for test:");
        server->SendChatMessage(clientId, false, 0, 0xffffffff, "> Nickname: Stid Id: 6 TruckersMPID: 10");
        server->SendChatMessage(clientId, false, 0, 0xff00ff00, "[System] Found 1 results.");
    }

    void ChatCommands::SearchTag(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        if(args.GetLength() < 3)
        {
            server->SendChatMessage(clientId, false, 0, 0xff00ff00, "[System] There should be at least 3 characters.");
            return;
        }

        server->SendChatMessage(clientId, false, 0, 0xff00ff00, "[System] Results for Proton:");
        server->SendChatMessage(clientId, false, 0, 0xffffffff, "> Nickname: Stid Tag: Proton 5.3 ID: 6 TruckersMPID: 10");
        server->SendChatMessage(clientId, false, 0, 0xff00ff00, "[System] Found 1 results.");
    }

    void ChatCommands::Help(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        server->SendChatMessage(clientId, false, 0, 0xff818180, "[System] Avalaible commands:");
        for(auto &command : m_commands)
            server->SendChatMessage(clientId, false, 0, 0xffffffff, "[System] " + command.description);
    }

    void ChatCommands::ToggleGroup(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {
        Player* player = server->GetPlayer(clientId);
        if(player)
        {
            player->groupVisible = !player->groupVisible;

            if(player->groupVisible)
                server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] Your group is now hidden");
            else
                server->SendChatMessage(clientId, false, 0, 0xffff0000, "[System] Your group is now visible");
        }
    }

    void ChatCommands::TFMDJ(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {

    }

    void ChatCommands::TFMRequest(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {

    }

    void ChatCommands::TFMShoutout(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {

    }

    void ChatCommands::TFMTraffic(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {

    }

    void ChatCommands::TFMCurrentSong(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {

    }

    void ChatCommands::TFMLastSong(Server* server, RakNet::SystemAddress clientId, RakNet::RakString args)
    {

    }
}