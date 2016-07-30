cmake_minimum_required(VERSION 2.6)
include(FindBoost)

project(rtypeClient)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

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

find_package(Boost 1.39.0 COMPONENTS system thread filesystem serialization REQUIRED)
find_package(SFML REQUIRED)

include_directories(header)
include_directories(${Boost_INCLUDE_DIRS})


file(
  GLOB_RECURSE
  rtypeClientFiles
  src/*.cpp
  header/*.h*
)

if (UNIX)
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/WLoaderLib.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Player1.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Player2.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Player3.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Player4.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Monster1.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Monster2.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon1.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon2.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon3.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon4.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Boss1.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/Explosion1.cpp")
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/main.level.cpp")
else (WIN32)
  list (REMOVE_ITEM rtypeClientFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/ULoaderLib.cpp")
endif()

add_executable(rtypeClient ${rtypeClientFiles})

target_link_libraries(
  rtypeClient
  ${Boost_LIBRARIES}
  ${SFML_LIBRARY}
)
