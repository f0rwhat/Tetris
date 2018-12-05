cmake_minimum_required(VERSION 3.0)
project(Tetris)

#set the C++ standard to be used 
set (CMAKE_CXX_STANDARD 14)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(HEADERS 
                src/Block.h
		src/mapCLASS.h
		src/observerCLASS.h)

set(SOURCES	
                src/Block.cpp
		src/main.cpp)

include_directories(external/include)
link_directories(external/lib/SFML)

add_definitions(-DSFML_STATIC)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(Tetris sfml-graphics-s sfml-window-s sfml-system-s opengl32 freetype winmm gdi32)
