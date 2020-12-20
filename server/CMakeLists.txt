add_executable(TruckersMP-Server main.cpp ServerBase.cpp ServerQueue.cpp Server.cpp ChatCommands.cpp)

include_directories(${TRUCKERSMP_RAKNET_HEADERS} ${TRUCKERSMP_HEADERS})

target_link_libraries(TruckersMP-Server ${TRUCKERSMP_RAKNET_LIBS} pthread)