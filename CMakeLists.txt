cmake_minimum_required(VERSION 3.0)
project(Tetris)

#set the C++ standard to be used 
set (CMAKE_CXX_STANDARD 14)

set(HEADERS 
		src/blockCLASS.h
		src/mapCLASS.h
		src/observerCLASS.h)

set(SOURCES	
		src/main.cpp)

file(GLOB DLLS
		bin/openal32.dll
		bin/sfml-graphics-2.dll
		bin/sfml-system-2.dll
		bin/sfml-window-2.dll)

include_directories(import)
link_directories(lib/SFML)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
file(COPY ${DLLS} DESTINATION ${EXECUTABLE_OUTPUT_PATH})


target_link_libraries(Tetris sfml-graphics sfml-system sfml-window sfml-main) 
