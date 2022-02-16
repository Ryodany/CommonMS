cmake_minimum_required (VERSION 3.22.2)
project(CommonmsProject VERSION 1.0.0)

add_library(CommonmsLib
	library.cpp
	library.h
	games.h
	player.h)

add_executable("${PROJECT_NAME}" main.cpp)

target_link_libraries("${PROJECT_NAME}" PRIVATE CommonmsLib)