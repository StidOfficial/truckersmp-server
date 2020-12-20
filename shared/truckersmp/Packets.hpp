#pragma once

/* For queue server */
#define PACKET_QUEUE_UNKNOWN1                   0x15 // Unreceive
#define PACKET_QUEUE_AUTHENTICATION_REFUSED     0x90
#define PACKET_QUEUE_AUTHENTICATION             0xbb
#define PACKET_QUEUE_POSITION                   0xbc
#define PACKET_QUEUE_FINISH                     0xbd

/* For server */
#define PACKET_CLIENT_TRUCK_STATUS              0x8c
#define PACKET_SERVER_PLAYER_STATUS             0x8c
#define PACKET_SERVER_AUTHENTICATION            0x8d
#define PACKET_SERVER_AUTHENTICATION_ACCEPTED   0x8f
#define PACKET_SERVER_GET_PLAYER_INFO           0x8f
#define PACKET_SERVER_AUTHENTICATION_REFUSED    0x90
#define PACKET_SERVER_PLAYER_INFO               0x91
#define PACKET_CLIENT_UNKNOWN1                  0x92
#define PACKET_SERVER_PLAYER_TRUCK_UNSPAWN      0x93
#define PACKET_SERVER_PLAYER_TRAILER_DETACH     0x94
#define PACKET_SERVER_PLAYER_FINISH_MISSION     0x95
#define PACKET_SERVER_PLAYER_CHANGE_TAG         0x9b
#define PACKET_SERVER_PLAYER_TOLL_GATE          0x9d
#define PACKET_SERVER_PLAYER_UPDATE_SETTINGS    0x9c
#define PACKET_SERVER_TIME                      0x9f
#define PACKET_SERVER_JOIN                      0xa1 // Source
#define PACKET_SERVER_JOIN_REPLY                0xa2 // Source
#define PACKET_SERVER_CHAT_MESSAGE              0xa3
#define PACKET_SERVER_CURRENT_TIME              0xa4
#define PACKET_SERVER_PLAYER_TALK               0xa5
#define PACKET_SERVER_UNKNOWN4                  0xa6
#define PACKET_SERVER_ADD_PLAYER                0xa8
#define PACKET_CLIENT_PLAYER_STATUS             0xa8
#define PACKET_SERVER_UNKNOWN3                  0xa9
#define PACKET_SERVER_KICK_PLAYER               0xac
#define PACKET_SERVER_PLAYER_ID                 0xc0
#define PACKET_SERVER_PLAYER_SUBMIT_REPORT      0xb8
#define PACKET_SERVER_UNKNOWN2                  0xbf
#define PACKET_SERVER_FIX_TRUCK                 0xc1