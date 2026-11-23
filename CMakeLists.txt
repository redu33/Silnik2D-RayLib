cmake_minimum_required(VERSION 4.0)
project(Silnk2D)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/raylib)

add_executable(Silnk2D src/main.cpp
        src/Engine.cpp
        src/Engine.h
        src/Primitives.cpp
        src/Primitives.h
        src/Objects.h
        src/Shapes.cpp
        src/Shapes.h
        src/Player.cpp
        src/Player.h
        src/Objects.cpp
        src/BitmapHandler.cpp
        src/BitmapHandler.h
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2")

target_link_libraries(Silnk2D PRIVATE raylib)