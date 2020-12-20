#pragma once

#include <raknet/RakNetTypes.h>
#include <raknet/BitStream.h>
#include <raknet/MessageIdentifiers.h>

#include <iostream>

namespace TruckersMP
{
    class Utils
    {
    public:
        static unsigned char GetPacketIdentifier(RakNet::Packet* packet)
        {
            if (packet == nullptr)
                return 255;

            if ((unsigned char)packet->data[0] == ID_TIMESTAMP)
            {
                RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
                return (unsigned char) packet->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
            }
            else
                return (unsigned char) packet->data[0];
        }
        static void PrintLeftDataPacket(RakNet::BitStream* bitStream)
        {
            std::cout << "(" << std::dec << bitStream->GetNumberOfUnreadBits() << ") ";

            uint8_t byte;
            while(bitStream->GetNumberOfUnreadBits() >= 8)
            {
                if(bitStream->Read(byte))
                    printf("%.2X ", byte);
            }

            if(bitStream->GetNumberOfUnreadBits() > 0)
                std::cout << "b";

            while(bitStream->GetNumberOfUnreadBits())
            {
                if(bitStream->ReadBit())
                    std::cout << "1";
                else
                    std::cout << "0";
            }

            std::cout << std::endl;
        }
        static void TryFindString(RakNet::BitStream* bitStream, bool reset = false)
        {
            int offset = 0, numBits;

            if(reset)
            {
                bitStream->ResetReadPointer();
                numBits = bitStream->GetNumberOfUnreadBits();
            }
            else
            {
                int lastBits = bitStream->GetNumberOfUnreadBits();
                bitStream->ResetReadPointer();
                numBits = bitStream->GetNumberOfUnreadBits();

                offset = numBits - lastBits;
            }

            std::cout << "Start offset : " << std::dec << offset << std::endl;

            RakNet::RakString string;
            while(offset < numBits)
            {
                bitStream->SetReadOffset(offset);

                if(bitStream->ReadCompressed(string) && string.GetLength() > 0)
                    std::cout << "String found at " << std::dec << offset << " : " << string << std::endl;

                offset++;
            }
        }
        static RakNet::RakString Format(const char* format, ...)
        {
            char buffer[254];

            va_list args;
            va_start(args, format);

            vsprintf(buffer, format, args);

            va_end(args);

            return RakNet::RakString(buffer);
        }
        static void Debug(uint8_t* data, size_t size)
        {
            RakNet::BitStream bitStream;

            for(size_t i = 0; i < size; i++)
                bitStream.Write(data[i]);

            TryFindString(&bitStream);
        }
        template<typename T>
        static void Find(RakNet::BitStream* bitStream, T value, bool reset = false)
        {
            int offset = 0, numBits;

            if(reset)
            {
                bitStream->ResetReadPointer();
                numBits = bitStream->GetNumberOfUnreadBits();
            }
            else
            {
                int lastBits = bitStream->GetNumberOfUnreadBits();
                bitStream->ResetReadPointer();
                numBits = bitStream->GetNumberOfUnreadBits();

                offset = numBits - lastBits;
            }

            std::cout << "Start offset : " << std::dec << offset << std::endl;

            T found;
            while(offset < numBits)
            {
                bitStream->SetReadOffset(offset);

                if(bitStream->Read(found) && found == value)
                    std::cout << "String found at " << std::dec << offset << " : " << std::dec << (int)found << " - " << std::hex << (int)found << std::endl;

                offset++;
            }
        }
    };
}