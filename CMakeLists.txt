cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(OPhaseGroupAssignment)

add_executable(BasicTest basic_test definitions.cpp algorithms.cpp)
add_executable(Main main.cpp definitions.cpp algorithms.cpp moves_local_search.cpp parse.cpp)
add_executable(RandomizedTest randomized_test definitions.cpp algorithms.cpp)

execute_process(COMMAND cmake -P ${CMAKE_CURRENT_SOURCE_DIR}/download_boost.cmake)

include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR}/boost/)

# glob boost sources
file(GLOB MINI_BOOST_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/boost/libs/graph/src/*.cpp)

add_library(mini_boost STATIC ${MINI_BOOST_SOURCES})
set_target_properties(mini_boost PROPERTIES LINKER_LANGUAGE CXX)
set(Boost_LIBRARIES mini_boost)
set(Boost_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/boost/boost/)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# set flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmaybe-uninitialized")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnoexcept")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPARANOID ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function")
endif()
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
