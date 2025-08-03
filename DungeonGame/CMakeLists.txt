cmake_minimum_required(VERSION 3.12)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 3
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Add tmxlite as a subdirectory
add_subdirectory(external/tmxlite)

# Your executable
add_executable(DungeonGame
    main.cpp
    src/Game.cpp
    src/TileMap.cpp
 "src/GameObject.h" "src/GameObject.cpp" "src/Player.h" "src/Player.cpp" "src/Animation.h" "src/Animation.cpp")

target_include_directories(DungeonGame PRIVATE src)

# Link libraries
target_link_libraries(DungeonGame 
    PRIVATE SFML::Graphics SFML::Window SFML::System tmxlite
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)