add_executable (gladeui main.cpp slate.cpp)
target_link_libraries (gladeui ${GTK2_LIBRARIES})
target_link_libraries (gladeui ${Boost_LIBRARIES})
file (COPY ${PROJECT_SOURCE_DIR}/gladeui/cadview.glade
  DESTINATION ${PROJECT_BINARY_DIR}/gladeui )
