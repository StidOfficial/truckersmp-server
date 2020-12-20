#include "ServerQueue.hpp"

#include <raknet/BitStream.h>

#include <truckersmp/Utils.hpp>
#include <truckersmp/TruckersMP.hpp>

#include <iostream>

namespace TruckersMP
{
    ServerQueue::ServerQueue(unsigned short port)
        : ServerBase(100, port)
    {
        std::cout << "[ServerQueue][" << 0 << ":" << port << "] Listen on " << port << std::endl;
    }

    void ServerQueue::OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet)
    {
        switch(packetId)
        {
            case PACKET_QUEUE_AUTHENTICATION:
            {
                uint8_t protocolVersion;
                uint32_t appId;
                uint32_t accountId;

                bitStream->Read(protocolVersion);
                bitStream->Read(appId);
                bitStream->Read(accountId);

#ifndef NDEBUG
                std::cout << "[ServerQueue][" << m_server->GetMyBoundAddress().ToString() << "][" << packet->systemAddress.ToString() << "] Receive queue initialization" << std::endl;
#endif

                if(protocolVersion == TRUCKERSMP_PROTOCOL_VERSION)
                {
                    if(TruckersMP::IsSupportedAppId(appId))
                    {
                        SendPosition(packet->systemAddress, 500);
                        SendFinish(packet->systemAddress);
                    }
                    else
                        SendAuthenticationRefused(packet->systemAddress, AuthenticationError::INVALID_CLIENT);
                }
                else
                    SendAuthenticationRefused(packet->systemAddress, AuthenticationError::INVALID_CLIENT_PROTOCOL);
                break;
            }
            default:
            {
#ifndef NDEBUG
                std::cerr << "[ServerQueue][" << m_server->GetMyBoundAddress().ToString() << "][" << packet->systemAddress.ToString() << "] Unknown packet ID : " << std::hex << (int)packetId << std::endl;
#endif
                break;
            }
        }
    }

    void ServerQueue::SendPosition(RakNet::SystemAddress clientId, uint32_t position)
    {
#ifndef NDEBUG
        std::cout << "[ServerQueue][" << m_server->GetMyBoundAddress().ToString() << "][" << clientId.ToString() << "] Send queue position" << std::endl;
#endif

        RakNet::BitStream queuePosition;
        queuePosition.Write(position);

        SendMessage(PACKET_QUEUE_POSITION, &queuePosition, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void ServerQueue::SendFinish(RakNet::SystemAddress clientId)
    {
#ifndef NDEBUG
        std::cout << "[ServerQueue][" << m_server->GetMyBoundAddress().ToString() << "][" << clientId.ToString() << "] Send queue finish" << std::endl;
#endif

        RakNet::BitStream queueFinish;
        queueFinish.Write((uint32_t)1723007763); // ticket random

        SendMessage(PACKET_QUEUE_FINISH, &queueFinish, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);
    }

    void ServerQueue::SendAuthenticationRefused(RakNet::SystemAddress clientId, AuthenticationError error)
    {
        RakNet::BitStream authenticationRefused;

        authenticationRefused.WriteCasted<uint8_t>(error);

        SendMessage(PACKET_QUEUE_AUTHENTICATION_REFUSED, &authenticationRefused, HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientId, false);

        m_server->CloseConnection(clientId, true);
    }

    ServerQueue::~ServerQueue()
    {
    }
}