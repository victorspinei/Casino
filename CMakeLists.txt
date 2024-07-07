cmake_minimum_required(VERSION 3.29)
project(Casino)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer")
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Casino src/main.cpp
        src/Casino.h
        src/Casino.cpp
        src/TextureManager.cpp)

