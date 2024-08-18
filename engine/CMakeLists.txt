cmake_minimum_required(VERSION 3.15)

project (
	Engine
	VERSION 0.1
	DESCRIPTION "Chess engine using dfs and search tree pruning algorithms"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB LIB_SOURCES "lib/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Engine src/driver.cpp)
add_executable(Test test/main_test.cpp ${LIB_SOURCES})


include_directories(
	"./include"
)
