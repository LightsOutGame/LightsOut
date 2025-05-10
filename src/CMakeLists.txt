# Game sources
set(GAME_SOURCES
        MainGame.cpp
)

# Create executable as a macOS bundle
add_executable(LightsOut MACOSX_BUNDLE ${GAME_SOURCES})

# Link with SDL3
target_link_libraries(LightsOut PRIVATE SDL3::SDL3)

if(APPLE)
    # Set bundle properties
    set_target_properties(LightsOut PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.lightsout"
            MACOSX_BUNDLE_BUNDLE_NAME "LightsOut"
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    )

    # Set install RPATH for macOS bundle
    set_target_properties(LightsOut PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            INSTALL_RPATH "@executable_path/../Frameworks"
    )

    # Add post-build command to copy SDL3 into the app bundle Frameworks directory
    add_custom_command(TARGET LightsOut POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:LightsOut>/../Frameworks"
            COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:SDL3-shared>" "$<TARGET_FILE_DIR:LightsOut>/../Frameworks/"
            COMMENT "Copying SDL3 library into app bundle"
            VERBATIM
    )

    # Install target for both local installation and DMG packaging
    install(TARGETS LightsOut
            BUNDLE DESTINATION .
            COMPONENT Runtime
    )
endif()