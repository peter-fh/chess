cmake_minimum_required(VERSION 3.15)

project (
	Engine
	VERSION 0.1
	DESCRIPTION "Chess engine using dfs and search tree pruning algorithms"
	LANGUAGES CXX
)

include_directories(
	"./include"
	"./test"
)

file(MAKE_DIRECTORY "generated")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB LIB_SOURCES "lib/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (ENGINE)
	message("Building engine executable")
	add_executable(Engine src/engine_main.cpp ${LIB_SOURCES})
elseif (PST)
	message("Building pst executable")
	add_executable(Pst src/pst_main.cpp ${LIB_SOURCES})
elseif (TEST)
	message("Building test executable")
	include_directories(
	)
	add_executable(Test test/test_main.cpp ${LIB_SOURCES} ${TEST_SOURCES})
else ()
	message("ERROR: Please specify an entrypoint")
endif()


