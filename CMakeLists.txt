cmake_minimum_required(VERSION 3.0.0)
project(TruckersMP VERSION 0.1.0)

include(CTest)
enable_testing()

set(TRUCKERSMP_RAKNET_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/RakNet/include)
set(TRUCKERSMP_RAKNET_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/RakNet/Lib/LibStatic/libRakNetLibStatic.a)
set(TRUCKERSMP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/shared)

# If RAKNET_SUPPORT_IPV6 set to 0 and is set to here, you receive only ID_MESSAGE_PING
#add_compile_definitions(RAKNET_SUPPORT_IPV6=1)

add_subdirectory(client)
add_subdirectory(server)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)