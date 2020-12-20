#pragma once

#include <string>

namespace TruckersMP
{
    enum AuthenticationError
    {
        INVALID_CLIENT_PROTOCOL,
        PLAYER_NOT_WHITELISTED,
        STEAMID_ALREADY_CONNECTED,
        INVALID_SESSION,
        BANNED,
        INVALID_CLIENT,
        UNKNOWN,
        PROTOCOL_ERROR,
        UNREGISTERED_DLC
    };

    class Authentication
    {
    public:
        static std::string GetError(AuthenticationError error)
        {
            switch(error)
            {
                case AuthenticationError::INVALID_CLIENT_PROTOCOL:
                    return "The client protocol version does not match";
                    break;
                case AuthenticationError::PLAYER_NOT_WHITELISTED:
                    return "The current player is not whitelisted";
                    break;
                case AuthenticationError::STEAMID_ALREADY_CONNECTED:
                    return "Someone is already playing with that SteamID";
                    break;
                case AuthenticationError::INVALID_SESSION:
                    return "Current session is invalid";
                    break;
                case AuthenticationError::BANNED:
                    return "The current player is banned from the TruckerMP network.";
                    break;
                case AuthenticationError::INVALID_CLIENT:
                    return "An invalid client is used, or data files do not match with the server";
                    break;
                case AuthenticationError::UNKNOWN:
                    return "Unknown error";
                    break;
                case AuthenticationError::PROTOCOL_ERROR:
                    return "Protocol error";
                    break;
                case AuthenticationError::UNREGISTERED_DLC:
                    return "Unregistered DLC packages found";
                    break;
                default:
                    return "Unknown";
            }
        };
    };
}