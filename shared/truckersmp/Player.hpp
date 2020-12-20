#pragma once

#include <raknet/RakString.h>

namespace TruckersMP
{
    struct Player
    {
        RakNet::AddressOrGUID clientId;
        uint32_t id;
        uint32_t accountId;
        uint64_t steamId;
        RakNet::RakString name;
        RakNet::RakString tag;
        uint32_t tagColor;
        bool groupVisible;
        uint8_t unknown1;
    };
}