# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

set(SOURCE_FILES "MainGame.cpp")
# Add source to this project's executable.
if (WIN32)
	# NOTE: I re-enabled the command line for the reflection testing. ADD BACK THE WIN32 FLAG LATER
	add_executable (LightsOut ${SOURCE_FILES})
elseif (APPLE)
	add_executable (LightsOut MACOSX_BUNDLE ${SOURCE_FILES})
else()
	add_executable (LightsOut ${SOURCE_FILES})
endif()

target_compile_features(LightsOut PUBLIC cxx_std_20)
	
# Link to the actual SDL3 library.
target_link_libraries(LightsOut PRIVATE SDL3::SDL3)
