add_executable(TruckersMP-Client main.cpp ClientBase.cpp ClientQueue.cpp Client.cpp)

include_directories(${TRUCKERSMP_RAKNET_HEADERS} ${TRUCKERSMP_HEADERS})

target_link_libraries(TruckersMP-Client ${TRUCKERSMP_RAKNET_LIBS} pthread)