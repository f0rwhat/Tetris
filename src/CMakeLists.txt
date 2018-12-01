cmake_minimum_required(VERSION 3.0)
project(Tetris)

#set the C++ standard to be used 
set (CMAKE_CXX_STANDARD 14)

set(HEADERS 
		blockCLASS.h
		mapCLASS.h
		observerCLASS.h)

set(SOURCES	
		main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/../import)
link_directories(${CMAKE_SOURCE_DIR}/../lib/SFML)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(Tetris sfml-graphics sfml-system sfml-window sfml-main) 
