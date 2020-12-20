#pragma once

#include <cstdint>

#define ETS2_APP_ID                 227300
#define ATS_APP_ID                  270880

#define TRUCKERSMP_DEFAULT_PORT     42700

#define TRUCKERSMP_PROTOCOL_VERSION 173

namespace TruckersMP
{
    class TruckersMP
    {
    public:
        static bool IsSupportedAppId(uint32_t appId)
        {
            return appId == ETS2_APP_ID || appId == ATS_APP_ID;
        };
    };
}