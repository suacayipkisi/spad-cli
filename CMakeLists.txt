cmake_minimum_required(VERSION 3.16)
project(SPAD-CLI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
	main.cpp
	src/spadcli.cpp
)
add_executable(spadcli ${SOURCES})
