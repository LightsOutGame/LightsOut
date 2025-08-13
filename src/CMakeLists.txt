# CMakeList.txt : CMake project for LightsOut, include source and define
# project specific logic here.
#

# Add source to this project's executable.


set(ENGINE_SRC "engine/EntityRef.cpp" "engine/Component.cpp" "engine/ComponentRef.cpp" "engine/AudioTrack.cpp")
set(COMPONENTS_SRC "components/SquareRenderComponent.cpp" "systems/AudioSystem.cpp")
set(SYSTEMS_SRC "systems/RenderSystem.cpp")

set(SRC ${ENGINE_SRC} ${COMPONENTS_SRC} ${SYSTEMS_SRC} "Game.cpp" "Setup.cpp" "Main.cpp" "Utils.cpp")


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


target_include_directories(LightsOut PRIVATE "include")

# Asset/Resource files
add_custom_command(
        TARGET LightsOut POST_BUILD
		COMMENT "Copying resource files: ${CMAKE_SOURCE_DIR}/src/assets -> $<TARGET_FILE_DIR:LightsOut>/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
		        ${CMAKE_SOURCE_DIR}/src/assets
				$<TARGET_FILE_DIR:LightsOut>/assets)
