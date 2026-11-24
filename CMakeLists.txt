cmake_minimum_required(VERSION 4.0)
project(Silnik2D)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/raylib)

add_executable(Silnik2D
        src/main.cpp
        src/Engine.cpp
        src/Engine.h
        src/Primitives.cpp
        src/Primitives.h
        src/Objects.cpp
        src/Objects.h
        src/Shapes.cpp
        src/Shapes.h
        src/Player.cpp
        src/Player.h
        src/BitmapHandler.cpp
        src/BitmapHandler.h
        src/Game.cpp
        src/Game.h
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2")

add_custom_command(TARGET Silnik2D POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:Silnik2D>/textures
)

target_link_libraries(Silnik2D PRIVATE raylib)