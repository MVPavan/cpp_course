cmake_minimum_required(VERSION 3.19)
project(Udacity)

set(CMAKE_CXX_STANDARD 17)

#add_library(LibsModule Concurrency/practice.cpp)
#target_link_libraries(LibsModule -lpthread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(
        Udacity
        Concurrency/practice.cpp
#        main.cpp
)
#target_link_libraries(Udacity LibsModule)


