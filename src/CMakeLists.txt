cmake_minimum_required (VERSION 2.8)
project (CADVIEW)

message(STATUS "CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")

set (CADVIEW_VERSION_MAJOR 0)
set (CADVIEW_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/cadview_config.h.in"
  "${PROJECT_BINARY_DIR}/cadview_config.h"
)

include_directories ("${PROJECT_BINARY_DIR}")

find_package(GTK2 2.8 REQUIRED gtk)
include_directories(${GTK2_INCLUDE_DIRS})
message(STATUS "GTK2_INCLUDE_DIRS = ${GTK2_INCLUDE_DIRS}")
  

find_package(Boost 1.47 REQUIRED regex)
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")

add_subdirectory (cadcore)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  add_subdirectory (cadview)
  add_subdirectory (gladeui)
  add_subdirectory (gtklab)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
