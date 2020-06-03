cmake_minimum_required(VERSION 3.14)
project(dccp)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS regex system coroutine context thread serialization REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(client dccp.hpp client.cpp)
    add_executable(server dccp.hpp server.cpp)
    target_link_libraries (client ${Boost_LIBRARIES})
    target_link_libraries (server ${Boost_LIBRARIES})
endif()


