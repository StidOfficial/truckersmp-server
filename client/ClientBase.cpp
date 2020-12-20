#include "ClientBase.hpp"

#include <raknet/MessageIdentifiers.h>
#include <raknet/BitStream.h>
#include <raknet/RakSleep.h>

#include <truckersmp/Utils.hpp>

#include <iostream>

namespace TruckersMP
{
    //RakNet::PacketLogger messageHandler;

    ClientBase::ClientBase()
    {
        m_client = RakNet::RakPeerInterface::GetInstance();

        m_client->SetMaximumIncomingConnections(1);

        RakNet::SocketDescriptor socketDescriptor;
        bool b = m_client->Startup(1, &socketDescriptor, 1) == RakNet::RAKNET_STARTED;
        if (!b)
        {
            std::cerr << "[ClientBase] Client failed to start.  Terminating." << std::endl;
            exit(1);
        }

        //messageHandler.LogHeader();
    }

    bool ClientBase::Connect(const char ip[64], unsigned short port)
    {
        RakNet::ConnectionAttemptResult car = m_client->Connect(ip, port, nullptr, 0);
        
        std::cout << "[ClientBase][" << m_client->GetMyBoundAddress().ToString() << "] GUID : " << m_client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << std::endl;
        std::cout << "[ClientBase][" << m_client->GetMyBoundAddress().ToString() << "] Connection..." << std::endl;

        return car == RakNet::CONNECTION_ATTEMPT_STARTED;
    }

    void ClientBase::OnRemoteNewIncomingConnection(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnAlreadyConnected(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnIncompatibleProtocolVersion(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnDisconnection(RakNet::SystemAddress clientAddress, bool remote)
    {
    }

    void ClientBase::OnConnectionLost(RakNet::SystemAddress serverAddress, bool remote)
    {
    }

    void ClientBase::OnBanned(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnConnectionAttemptFailed(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnNoFreeIncomingConnections(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnInvalidPassword(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnConnectionRequestAccepted(RakNet::SystemAddress serverAddress)
    {
    }

    void ClientBase::OnPing(RakNet::SystemAddress serverAddress, bool connected)
    {
    }

    void ClientBase::OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet)
    {
    }

    void ClientBase::SendMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, PacketPriority priority, PacketReliability reliability,
                                    char orderingChannel, const RakNet::AddressOrGUID systemIdentifier, bool broadcast, uint32_t forceReceiptNumber)
    {
        RakNet::BitStream packet;
        packet.Write((RakNet::MessageID)(ID_USER_PACKET_ENUM + 1));
        packet.Write(packetId);
        if(bitStream)
        {
            bitStream->ResetReadPointer();
            packet.AlignWriteToByteBoundary();
            packet.Write(bitStream);
        }

        m_client->Send(&packet, priority, reliability, orderingChannel, systemIdentifier, broadcast, forceReceiptNumber);
    }

    void ClientBase::Listen()
    {
        RakNet::Packet* packet;
        unsigned char packetId;

        std::cout << "[ClientBase][" << m_client->GetMyBoundAddress().ToString() << "] Listen..." << std::endl;

        while(m_client->IsActive())
        {
            RakSleep(30);

            while(packet = m_client->Receive())
            {
                packetId = Utils::GetPacketIdentifier(packet);

                switch (packetId)
                {
                case ID_DISCONNECTION_NOTIFICATION:
                    OnDisconnection(packet->systemAddress, false);
                    break;
                case ID_ALREADY_CONNECTED:
                    OnAlreadyConnected(packet->systemAddress);
                    break;
                case ID_INCOMPATIBLE_PROTOCOL_VERSION:
                    OnIncompatibleProtocolVersion(packet->systemAddress);
                    break;
                case ID_REMOTE_DISCONNECTION_NOTIFICATION:
                    OnDisconnection(packet->systemAddress, true);
                    break;
                case ID_REMOTE_CONNECTION_LOST:
                    OnConnectionLost(packet->systemAddress, true);
                    break;
                case ID_REMOTE_NEW_INCOMING_CONNECTION:
                    OnRemoteNewIncomingConnection(packet->systemAddress);
                    break;
                case ID_CONNECTION_BANNED:
                    OnBanned(packet->systemAddress);
                    break;			
                case ID_CONNECTION_ATTEMPT_FAILED:
                    OnConnectionAttemptFailed(packet->systemAddress);
                    break;
                case ID_NO_FREE_INCOMING_CONNECTIONS:
                    OnNoFreeIncomingConnections(packet->systemAddress);
                    break;
                case ID_INVALID_PASSWORD:
                    OnInvalidPassword(packet->systemAddress);
                    break;
                case ID_CONNECTION_LOST:
                    OnConnectionLost(packet->systemAddress, false);
                    break;
                case ID_CONNECTION_REQUEST_ACCEPTED:
                    OnConnectionRequestAccepted(packet->systemAddress);
                    break;
                case ID_CONNECTED_PING:
                    OnPing(packet->systemAddress, true);
                    break;
                case ID_UNCONNECTED_PING:
                    OnPing(packet->systemAddress, false);
                    break;
                default:
                    RakNet::BitStream messageData(packet->data, packet->length, false);
                    messageData.SetWriteOffset(packet->bitSize);

                    messageData.IgnoreBytes(1); // Ignore RakNet packet ID
                    RakNet::MessageID messagePacketId;
                    messageData.Read(messagePacketId);

                    messageData.AlignReadToByteBoundary();

                    OnMessage(messagePacketId, &messageData, packet);

#ifndef NDEBUG
                    if(messageData.GetNumberOfUnreadBits() > 0)
                    {
                        std::cerr << "[ClientBase][" << m_client->GetMyBoundAddress().ToString() << "][ID:" << std::hex << (int)messagePacketId << "] Unread data : ";
                        Utils::PrintLeftDataPacket(&messageData);
                    }
#endif
                    break;
                }
            }
        }

        std::cout << "[ServerBase][" << m_client->GetMyBoundAddress().ToString() << "] Shutdown..." << std::endl;
    }

    ClientBase::~ClientBase()
    {
        m_client->Shutdown(300);
        RakNet::RakPeerInterface::DestroyInstance(m_client);
    }
}