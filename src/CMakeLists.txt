cmake_minimum_required(VERSION 2.8)
project(algorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# set(PROJECT_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../bin/")
# set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../bin/")
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${PROJECT_INCLUDE_DIR})

# GTest
enable_testing()
find_package(GTest REQUIRED)
if(GTEST_FOUND)
  message("GTest found")
  include_directories(${GTEST_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "can not find GTest")
endif()
# GTest

# Boost
find_package(Boost REQUIRED)
if(Boost_FOUND)
  message("Boost found")
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "can not find Boost")
endif()
# Boost

add_subdirectory(dynamic_program/test/)
add_subdirectory(data_structure/test/)
add_subdirectory(remove_duplicate/test)
add_subdirectory(search/test)
add_subdirectory(double_pointer/test)
add_subdirectory(slide_window/test)
add_subdirectory(back_track/test)
add_subdirectory(trick/test)
add_subdirectory(sort/test)
add_subdirectory(computational_geometry/test)
add_subdirectory(stl/test)
