cmake_minimum_required(VERSION 2.6)
include(FindBoost)

project(rtypeServer)

if (UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
  endif()
else (WIN32)
  SET(Boost_LIB_DIAGNOSTIC_DEFINITIONS "-DBOOST_LIB_DIAGNOSTIC")
  SET(CMAKE_INSTALL_PREFIX ".")
endif()

set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.39.0 COMPONENTS system thread REQUIRED)

include_directories(header)
include_directories(${Boost_INCLUDE_DIRS})

file(
  GLOB_RECURSE
  rtypeServerFiles
  src/*.cpp
  header/*.h*
)

add_executable(rtypeServer ${rtypeServerFiles})

target_link_libraries(
  rtypeServer
  ${Boost_LIBRARIES}
)
