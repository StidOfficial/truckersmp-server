#include "Server.hpp"

#include "ChatCommands.hpp"

#include <raknet/BitStream.h>
#include <raknet/StringCompressor.h>
#include <raknet/RakNetTypes.h>

#include <truckersmp/Utils.hpp>
#include <truckersmp/TruckersMP.hpp>

#include <iostream>
#include <algorithm>
#include <cassert>

namespace TruckersMP
{
    Server::Server(unsigned short port)
        : ServerBase(100, port)
    {
        std::cout << "[Server][" << 0 << ":" << port << "] Listen on " << port << std::endl;

        Player* player;

        player = new Player;
        player->id = 170;
        player->accountId = 3203799;
        player->steamId = 76561198274423088;
        player->name = "rahka";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 511;
        player->accountId = 3344367;
        player->steamId = 76561198364062520;
        player->name = "Mathiaaaaas2020";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x02;

        m_players.push_back(player);

        player = new Player;
        player->id = 3085;
        player->accountId = 3375117;
        player->steamId = 76561198047467907;
        player->name = "Sherhan4ik163";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 3087;
        player->accountId = 2982918;
        player->steamId = 76561198989799072;
        player->name = "Kitty Boi";
        player->tag = "ROMANIA";
        player->tagColor = 0xffee00;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 254;
        player->accountId = 3106383;
        player->steamId = 76561198166401531;
        player->name = "Fuemix";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 717;
        player->accountId = 3125202;
        player->steamId = 76561198967396612;
        player->name = "AidenBvL";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 270;
        player->accountId = 2944226;
        player->steamId = 76561198362750154;
        player->name = "Hurican";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 1494;
        player->accountId = 3372548;
        player->steamId = 76561199038946073;
        player->name = "prokalabg";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 446;
        player->accountId = 3365329;
        player->steamId = 76561198283948421;
        player->name = "Refgue";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 1607;
        player->accountId = 1492234;
        player->steamId = 76561198351873853;
        player->name = "SkyroXXXXXX";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 1056;
        player->accountId = 3351452;
        player->steamId = 76561199009004926;
        player->name = "nikita_petrin";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 1767;
        player->accountId = 3370316;
        player->steamId = 76561199043343801;
        player->name = "RounokRaad";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 1838;
        player->accountId = 436023;
        player->steamId = 76561198029875868;
        player->name = "aitor24681";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 400;
        player->accountId = 3191168;
        player->steamId = 76561199014917530;
        player->name = "wotblaszlo";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);

        player = new Player;
        player->id = 2751;
        player->accountId = 2979746;
        player->steamId = 76561198964725171;
        player->name = "mertcan5034";
        player->tag = "";
        player->tagColor = 0xa44f2;
        player->unknown1 = 0x12;

        m_players.push_back(player);
    }

    void Server::OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet)
    {
        switch(packetId)
        {
            case PACKET_SERVER_AUTHENTICATION:
            {
                uint8_t protocolVersion;
                uint32_t appId;
                uint64_t steamId;
                uint32_t accountId;
                RakNet::RakString sessionId;

                bitStream->Read(protocolVersion);
                bitStream->Read(appId);
                bitStream->Read(steamId);
                bitStream->Read(accountId);
                bitStream->ReadCompressed(sessionId);
                // Probably memory addresses
                uint64_t dummy;
                for(int i = 0; i < 20; i++)
                {
                    bitStream->Read(dummy);
                    std::cout << std::hex << dummy << " : " << std::dec << dummy << std::endl;
                }

                std::cout << "App ID : " << std::dec << appId << std::endl;
                std::cout << "Steam ID : " << std::dec << steamId << std::endl;
                std::cout << "Account ID : " << std::dec << accountId << std::endl;
                std::cout << "Session ID : " << std::dec << sessionId << std::endl;

                if(protocolVersion == TRUCKERSMP_PROTOCOL_VERSION)
                {
                    if(TruckersMP::IsSupportedAppId(appId))
                    {
                        // check steamId, accountId and sessionId
                        // if all good but queue ticket set to 0 = Error DLC
                        if(true)
                        {
                            Player* player = new Player();
                            player->clientId = packet->systemAddress;
                            player->accountId = accountId;
                            player->steamId = steamId;

                            AddPlayer(player);

                            AuthenticationAccepted(packet->systemAddress);
                        }
                        else
                            AuthenticationRefused(packet->systemAddress, AuthenticationError::INVALID_SESSION);
                    }
                    else
                        AuthenticationRefused(packet->systemAddress, AuthenticationError::INVALID_CLIENT);
                }
                else
                    AuthenticationRefused(packet->systemAddress, AuthenticationError::INVALID_CLIENT_PROTOCOL);
                break;
            }
            case PACKET_SERVER_GET_PLAYER_INFO:
            {
                RakNet::RakString playerName;
                RakNet::RakString playerTag;
                uint32_t playerTagColor;
                uint64_t playerSteamId;
                uint32_t timestamp;

                bitStream->ReadCompressed(playerName);
                bitStream->ReadCompressed(playerTag);
                bitStream->Read(playerTagColor);
                bitStream->Read(playerSteamId);
                bitStream->Read(timestamp);

                std::cout << "Tag color : " << std::hex << playerTagColor << std::endl;
                std::cout << "Timestamp : " << timestamp << std::endl;

                Player* player = GetPlayer(packet->systemAddress);
                if(player)
                {
                    player->name = playerName;
                    player->tag = playerTag;
                    player->tagColor = playerTagColor;

                    SendPlayerInfo(packet->systemAddress);

                    for(auto &other_player : m_players)
                        if(other_player->id != player->id)
                            SendAddPlayer(packet->systemAddress, other_player);
                }
                break;
            }
            case PACKET_CLIENT_PLAYER_STATUS:
            {
                uint32_t playerId;

                bitStream->Read(playerId);

                Player* player = GetPlayer(playerId);
                if(player)
                    SendPlayerStatus(packet->systemAddress, player);

                break;
            }
            case PACKET_CLIENT_TRUCK_STATUS:
            {
                Player* player = GetPlayer(packet->systemAddress);
                if(!player)
                    return;

                uint32_t playerId;

                bitStream->Read(playerId);

                assert(playerId == 0x0);

                /*Utils::Find(bitStream, -46096.3, true);
                Utils::Find(bitStream, -46096.3f, true);
                Utils::Find(bitStream, 58.0, true);
                Utils::Find(bitStream, 58.0f, true);
                Utils::Find(bitStream, 8221.8, true);
                Utils::Find(bitStream, 8221.8f, true);*/

                uint8_t byte;
                for(int i = 0; i < bitStream->GetNumberOfBytesUsed(); i++)
                    bitStream->Read(byte);
        
                // Skip truck position ...

                /*uint32_t unknown1;
                uint32_t unknown2;
                uint8_t unknown3;
                uint8_t unknown4;
                uint8_t unknown5;
                uint8_t unknown3;

                bitStream->Read(unknown1);
                bitStream->Read(unknown2);
                bitStream->Read(unknown3); // 0xc8
                bitStream->Read(unknown4);*/

                //SendTime(packet->systemAddress);
                //SendPlayerId(packet->systemAddress, 23);
                //SendChatMessage(packet->systemAddress, false, -1, 0xffff0000, "*** Turn on your headlights! If you will not enable them, you will be kicked within 5 seconds! ***");
                //SendChatMessage(packet->systemAddress, false, -1, 0xffff0000, "Please move! If you will not move within next minute you will be automatically kicked!");

                //Kick(packet->systemAddress, "Away from the keyboard");
                //Kick(packet->systemAddress, "Not enabled headlights while driving.");

                for(auto &other_player : m_players)
                        if(other_player->id != player->id)
                            SendPlayerStatus(packet->systemAddress, other_player);
                break;
            }
            case PACKET_SERVER_CHAT_MESSAGE:
            {
                RakNet::RakString playerMessage;
                uint8_t unknown[7];

                bitStream->ReadCompressed(playerMessage);

                Player* player = GetPlayer(packet->systemAddress);
                if(player)
                    if(!ChatCommands::Process(this, packet->systemAddress, playerMessage))
                        SendChatMessage(packet->systemAddress, true, player->id, 0, playerMessage);

                //SendUnknown1(packet->systemAddress);
                break;
            }
            case PACKET_SERVER_UNKNOWN2:
            {
                uint8_t unknown;
                bitStream->Read(unknown);

                std::cout << "[Server] Unknown : " << std::hex << (int)unknown << std::endl;
                break;
            }
            case PACKET_SERVER_UNKNOWN4:
            {
                uint32_t playerId;

                bitStream->Read(playerId);

                std::cout << "[Server] Unknown4" << std::endl;
                break;
            }
            case PACKET_CLIENT_UNKNOWN1:
            {
                //String found at 1199 : <align right=-16>STID 2000</align>|_france
                //DebugPacket(packet);
                //Utils::TryFindString(bitStream);

                std::cout << "[Server] Unknown1" << std::endl;
                break;
            }
            case PACKET_SERVER_PLAYER_FINISH_MISSION:
            {
                std::cout << "[Server] Player finish mission" << std::endl;
                break;
            }
            case PACKET_SERVER_PLAYER_CHANGE_TAG:
            {
                RakNet::RakString newPlayerTag;
                uint32_t newPlayerTagColor;

                bitStream->ReadCompressed(newPlayerTag);
                bitStream->Read(newPlayerTagColor);

                std::cout << "[Server] Player change tag : " << newPlayerTag << " - " << std::hex << newPlayerTagColor << std::endl;

                Player* player = GetPlayer(packet->systemAddress);
                if(player)
                {
                    player->tag = newPlayerTag;
                    player->tagColor = newPlayerTagColor;
                }
                break;
            }
            case PACKET_SERVER_PLAYER_SUBMIT_REPORT:
            {
                uint8_t unknown1;
                uint32_t playerId;
                uint32_t accountId;
                uint16_t unknown11;
                bool reason1;
                bool reason2;
                bool reason3;
                bool reason4;
                bool reason5;
                bool reason_other;
                bool reason_wrong_way_driving;
                bool reason_chat_abuse;
                bool reason_inappropriate_name_avatar_tag;
                bool reason_cb_radio_abuse;
                bool reason_inappropriate_overtaking;
                bool reason_cheating;
                bool reason_reckless_driving;
                bool reason_trolling_griefing;
                bool reason_ramming;
                bool reason_blocking;
                RakNet::RakString unknown4;
                uint32_t unknown5;
                uint32_t numMods;
                uint32_t unknown7;

                RakNet::RakString filePath;
                bool unknown66;
                uint32_t unknown8;
                uint32_t unknown9;
                uint32_t unknown10;
                bool unknown67;

                bitStream->Read(unknown1);
                bitStream->Read(playerId);
                bitStream->Read(accountId);
                bitStream->Read(unknown11);
                bitStream->ReadCompressed(reason1);
                bitStream->ReadCompressed(reason2);
                bitStream->ReadCompressed(reason3);
                bitStream->ReadCompressed(reason4);
                bitStream->ReadCompressed(reason5);
                bitStream->ReadCompressed(reason_other);
                bitStream->ReadCompressed(reason_wrong_way_driving);
                bitStream->ReadCompressed(reason_chat_abuse);
                bitStream->ReadCompressed(reason_inappropriate_name_avatar_tag);
                bitStream->ReadCompressed(reason_cb_radio_abuse);
                bitStream->ReadCompressed(reason_inappropriate_overtaking);
                bitStream->ReadCompressed(reason_cheating);
                bitStream->ReadCompressed(reason_reckless_driving);
                bitStream->ReadCompressed(reason_trolling_griefing);
                bitStream->ReadCompressed(reason_ramming);
                bitStream->ReadCompressed(reason_blocking);
                bitStream->ReadCompressed(unknown4);
                bitStream->Read(unknown5);
                bitStream->Read(numMods);
                bitStream->Read(unknown7);

                for(uint32_t i = 0; i < numMods; i++)
                {
                    bitStream->ReadCompressed(filePath);
                    bitStream->ReadCompressed(unknown66);
                    bitStream->ReadCompressed(unknown67);
                    bitStream->Read(unknown8);
                    bitStream->Read(unknown9);
                    bitStream->Read(unknown10);

                    std::cout << filePath << std::endl;
                    std::cout << unknown66 << std::endl;
                    std::cout << unknown8 << std::endl;
                    std::cout << unknown9 << std::endl;
                    std::cout << unknown10 << std::endl;
                    std::cout << unknown67 << std::endl;
                    std::cout << "---" << std::endl;
                }

                assert(unknown1 == 0x6);
                assert(unknown11 == 0x0);
                assert(unknown5 == 0x0);
                assert(unknown7 == 0x18);

                std::cout << "Report : " << std::dec << playerId << std::endl;
                std::cout << "Player ID : " << std::dec << (int)accountId << std::endl;

                //Utils::TryFindString(bitStream);
                Utils::PrintLeftDataPacket(bitStream);

                std::cout << "[Server] Player report" << std::endl;
                break;
            }
            case PACKET_SERVER_PLAYER_UPDATE_SETTINGS:
            {
                uint8_t unknown5;
                bitStream->Read(unknown5); // 64 = quit game, 40 = ???

                std::cout << "[Server] Update settings : " << (int)unknown5 << std::endl;
                break;
            }
            case PACKET_SERVER_PLAYER_TOLL_GATE:
            {
                std::cout << "[Server] Toll gate : " << std::endl;

                /*uint8_t unknown;
                uint16_t unknown1;
                uint8_t unknown2;
                uint16_t unknown3;
                uint8_t unknown4;

                bitStream->Read(unknown);
                bitStream->Read(unknown1);
                bitStream->Read(unknown2);
                bitStream->Read(unknown3);
                bitStream->Read(unknown4);

                std::cout << "unknown:" << std::dec << (int)unknown << ",unknown1:" << std::dec << (int)unknown1 << ",unknown2:" << std::dec << (int)unknown2 << ",unknown3:" << std::dec << (int)unknown3 << ",unknown4:" << std::dec << (int)unknown4 << std::endl;*/

                SendTollGate(packet->systemAddress); // Find the official packet id
                break;
            }
            case PACKET_SERVER_PLAYER_TALK:
            {
                uint8_t byte;
                for(int i = 0; i < bitStream->GetNumberOfBytesUsed(); i++)
                    bitStream->Read(byte);

                // Skip voice data
                break;
            }
            case PACKET_SERVER_PLAYER_TRUCK_UNSPAWN:
            {
                std::cout << "[Server] Truck unspawn" << std::endl;
                break;
            }
            case PACKET_SERVER_PLAYER_TRAILER_DETACH:
            {
                std::cout << "[Server] Trailer detach" << std::endl;

                // String found at 477 : CT-124-CJ.<offset hshift=5 vshift=-5><img src=/material/ui/lp/france/18.mat color=FFFFFFFF width=16 height=34>|france

                bool unknown;
                RakNet::RakString unknown1;

                unknown = bitStream->ReadBit();

                std::cout << unknown << std::endl;
                break;
            }
            default:
            {
                std::cerr << "[Server] Unknown packet id : " << std::hex << (int)packetId << " " << std::endl;
                Utils::PrintLeftDataPacket(bitStream);
                break;
            }
        }
    }

    void Server::OnDisconnect(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID)
    {
        std::cout << "[Server] Client " << clientAddress.ToString() << " disconnect" << std::endl;

        RemovePlayer(clientAddress);
    }

    void Server::OnConnectionLost(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID)
    {
        std::cout << "[Server] Client " << clientAddress.ToString() << " connection lost" << std::endl;

        RemovePlayer(clientAddress);
    }

    uint32_t Server::GeneratePlayerId()
    {
        uint32_t lastId = 0;
        for(auto &player : m_players)
            if(lastId + 1 == player->id)
                break;
            else
                lastId = player->id;

        return lastId + 1;
    }

    uint32_t Server::AddPlayer(Player* player)
    {
        player->id = GeneratePlayerId();

        m_players.push_back(player);

        return player->id;
    }

    Player* Server::GetPlayer(uint32_t id)
    {
        for(auto &player : m_players)
            if(player->id == id)
                return player;

        return nullptr;
    }

    Player* Server::GetPlayer(RakNet::AddressOrGUID clientId)
    {
        for(auto &player : m_players)
            if(player->clientId == clientId)
                return player;

        return nullptr;
    }

    bool Server::RemovePlayer(uint32_t id)
    {
        Player* player = GetPlayer(id);

        return RemovePlayer(player);
    }

    bool Server::RemovePlayer(RakNet::AddressOrGUID clientId)
    {
        Player* player = GetPlayer(clientId);

        return RemovePlayer(player);
    }

    bool Server::RemovePlayer(Player* player)
    {
        if(!player)
            return false;

        std::remove(m_players.begin(), m_players.end(), player);
        delete player;

        return true;
    }

    std::vector<Player*> Server::GetPlayers()
    {
        return m_players;
    }

    uint32_t Server::GetCurrentPlayers()
    {
        return m_players.size();
    }

    uint32_t Server::GetMaximumPlayers()
    {
        return m_server->GetMaximumNumberOfPeers();
    }

    RakNet::RakString Server::GetName()
    {
        return "ETS2 Server";
    }

    void Server::AuthenticationAccepted(RakNet::SystemAddress clientId)
    {
        RakNet::BitStream authenticationAccepted;
        authenticationAccepted.Write((uint8_t)0);
        authenticationAccepted.Write((uint8_t)0);

        SendMessage(PACKET_SERVER_AUTHENTICATION_ACCEPTED, &authenticationAccepted, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::AuthenticationRefused(RakNet::SystemAddress clientId, AuthenticationError error)
    {
        RakNet::BitStream authenticationRefused;

        authenticationRefused.WriteCasted<uint8_t>(error);
        authenticationRefused.Write((uint8_t)0);

        SendMessage(PACKET_SERVER_AUTHENTICATION_REFUSED, &authenticationRefused, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);

        m_server->CloseConnection(clientId, true);
    }

    void Server::SendPlayerInfo(RakNet::SystemAddress clientId)
    {
        Player* player = GetPlayer(clientId);
        if(!player)
            return;

        RakNet::BitStream playerInfo;

        playerInfo.Write(player->id);
        playerInfo.Write(player->accountId);
        playerInfo.WriteCompressed(player->name);
        playerInfo.Write((uint32_t)0x00e4f854); // ???
        playerInfo.Write((uint32_t)0x00ffc000); // ???
        playerInfo.Write((uint32_t)0x0048a700); // ???
        playerInfo.Write((uint32_t)0x10000000); // ???
        playerInfo.Write((uint8_t)0x32); // ???
        playerInfo.WriteCompressed(false); // ???
        playerInfo.WriteCompressed(true); // ???
        playerInfo.WriteCompressed(true); // ???
        playerInfo.WriteCompressed(false); // ???
        playerInfo.WriteCompressed((RakNet::RakString)"Player");
        playerInfo.WriteCompressed((RakNet::RakString)""); // ???
        playerInfo.Write((uint32_t)0xffffffff); // ???

        SendMessage(PACKET_SERVER_PLAYER_INFO, &playerInfo, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::SendChatMessage(RakNet::SystemAddress clientId, bool isPlayer, uint32_t playerId, uint32_t color, RakNet::RakString message)
    {
        RakNet::BitStream chatMessage;

        chatMessage.WriteCompressed(isPlayer);
        if(isPlayer)
        {
            chatMessage.WriteCompressed(false);
            chatMessage.Write(playerId);
            chatMessage.WriteCompressed(false);
            chatMessage.WriteCompressed(false);
            chatMessage.WriteCompressed(message);
        }
        else
        {
            chatMessage.Write(color);
            chatMessage.WriteCompressed(message);
        }

        SendMessage(PACKET_SERVER_CHAT_MESSAGE, &chatMessage, HIGH_PRIORITY, RELIABLE_ORDERED);
    }

    void Server::Kick(RakNet::SystemAddress clientId, RakNet::RakString message)
    {
        RakNet::BitStream kick;

        bool unknown;
        kick.WriteCompressed(unknown);
        kick.WriteCompressed(message);

        SendMessage(PACKET_SERVER_KICK_PLAYER, &kick, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::SendUnknown1(RakNet::SystemAddress clientId)
    {
        RakNet::BitStream unknown1;

        uint8_t data[5] = { 0x00, 0x00, 0x03, 0x24, 0x00 };
        for(int i = 0; i < sizeof(data); i++)
            unknown1.Write(data[i]);

        SendMessage(PACKET_SERVER_UNKNOWN3, &unknown1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::SendAddPlayer(RakNet::SystemAddress clientId, Player* player)
    {
        RakNet::BitStream addPlayer;

        addPlayer.WriteCompressed(false);
        addPlayer.Write(player->id);
        addPlayer.WriteCompressed(player->name);
        addPlayer.WriteCompressed(player->tag);
        addPlayer.Write(player->tagColor);
        addPlayer.WriteCompressed((RakNet::RakString)"Player");
        addPlayer.Write((uint32_t)0xffffffff); // ???
        addPlayer.Write(player->steamId);
        addPlayer.Write(player->accountId);
        addPlayer.Write(player->unknown1); // (binary less than 8 bits) ???

        SendMessage(PACKET_SERVER_ADD_PLAYER, &addPlayer, HIGH_PRIORITY, RELIABLE_ORDERED, 1, clientId, false);

        /*RakNet::BitStream teste2;

        uint8_t test2[] = { 0x00, 0x00, 0x00, 0xab, 0x80, 0x00, 0x00, 0x10, 0x1c, 0x8a, 0xf0, 0x9a, 0xa2, 0xa8, 0xea, 0xea, 0xfc, 0x00, 0x02, 0x91, 0x3c, 0x80, 0x00, 0x00, 0x05, 0x13, 0xb2, 0x4d, 0x58, 0xca, 0xbf, 0xff, 0xff, 0xff, 0xe0, 0x22, 0x00, 0x00, 0x23, 0x52, 0x97, 0x63, 0x40, 0x03, 0x16, 0xb4, 0xe2, 0x60, 0x03, 0x28, 0x80, 0x00, 0x00, 0x0f, 0x22, 0x00, 0x00, 0x57, 0x7e, 0x88, 0x00, 0x01, 0x5d, 0xda, 0x20, 0x00, 0x05, 0xb8, 0x5b, 0x00, 0x00, 0x16, 0xe1, 0x2c, 0x00, 0x00, 0x5b, 0x82, 0x88, 0x00, 0x01, 0x5e, 0x2e, 0x60, 0x00, 0x00, 0x1a, 0x98, 0x3f, 0xdf, 0xef, 0xf9, 0x80, 0x00, 0x00, 0x6a, 0x64, 0xff, 0x7f, 0xbf, 0xe6, 0x00, 0x00, 0x01, 0xfc, 0x83, 0xfd, 0xfe, 0xff, 0x98, 0x00, 0x00, 0x07, 0xf2, 0x4f, 0xf7, 0xfb, 0xfe, 0xa0, 0x00, 0x05, 0x70, 0xb8, 0x42, 0xa0, 0x00, 0x05, 0x6a, 0xb8, 0x42, 0xa0, 0x00, 0x05, 0x6b, 0x08, 0x42, 0xa0, 0x00, 0x05, 0x68, 0xb8, 0x42, 0xa0, 0x00, 0x05, 0x6c, 0x88, 0x42, 0xa0, 0x00, 0x05, 0x6d, 0xf8, 0x42, 0xa0, 0x00, 0x05, 0x44, 0x18, 0x42, 0xa0, 0x00, 0x05, 0x6c, 0x28, 0x42, 0xa0, 0x00, 0x05, 0x44, 0xc8, 0x42, 0x60, 0x00, 0x00, 0x1c, 0x18, 0x3f, 0xdf, 0xef, 0xf9, 0x80, 0x00, 0x00, 0x61, 0x20, 0xff, 0x7f, 0xbf, 0xe6, 0x00, 0x00, 0x01, 0xc1, 0x93, 0xfd, 0xfe, 0xff, 0x98, 0x00, 0x00, 0x06, 0x12, 0x54, 0x7f, 0xc2, 0x60, 0x00, 0x00, 0x21, 0x19, 0x3f, 0xdf, 0xef, 0xf9, 0x80, 0x00, 0x00, 0x7b, 0xe4, 0xff, 0x7f, 0xbf, 0xe6, 0x00, 0x00, 0x02, 0x11, 0x83, 0xfd, 0xfe, 0xff, 0x98, 0x00, 0x00, 0x07, 0xbe, 0x0f, 0xf8, 0x42, 0x60, 0x00, 0x00, 0x20, 0x38, 0x42, 0x10, 0x98, 0x00, 0x00, 0x08, 0x0e, 0x50, 0x84, 0x26, 0x00, 0x00, 0x01, 0xae, 0x94, 0x21, 0x09, 0x80, 0x00, 0x00, 0x6b, 0xa1, 0x08, 0x42, 0xa0, 0x00, 0x05, 0x44, 0x58, 0x42, 0x40, 0x00, 0x05, 0x45, 0x60, 0x00, 0x00, 0x02, 0x01, 0x9c, 0xc0, 0xcf, 0xa9, 0x56, 0x56, 0x8c, 0x64, 0x80, 0x00, 0x0a, 0x86, 0x20, 0x00, 0x00, 0x04, 0x09, 0xda, 0x61, 0x56, 0xea, 0xb2, 0xbc, 0xbe, 0xea, 0x80, 0x00, 0x15, 0xbd, 0x27, 0x49, 0xd6, 0x64, 0xa2, 0x31, 0x1a, 0xa0, 0x00, 0x05, 0x43, 0xe8, 0x42, 0xa0, 0x00, 0x05, 0x71, 0x58, 0x42, 0xa0, 0x00, 0x05, 0x73, 0xc8, 0x42, 0xa0, 0x00, 0x05, 0x75, 0xb8, 0x42, 0x20, 0x00, 0x05, 0x78, 0xaa, 0x80, 0x00, 0x15, 0xdc, 0xe1, 0x0a, 0x80, 0x00, 0x15, 0xb5, 0xef, 0x08, 0xca, 0x74, 0xbe, 0x2e, 0x6c, 0x36, 0x1b, 0x0d, 0x86, 0xc3, 0x29, 0x96, 0xa0, 0x00, 0x05, 0x41, 0xe8, 0x42, 0xa0, 0x00, 0x05, 0x42, 0x4a, 0xd2, 0x50, 0x8c, 0xea, 0x71, 0x38, 0x9c, 0x4e, 0x27, 0x1a, 0x80, 0x00, 0x15, 0xa7, 0x75, 0x8c, 0xc2, 0x32, 0x9d, 0x2b, 0x6b, 0xe8, 0xdc, 0x6e, 0x37, 0x1b, 0x8d, 0xc6, 0xe3, 0x71, 0xb8, 0xdc, 0x6e, 0xa8, 0x00, 0x01, 0x5d, 0x92, 0x10, 0x88, 0x00, 0x01, 0x5e, 0x36, 0xa0, 0x00, 0x05, 0x6f, 0xe8, 0x42, 0x80, 0x00, 0x05, 0x8b, 0x7a, 0x00, 0x20, 0x22, 0x92, 0x92, 0x9e, 0x0e, 0x0e, 0x00, 0x0f, 0xf0, 0x0f, 0xf0, 0x00, 0x00, 0x20, 0x40, 0x9f, 0xf0, 0x00, 0x00, 0x00, 0x22, 0x27, 0x6a, 0xad, 0xdf, 0x2f, 0xd5, 0x7e, 0xa2, 0x9d, 0x95, 0x0f, 0xfc, 0xe9, 0x84, 0xb6, 0x95, 0x6a, 0xf8, 0xe6, 0x7e, 0x88, 0x08, 0x4d, 0x05, 0x2b, 0x28, 0xc0, 0xcb, 0xce, 0xd3, 0xd1, 0xe3, 0x14, 0xbb, 0x88, 0xb4, 0x12, 0x13, 0xf7, 0xfc, 0xf1, 0xab, 0x99, 0x71, 0xeb, 0xf9, 0xd5, 0x72, 0x69, 0x6d, 0xd8, 0x1e, 0x3d, 0x01, 0xd8, 0x3a, 0xd6, 0xe4, 0x00, 0x01, 0x00, 0x7e, 0xfe, 0x00 };
        for(int i = 0; i < sizeof(test2); i++)
            teste2.Write(test2[i]);

        SendMessage(PACKET_SERVER_ADD_PLAYER, &teste2, HIGH_PRIORITY, RELIABLE_ORDERED, 1, clientId, false);*/
    }

    void Server::SendPlayerStatus(RakNet::SystemAddress clientId, Player* player)
    {
        RakNet::BitStream playerStatus;

        playerStatus.Write(player->id);
        playerStatus.WriteCasted<uint16_t>(m_server->GetLastPing(player->clientId));
        playerStatus.Write((uint32_t)0x00000000);
        playerStatus.Write((uint32_t)0x4cc5ce42);
        playerStatus.Write((uint32_t)0xcb5f8200);
        /*playerStatus.Write((uint32_t)0xd8f95d7c);
        playerStatus.Write((uint32_t)0xc84cff80);
        playerStatus.Write((uint32_t)0x1e39a0b5);
        playerStatus.Write((uint32_t)0xca13415d);
        playerStatus.Write((uint32_t)0xba303be3);
        playerStatus.Write((uint32_t)0x1efb4e0f);
        playerStatus.Write((uint32_t)0x1ee88db1);
        playerStatus.Write((uint32_t)0x50fda488);
        playerStatus.Write((uint32_t)0xdee9a757);
        playerStatus.Write((uint32_t)0xe27f2a6e);
        playerStatus.Write((uint32_t)0x8973ab82);
        playerStatus.Write((uint32_t)0x447ed1b7);
        playerStatus.Write((uint16_t)0x70c8);
        playerStatus.Write((uint8_t)0x20);*/

        SendMessage(PACKET_SERVER_PLAYER_STATUS, &playerStatus, HIGH_PRIORITY, RELIABLE_SEQUENCED, 2, clientId, false);
    }

    void Server::SendPlayerId(RakNet::SystemAddress clientId, uint32_t playerId)
    {
        RakNet::BitStream message;

        message.Write(playerId);
        message.Write((uint8_t)0);

        SendMessage(PACKET_SERVER_PLAYER_ID, &message, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::SendTime(RakNet::SystemAddress clientId)
    {
        RakNet::BitStream time;

        uint8_t data[] = { 0x00, 0xe4, 0xf8, 0x55, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x48, 0xa7, 0x00, 0x15, 0x00 };
        //uint8_t data[] = { 0x00, 0xe4, 0xf8, 0x56, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x48, 0xa7, 0x01, 0x55, 0x00 };
        //uint8_t data[] = { 0x00, 0xe4, 0xf8, 0x57, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x48, 0xa7, 0x02, 0x95, 0x00 };
        //uint8_t data[] = { 0x00, 0xe4, 0xf8, 0x58, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x48, 0xa7, 0x03, 0xd3, 0x00 };
        for(int i = 0; i < sizeof(data); i++)
            time.Write(data[i]);

        SendMessage(PACKET_SERVER_TIME, &time, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::SendTollGate(RakNet::SystemAddress clientId)
    {
        RakNet::BitStream tollGate;

        uint8_t data[] = { 0x5, 0xfb, 0xf6, 0x4, 0xa8, 0x51, 0x0, 0x1, 0xc7, 0x2, 0x42, 0x2, 0x42, 0x15, 0xf0, 0x0, 0x45, 0xa6, 0x5d, 0x9 };
        for(int i = 0; i < sizeof(data); i++)
            tollGate.Write(data[i]);

        uint8_t test = 0;
        tollGate.WriteBits(&test, 1);

        // Not the valid packet id
        //SendMessage(PACKET_SERVER_PLAYER_TOLL_GATE, &tollGate, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::SendCurrentTime(RakNet::SystemAddress clientId)
    {
        RakNet::BitStream currentTime;

        // 2020-07-29 20:21:43 (UTC)
        // 2020-07-29 20:21:43 (Central Europe Daylight)

        currentTime.Write((uint8_t)0x00); // ???
        currentTime.Write((uint8_t)43); // Seconds
        currentTime.Write((uint8_t)21); // Minutes
        currentTime.Write((uint8_t)20); // Hours
        currentTime.Write((uint8_t)29); // Days
        currentTime.Write((uint8_t)06); // Mounth - 1
        currentTime.Write((uint32_t)120); // Years (2020 - 120)

        SendMessage(PACKET_SERVER_CURRENT_TIME, &currentTime, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void Server::SendFixTruck(RakNet::SystemAddress clientId)
    {
        RakNet::BitStream fixTruck;

        fixTruck.WriteCompressed(true);

        SendMessage(PACKET_SERVER_FIX_TRUCK, &fixTruck, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    Server::~Server()
    {
    }
}