cmake_minimum_required(VERSION 3.20)
project(RPG_game LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options("/utf-8")

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} "src/map.cpp" "src/include/cute_tiled.h")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS src/)