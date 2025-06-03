# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(SRC "MainGame.cpp"
	"Component.cpp"
	"EntityRef.cpp"
	"Events.cpp"
	)
if (WIN32)
	add_executable (LightsOut WIN32 ${SRC})
elseif (APPLE)
	add_executable (LightsOut MACOSX_BUNDLE ${SRC})
else()
	add_executable (LightsOut ${SRC})
endif()
	
# Link to the actual SDL3 library.
target_link_libraries(LightsOut PRIVATE SDL3::SDL3)

target_include_directories(LightsOut PRIVATE ""include"")
