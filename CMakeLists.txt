cmake_minimum_required(VERSION 3.8)
project(VFMS)

# Check for Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    src/command_map.cpp
    src/string_parser.cpp
)

# libvfms library
add_library(libvfms SHARED ${SOURCES} ${USED_LIBS})

# VFMS executable
add_executable(vfms src/main.cpp)
target_link_libraries(vfms libvfms ${USED_LIBS})