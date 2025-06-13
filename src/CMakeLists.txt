# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(SRC "Game.cpp"
	"EntityRef.cpp"
	"Events.cpp"
	"Component.cpp"
	"ComponentRef.cpp"
	"RenderComponent.cpp"
    "PrinterComponent.cpp"
	"SquareRenderComponent.cpp")


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

# Link to the actual SDL3 library.
target_link_libraries(LightsOut PRIVATE SDL3::SDL3)

target_include_directories(LightsOut PRIVATE "include")
