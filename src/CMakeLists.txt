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

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.47 REQUIRED regex)
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")

add_subdirectory (cadcore)

find_package(GTK2 2.8 gtk)

if(GTK2_FOUND)
  include_directories(${GTK2_INCLUDE_DIRS})
  message(STATUS "GTK2_INCLUDE_DIRS = ${GTK2_INCLUDE_DIRS}")
  message(STATUS "GTK2_LIBRARIES = ${GTK2_LIBRARIES}")

  add_subdirectory (cadview)
  add_subdirectory (gladeui)
  add_subdirectory (gtklab)
endif()