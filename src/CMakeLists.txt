# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(SRC "MainLoop.cpp"
	"EntityRef.cpp"
	"Events.cpp"
	"Component.cpp"
	"ComponentRef.cpp"
    "PrinterComponent.cpp")


if (WIN32)
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
