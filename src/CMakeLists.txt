cmake_minimum_required(VERSION 3.0)
project(Tetris)

set(HEADERS 
		blockCLASS.h
		mapCLASS.h
		observerCLASS.h)

set(SOURCES	
		main.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})