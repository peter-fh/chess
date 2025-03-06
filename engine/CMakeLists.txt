cmake_minimum_required(VERSION 3.15)

project (
	Engine
	VERSION 0.1
	DESCRIPTION "Chess engine using dfs and search tree pruning algorithms"
	LANGUAGES CXX
)

include_directories(
	PUBLIC "./include"
	"./test"
)

file(MAKE_DIRECTORY "generated")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB LIB_SOURCES "lib/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (PST)
	message("Building pst executable")
	add_executable(Pst src/pst_main.cpp ${LIB_SOURCES})
elseif (TEST)
	message("Building test executable")
	include_directories(
	)
	add_executable(Test test/test_main.cpp ${LIB_SOURCES} ${TEST_SOURCES})
else ()
	message("Building engine executable")
	add_library(Engine SHARED ${LIB_SOURCES})
	target_include_directories(Engine
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	)
endif()


