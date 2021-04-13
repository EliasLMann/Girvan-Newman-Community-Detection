cmake_minimum_required(VERSION 3.16)
project(21-s-pa03-eliasmann)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS_DEBUG "-O3")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.75.0 COMPONENTS graph)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(21-s-pa03-eliasmann src/main.cpp src/Girvan_Newman.cpp src/Girvan_Newman.h)
    target_link_libraries(21-s-pa03-eliasmann ${Boost_LIBRARIES})
endif()