cmake_minimum_required(VERSION 3.0.0)
project(DProtect)
set(Boost_USE_MULTITHREADED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lboost_thread -lboost_filesystem -lboost_log -DBOOST_LOG_DYN_LINK")

find_package( Boost 1.56.0 REQUIRED thread system log log_setup program_options)
find_package( Threads )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
#LINK_DIRECTORIES(${Boost_LIBRARY_DIR})

file(GLOB sources_localdir *.cpp *.h)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/Worker
)

set(SOURCE_FILES
  Worker/Master.cpp
  Worker/Checker.cpp
  Worker/System.cpp
  main.cpp)

add_executable(DProtect ${SOURCE_FILES})
