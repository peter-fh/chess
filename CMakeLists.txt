cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(HttpChessEngine)

add_subdirectory(engine)

add_executable(Server server.cpp)


target_link_libraries(Server PRIVATE Engine)
target_include_directories(Server PRIVATE ${CMAKE_SOURCE_DIR})

