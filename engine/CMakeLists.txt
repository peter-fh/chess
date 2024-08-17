cmake_minimum_required(VERSION 3.15)

project (
	Engine
	VERSION 0.1
	DESCRIPTION "Chess engine using dfs and search tree pruning algorithms"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB LIB_SOURCES "lib/*.cpp")

add_executable(Engine src/driver.cpp ${LIB_SOURCES})

include_directories(
	"./include"
)
