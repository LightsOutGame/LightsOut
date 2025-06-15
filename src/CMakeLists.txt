# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

# Add source to this project's executable.


file(GLOB_RECURSE ENGINE_SRC ${CMAKE_SOURCE_DIR}/src/engine/*.cpp)
file(GLOB_RECURSE COMPONENTS_SRC ${CMAKE_SOURCE_DIR}/src/components/*.cpp)
file(GLOB_RECURSE PHYSICS_SRC ${CMAKE_SOURCE_DIR}/src/physics/*.cpp)

set(SRC ${ENGINE_SRC} ${COMPONENTS_SRC} ${PHYSICS_SRC} "Game.cpp")


if (WIN32)
	# for later: Add the WIN32 flag back to this add_executable() call.
	# it removes the terminal window for Windows executables.
	# We're keeping it now for testing purposes.
	add_executable (LightsOut ${SRC})
elseif (APPLE)
	add_executable (LightsOut MACOSX_BUNDLE ${SRC})
else()
	add_executable (LightsOut ${SRC})
endif()

# Set C++ standard to 20
target_compile_features(LightsOut PUBLIC cxx_std_20)

# Link to the libraries used.
target_link_libraries(LightsOut PRIVATE SDL3::SDL3)
target_link_libraries(LightsOut PRIVATE SDL3_ttf::SDL3_ttf)
target_link_libraries(LightsOut PRIVATE SDL3_mixer::SDL3_mixer)


target_include_directories(LightsOut PRIVATE "include")
