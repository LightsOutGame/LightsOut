# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

# Add source to this project's executable.
if (WIN32)
	add_executable (LightsOut WIN32 "MainGame.cpp")
elseif (APPLE)
	add_executable (LightsOut MACOSX_BUNDLE "MainGame.cpp")
else()
	add_executable (LightsOut "MainGame.cpp")
endif()
	
# Link to the actual SDL3 library.
target_link_libraries(LightsOut PRIVATE SDL3::SDL3)
