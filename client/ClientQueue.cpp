#include "ClientQueue.hpp"

#include <truckersmp/Packets.hpp>
#include <truckersmp/Utils.hpp>
#include <truckersmp/TruckersMP.hpp>
#include <truckersmp/Authentication.hpp>

#include <iostream>

namespace TruckersMP
{
    ClientQueue::ClientQueue(uint32_t appId, uint32_t accountId)
        : ClientBase(), m_ticket(0), m_appId(appId), m_accountId(accountId)
    {
    }

    void ClientQueue::OnConnectionRequestAccepted(RakNet::SystemAddress serverAddress)
    {
        std::cout << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Connected !" << std::endl;

#ifndef NDEBUG
        std::cout << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Send queue initialization" << std::endl;
#endif

        RakNet::BitStream authentication;

        authentication.WriteCasted<uint8_t>(TRUCKERSMP_PROTOCOL_VERSION);
        authentication.Write(m_appId);
        authentication.Write(m_accountId);

        SendMessage(PACKET_QUEUE_AUTHENTICATION, &authentication);
    }

    void ClientQueue::OnConnectionAttemptFailed(RakNet::SystemAddress serverAddress)
    {
        std::cerr << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Failed connection" << std::endl;

        m_client->Shutdown(300);
    }

    void ClientQueue::OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet)
    {
        switch (packetId)
        {
            case PACKET_QUEUE_AUTHENTICATION_REFUSED:
            {
                AuthenticationError error;

                bitStream->ReadCasted<uint8_t>(error);

                std::cout << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Authentication refused : " << Authentication::GetError(error) << std::endl;
    
                m_client->Shutdown(300);
                break;
            }
            case PACKET_QUEUE_POSITION:
            {
                bitStream->Read(m_position);

                std::cout << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Receive queue position : " << GetPosition() << std::endl;;
                break;
            }
            case PACKET_QUEUE_FINISH:
            {
                std::cout << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Receive queue finish" << std::endl;

                bitStream->Read(m_ticket);

                m_client->Shutdown(300);
                break;
            }
            default:
            {
#ifndef NDEBUG
                std::cerr << "[ClientQueue][" << m_client->GetMyBoundAddress().ToString() << "] Unknown packet id : " << std::hex << (int)packetId << std::endl;
#endif
                break;
            }
        }
    }

    uint32_t ClientQueue::GetPosition()
    {
        return m_position;
    }

    uint32_t ClientQueue::GetTicket()
    {
        return m_ticket;
    }

    void ClientQueue::SetAppId(uint32_t appId)
    {
        m_appId = appId;
    }

    uint32_t ClientQueue::GetAppId()
    {
        return m_appId;
    }

    void ClientQueue::SetAccountId(uint32_t accountId)
    {
        m_accountId = accountId;
    }

    uint32_t ClientQueue::GetAccountId()
    {
        return m_accountId;
    }

    ClientQueue::~ClientQueue()
    {
    }
}