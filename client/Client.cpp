#include "Client.hpp"

#include <truckersmp/Packets.hpp>
#include <truckersmp/Utils.hpp>
#include <truckersmp/TruckersMP.hpp>
#include <truckersmp/Authentication.hpp>
#include <truckersmp/Player.hpp>

#include <iostream>
#include <cassert>

namespace TruckersMP
{
    Client::Client(uint32_t appId, uint64_t steamId, uint32_t accountId, RakNet::RakString sessionId, uint32_t ticket)
        : ClientBase(), m_appId(appId), m_steamId(steamId), m_accountId(accountId), m_sessionId(sessionId), m_ticket(ticket)
    {
    }

    void Client::OnConnectionRequestAccepted(RakNet::SystemAddress serverAddress)
    {
        std::cout << "[Client][" << m_client->GetMyBoundAddress().ToString() << "] Connected !" << std::endl;

        SendAuthentication(serverAddress);
    }

    void Client::OnConnectionAttemptFailed(RakNet::SystemAddress serverAddress)
    {
        std::cerr << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Failed connection" << std::endl;

        m_client->Shutdown(300);
    }

    void Client::OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet)
    {
        switch (packetId)
        {
            case PACKET_SERVER_AUTHENTICATION_ACCEPTED:
            {
                std::cout << "[Client][" << m_client->GetMyBoundAddress().ToString() << "] Authentication accepted !" << std::endl;

                uint8_t unknown1;
                uint8_t unknown2;

                bitStream->Read(unknown1);
                bitStream->Read(unknown2);

                std::cout << "unknown1:" << std::dec << (int)unknown1 << ",unknown2:" << std::dec << (int)unknown2 << std::endl;

                SendPlayerInfo(packet->systemAddress, "Stid", "Proton 5.3", 0xa44f2, m_steamId, 1723007763);
                break;
            }
            case PACKET_SERVER_AUTHENTICATION_REFUSED:
            {
                AuthenticationError error;
                uint8_t unknown1;

                bitStream->ReadCasted<uint8_t>(error);
                bitStream->Read(unknown1);

                std::cout << "[Client][" << m_client->GetMyBoundAddress().ToString() << "] Authentication refused : " << Authentication::GetError(error) << ",unknown1:" << std::dec << (int)unknown1 << std::endl;

                m_client->Shutdown(300);
                break;
            }
            case PACKET_SERVER_PLAYER_INFO:
            {
                Player player;

                uint32_t unknown1;
                uint32_t unknown2;
                uint32_t unknown3;
                uint32_t unknown4;
                uint8_t unknown5;
                bool unknown6;
                bool unknown7;
                bool unknown8;
                bool unknown9;
                RakNet::RakString groupName;
                RakNet::RakString unknown10;
                uint32_t unknown11;

                bitStream->Read(player.id);
                bitStream->Read(player.accountId);
                bitStream->ReadCompressed(player.name);
                bitStream->Read(unknown1);
                bitStream->Read(unknown2);
                bitStream->Read(unknown3);
                bitStream->Read(unknown4);
                bitStream->Read(unknown5);
                bitStream->ReadCompressed(unknown6);
                assert(unknown6 == false);
                bitStream->ReadCompressed(unknown7);
                assert(unknown7 == true);
                bitStream->ReadCompressed(unknown8);
                assert(unknown8 == true);
                bitStream->ReadCompressed(unknown9);
                assert(unknown9 == false);
                bitStream->ReadCompressed(groupName);
                bitStream->ReadCompressed(unknown10);
                bitStream->Read(unknown11);
                assert(unknown11 == 0xffffffff);

                std::cout << "[Client][" << m_client->GetMyBoundAddress().ToString() << "] Player info" << std::endl;

                SendUnknown(packet->systemAddress);
                SendUpdateSettings(packet->systemAddress);
                SendUnknown4(packet->systemAddress);

                SendChatMessage(packet->systemAddress, "test");
                break;
            }
            case PACKET_SERVER_CHAT_MESSAGE:
            {
                bool isPlayer, unknown1;
                uint32_t playerId, color;
                bool unknown2, unknown3;
                RakNet::RakString message;

                bitStream->ReadCompressed(isPlayer);
                if(isPlayer)
                {
                    bitStream->ReadCompressed(unknown1);
                    bitStream->Read(playerId);
                    bitStream->ReadCompressed(unknown2);
                    bitStream->ReadCompressed(unknown3);
                    bitStream->ReadCompressed(message);
                }
                else
                {
                    bitStream->Read(color);
                    bitStream->ReadCompressed(message);
                }

                if(isPlayer)
                    std::cout << "Player (" << playerId << ")(" << unknown1 << ":" << unknown2 << ":" << unknown3 << ") : " << message << std::endl;
                else
                    std::cout << "Server (color:" << color << ") : " << message << std::endl;

                break;
            }
            case PACKET_SERVER_ADD_PLAYER:
            {
                bool unknown1;
                uint32_t playerId;
                RakNet::RakString playerName;
                RakNet::RakString playerTag;
                uint32_t tagColor;
                RakNet::RakString groupName;
                uint32_t unknown3;
                uint64_t steamId;
                uint32_t accountId;
                uint8_t unknown4;

                bitStream->ReadCompressed(unknown1);
                assert(unknown1 == false);
                bitStream->Read(playerId);
                bitStream->ReadCompressed(playerName);
                bitStream->ReadCompressed(playerTag);
                bitStream->Read(tagColor);
                bitStream->ReadCompressed(groupName);
                bitStream->Read(unknown3);
                assert(unknown3 == 0xffffffff);
                bitStream->Read(steamId);
                bitStream->Read(accountId);
                bitStream->Read(unknown4);
                //assert(unknown4 == 0x10);

                std::cout << "Player id: " << std::dec << playerId << std::endl;
                std::cout << "Player name: " << playerName << std::endl;
                std::cout << "Player tag: " << playerTag << std::endl;
                std::cout << "Player tag color: " << std::hex << tagColor << std::endl;
                std::cout << "Player group name: " << groupName << std::endl;
                std::cout << "Player steamid: " << std::dec << steamId << std::endl;
                std::cout << "Player accountid: " << accountId << std::endl;
                std::cout << "unknown4:" << std::hex << (int)unknown4 << std::endl;

                //Utils::TryFindString(bitStream);
                break;
            }
            default:
            {
#ifndef NDEBUG
                std::cerr << "[Client][" << m_client->GetMyBoundAddress().ToString() << "] Unknown packet id : " << std::hex << (int)packetId << std::endl;
#endif
                break;
            }
        }
    }

    void Client::SendAuthentication(RakNet::SystemAddress serverAddress)
    {
        RakNet::BitStream authentication;

        authentication.Write((uint8_t)TRUCKERSMP_PROTOCOL_VERSION);
        authentication.Write(m_appId);
        authentication.Write(m_steamId);
        authentication.Write(m_accountId);
        authentication.WriteCompressed(m_sessionId);
        authentication.Write((uint64_t)0x3e8c747ba42);
        authentication.Write((uint64_t)0xc80000000);
        authentication.Write((uint64_t)0xb56480fcc0000000);
        authentication.Write((uint64_t)0x44d2b1b520000000);
        authentication.Write((uint64_t)0x3d37872b90000000);
        authentication.Write((uint64_t)0x1f1a88cab8000000);
        authentication.Write((uint64_t)0xb92dab864000000);
        authentication.Write((uint64_t)0x49d160eb6000000);
        authentication.Write((uint64_t)0x3d79c95d9000000);
        authentication.Write((uint64_t)0x1584d3748800000);
        authentication.Write((uint64_t)0x9304702400004b);
        authentication.Write((uint64_t)0xfffffffffffdc0dd);
        authentication.Write((uint64_t)0xfffffffffff1489a);
        authentication.Write((uint64_t)0xfffffffffff41d63);
        authentication.Write((uint64_t)0x7ffffffffffffb22);
        authentication.Write((uint64_t)0xbffffffffffe2339);
        authentication.Write((uint64_t)0xdfffffffffff0e47);
        authentication.Write((uint64_t)0x2fffffffffff8a38);
        authentication.Write((uint64_t)0xd7ffffffffffcf55);
        authentication.Write((uint64_t)0x3bffffffffffe055);
        uint8_t unknown2 = 0x56;
        authentication.WriteBits(&unknown2, 7); // b10101100

        SendMessage(PACKET_SERVER_AUTHENTICATION, &authentication);
    }

    void Client::SendPlayerInfo(RakNet::SystemAddress serverAddress, RakNet::RakString playerName, RakNet::RakString playerTag, uint32_t playerTagColor, uint64_t playerSteamId, uint32_t timestamp)
    {
        RakNet::BitStream playerInfo;

        playerInfo.WriteCompressed(playerName);
        playerInfo.WriteCompressed(playerTag);
        playerInfo.Write(playerTagColor);
        playerInfo.Write(playerSteamId);
        playerInfo.Write(timestamp);

        uint8_t test[20] = { 0x76, 0xBC, 0x29, 0xA6, 0xC6, 0xB6, 0xBB, 0x60, 0x72, 0x37, 0x7A, 0x28, 0x6C, 0xBD, 0x17, 0xD5, 0xAA, 0x0B, 0xAC, 0xB9 };
        for(int i = 0; i < sizeof(test); i++)
            playerInfo.Write(test[i]);

        SendMessage(PACKET_SERVER_GET_PLAYER_INFO, &playerInfo);
    }

    void Client::SendUnknown(RakNet::SystemAddress serverAddress)
    {
        RakNet::BitStream unknown;

        unknown.Write((uint8_t)0x0);

        SendMessage(PACKET_SERVER_UNKNOWN2, &unknown);
    }

    void Client::SendUpdateSettings(RakNet::SystemAddress serverAddress)
    {
        RakNet::BitStream updateSettings;

        updateSettings.Write((uint8_t)0x40);

        SendMessage(PACKET_SERVER_PLAYER_UPDATE_SETTINGS, &updateSettings);
    }

    void Client::SendUnknown4(RakNet::SystemAddress serverAddress)
    {
        RakNet::BitStream unknown4;

        unknown4.Write((uint32_t)0x12);

        uint8_t test[275] = { 0x80, 0x06, 0x62, 0x00, 0x00, 0x00, 0x40, 0x88, 0x00, 0x00, 0x4A, 0x5A, 0x20, 0x00, 0x01, 0x29, 0x58, 0x80, 0x00, 0x04, 0xA9, 0x62, 0x00, 0x00, 0x12, 0x9C, 0x88, 0x00, 0x00, 0x4B, 0x4A, 0x20, 0x00, 0x01, 0x29, 0xF9, 0x80, 0x00, 0x00, 0x53, 0xA0, 0xFF, 0x7F, 0xBF, 0xE6, 0x00, 0x00, 0x01, 0x2F, 0x83, 0xFD, 0xFE, 0xFF, 0x98, 0x00, 0x00, 0x04, 0xD6, 0x0F, 0xF7, 0xFB, 0xFE, 0x60, 0x00, 0x00, 0x14, 0x28, 0x3F, 0xDF, 0xEF, 0xF9, 0x80, 0x00, 0x00, 0x5C, 0xA0, 0xFF, 0x7F, 0xBF, 0xE6, 0x00, 0x00, 0x01, 0x61, 0x83, 0xFD, 0xFE, 0xFF, 0x98, 0x00, 0x00, 0x05, 0x8E, 0x0F, 0xF7, 0xFB, 0xFE, 0x60, 0x00, 0x00, 0x16, 0xB8, 0x3F, 0xDF, 0xEF, 0xFA, 0x00, 0x00, 0x04, 0xAC, 0x7F, 0xC0, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x00, 0x16, 0x16, 0x16, 0x2A, 0x00, 0x00, 0x12, 0x13, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x10, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x49, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x09, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x5E, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x48, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x55, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x5D, 0x84, 0x2A, 0x00, 0x00, 0x12, 0x93, 0x84, 0x3F, 0xC0, 0x00, 0x00, 0x01, 0x40, 0x7C, 0xBE, 0x69, 0x24, 0xC5, 0xF2, 0x93, 0x62, 0xD5, 0x75, 0x2B, 0xF3, 0xAA, 0xAF, 0x99, 0xBA, 0xB2, 0xA5, 0xA8, 0xCF, 0xD5, 0xBA, 0x8A, 0xA2, 0xA8, 0x9F, 0x2F, 0xA7, 0x1A, 0x49, 0x31, 0x19, 0xB9, 0xD3, 0x15, 0x6C, 0x4E, 0xCB, 0x15, 0x01, 0xE3, 0x8E, 0x26, 0xC2, 0xA1, 0x00, 0x8A, 0x00, 0x23, 0x0B, 0xCB, 0x12, 0x4F, 0xDC, 0xDE, 0x70, 0xED, 0x14, 0x0F, 0x70, 0x0F, 0xA7, 0x8B, 0xD5, 0xAD, 0x56, 0x7A, 0x8F, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00 };
        for(int i = 0; i < sizeof(test); i++)
            unknown4.Write(test[i]);

        SendMessage(PACKET_SERVER_UNKNOWN4, &unknown4);
    }

    void Client::SendChatMessage(RakNet::SystemAddress serverAddress, RakNet::RakString message)
    {
        RakNet::BitStream chatMessage;

        chatMessage.WriteCompressed(message);

        SendMessage(PACKET_SERVER_CHAT_MESSAGE, &chatMessage);
    }

    Client::~Client()
    {
    }
}