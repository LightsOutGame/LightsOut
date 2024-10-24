# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LightsOut "LightsOut.cpp" "LightsOut.h" "MainGame.cpp" "MainGame.h")

target_link_libraries(LightsOut SDL2)
target_include_directories(LightsOut PUBLIC "${PROJECT_SOURCE_DIR}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LightsOut PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
