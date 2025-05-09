cmake_minimum_required(VERSION 3.16)
project(LightsOut)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Configure SDL to build as a shared library on macOS
if(APPLE)
    set(SDL_FRAMEWORK OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC OFF CACHE BOOL "" FORCE)
    set(SDL_SHARED ON CACHE BOOL "" FORCE)
endif()

# Build vendored SDL3
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Add the game source
add_subdirectory(src)