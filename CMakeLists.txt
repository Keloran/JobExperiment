# CMake Version
cmake_minimum_required(VERSION 2.8)
include(CMakeDependentOption)

# Project Name
project(GameLibrary)

# OSX
set(CMAKE_MACOSX_RPATH 0)

# CMake Modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeConfigs)

# CMake Flags
if (WIN32)
    # C++11
    
else()
    if (APPLE)
        # C++11
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
        set(EXTRA_FLAGS " -x objective-c++")
    elseif (UNIX)
        # C++11
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -m64")
        set(EXTRA_FLAGS "")
    endif()
endif()

# Defines
set(GP ${PROJECT_SOURCE_DIR}/Game)
set(LibHeaders ${GP}/Game.hpp)
set(LibSources ${GP}/Game.cpp)

# Includes
list(APPEND LibHeaders ${GP}/Includes.hpp)

# Link Path
link_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

# Generator
include_directories(${GP}/Generator)
link_directories(${GP}/Generator)
list(APPEND LibHeaders ${GP}/Generator/Generator.hpp)

# Jobs
list(APPEND LibHeaders ${GP}/Generator/Jobs.hpp)
list(APPEND LibSources ${GP}/Generator/Jobs.cpp)

# Settlement
list(APPEND LibHeaders ${GP}/Generator/Settlements.hpp)
list(APPEND LibSources ${GP}/Generator/Settlements.cpp)

# Game Start
#include_directories(${GP}/GameStart)
#link_directories(${GP}/GameStart)
#list(APPEND LibHeaders ${GP}/GameStart/GameStart.hpp)
#list(APPEND LibSources ${GP}/GameStart/GameStart.cpp)

# Build Number
list(APPEND LibHeaders ${GP}/buildNumber.hpp)

# NordicEngine
find_package(NordicEngine)
include_directories(${NordicEngine_Path})
link_directories(${NordicEngine_Path})

# Generate Library
add_library(GameLibrary SHARED ${LibSources} ${LibHeaders})
set_target_properties(GameLibrary PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(GameLibrary PROPERTIES OUTPUT_NAME "Game")

# Link
target_link_libraries(GameLibrary NordicEngine)
