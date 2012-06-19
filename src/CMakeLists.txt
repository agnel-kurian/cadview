cmake_minimum_required (VERSION 2.6)
project (CADVIEW)

set (CADVIEW_VERSION_MAJOR 1)
set (CADVIEW_VERSION_MINOR 2)

configure_file (
  "${PROJECT_SOURCE_DIR}/cadview_config.h.in"
  "${PROJECT_BINARY_DIR}/cadview_config.h"
)

find_package(GTK2 2.8 COMPONENTS gtk)


if(GTK2_FOUND)
  include_directories(${GTK2_INCLUDE_DIRS})

  add_subdirectory (cadcore)
  add_subdirectory (cadview)
  add_subdirectory (gladeui)
  add_subdirectory (gtklab)

endif()

include_directories ("${PROJECT_BINARY_DIR}")

# add_executable(gladeui gladeui/main.cpp)
# target_link_libraries (gladeui gtk+-2.0) 