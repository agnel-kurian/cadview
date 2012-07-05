add_executable (cadview main.cpp slate.cpp)
target_link_libraries (cadview ${GTK2_LIBRARIES})
target_link_libraries (cadview ${Boost_LIBRARIES})
