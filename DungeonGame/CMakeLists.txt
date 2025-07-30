cmake_minimum_required(VERSION 3.12)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(DungeonGame
    main.cpp
    src/game.cpp
    src/game.h
)

target_include_directories(DungeonGame PRIVATE src)

target_link_libraries(DungeonGame PRIVATE SFML::Graphics SFML::Window SFML::System)
