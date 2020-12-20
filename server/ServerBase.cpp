#include "ServerBase.hpp"

#include <raknet/RakSleep.h>
#include <raknet/Kbhit.h>
#include <raknet/MessageIdentifiers.h>
#include <raknet/BitStream.h>

#include <truckersmp/Utils.hpp>

#include <iostream>

namespace TruckersMP
{
    ServerBase::ServerBase(unsigned int maxPlayers, unsigned short port)
    {
        m_server = RakNet::RakPeerInterface::GetInstance();

        m_server->SetTimeoutTime(30000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
        m_server->SetMaximumIncomingConnections(maxPlayers);

        RakNet::SocketDescriptor socketDescriptor(port, nullptr);
#if RAKNET_SUPPORT_IPV6==1
        socketDescriptor.socketFamily = AF_INET6; // Test out IPV6
#else
        socketDescriptor.socketFamily = AF_INET; // Test out IPV4
#endif
        bool b = m_server->Startup(maxPlayers, &socketDescriptor, 1) == RakNet::RAKNET_STARTED;
        if (!b)
        {
#if RAKNET_SUPPORT_IPV6==1
            std::cerr << "[ServerBase][" << 0 << ":" << port << "] Failed to start dual IPV4 and IPV6 ports. Trying IPV4 only." << std::endl;

            // Try again, but leave out IPV6
            socketDescriptor.socketFamily = AF_INET; // Test out IPV4
            b = m_server->Startup(maxPlayers, &socketDescriptor, 1) == RakNet::RAKNET_STARTED;
            if (!b)
            {
#endif
                std::cerr << "[ServerBase][" << 0 << ":" << port << "] Server failed to start.  Terminating." << std::endl;
                exit(1);
#if RAKNET_SUPPORT_IPV6==1
            }
#endif
        }

        m_server->SetOccasionalPing(true);
        m_server->SetUnreliableTimeout(1000);

        std::cout << "[ServerBase][" << m_server->GetMyBoundAddress().ToString() << "] Server GUID is " << m_server->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString() << std::endl;
    }

    void ServerBase::Listen()
    {
        RakNet::Packet* packet;
        unsigned char packetId;

        std::cout << "[ServerBase][" << m_server->GetMyBoundAddress().ToString() << "] Listen..." << std::endl;

        while(m_server->IsActive())
        {
            RakSleep(30);

            while (packet = m_server->Receive())
            {
                packetId = Utils::GetPacketIdentifier(packet);

                switch (packetId)
                {
                case ID_DISCONNECTION_NOTIFICATION:
                    OnDisconnection(packet->systemAddress, packet->guid);
                    break;
                case ID_NEW_INCOMING_CONNECTION:
                    OnNewIncomingConnection(packet->systemAddress, packet->guid);
                    break;
                case ID_INCOMPATIBLE_PROTOCOL_VERSION:
                    OnIncompatibleProtocolVersion(packet->systemAddress, packet->guid);
                    break;
                case ID_CONNECTED_PING:
                    OnPing(packet->systemAddress, packet->guid, true);
                    break;
                case ID_UNCONNECTED_PING:
                    OnPing(packet->systemAddress, packet->guid, false);
                    break;
                case ID_SND_RECEIPT_LOSS:
                case ID_CONNECTION_LOST:
                    OnConnectionLost(packet->systemAddress, packet->guid);
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
                        std::cerr << "[ClientBase][" << m_server->GetMyBoundAddress().ToString() << "][" << packet->systemAddress.ToString() << "][ID:" << std::hex << (int)messagePacketId << "] Unread data : ";
                        Utils::PrintLeftDataPacket(&messageData);
                    }
#endif
                    break;
                }

                m_server->DeallocatePacket(packet);
            }
        }

        std::cout << "[ServerBase][" << m_server->GetMyBoundAddress().ToString() << "] Shutdown..." << std::endl;
    }

    void ServerBase::OnNewIncomingConnection(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID)
    {
    }

    void ServerBase::OnIncompatibleProtocolVersion(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID)
    {
    }

    void ServerBase::OnPing(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID, bool connected)
    {
    }

    void ServerBase::OnMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, RakNet::Packet* packet)
    {
    }

    void ServerBase::OnDisconnection(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID)
    {
    }

    void ServerBase::OnConnectionLost(RakNet::SystemAddress clientAddress, RakNet::RakNetGUID clientGUID)
    {
    }

    void ServerBase::SendMessage(RakNet::MessageID packetId, RakNet::BitStream* bitStream, PacketPriority priority, PacketReliability reliability,
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

        m_server->Send(&packet, priority, reliability, orderingChannel, systemIdentifier, broadcast, forceReceiptNumber);
    }

    ServerBase::~ServerBase()
    {
        m_server->Shutdown(300);
        RakNet::RakPeerInterface::DestroyInstance(m_server);
    }
}