
cmake_minimum_required(VERSION 3.16)
project(LightsOut VERSION 1.0.0)

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

# CPack configuration for DMG creation on macOS
if(APPLE)
    # Set CPack variables
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_PACKAGE_NAME "LightsOut")
    set(CPACK_PACKAGE_VENDOR "Bagel Development")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "LightsOut Game")
    set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
#    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/src/AppIcon.icns") # Create or add this icon file

    # Customize DMG look (optional)
    set(CPACK_DMG_VOLUME_NAME "${CPACK_PACKAGE_NAME}")
    set(CPACK_DMG_FORMAT "UDBZ") # Use bzip2 compression
#    set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_SOURCE_DIR}/src/DMGBackground.png") # Create or add this image

    # Include Applications directory symlink in the DMG
#    set(CPACK_DMG_DS_STORE_SETUP_SCRIPT "${CMAKE_SOURCE_DIR}/src/DMGSetup.scpt") # Optional

    # Only include the macOS app bundle
    set(CPACK_COMPONENTS_ALL Runtime)

    # Add a custom target for creating the DMG
    add_custom_target(DMG
            COMMAND ${CMAKE_COMMAND} --build . --target package
            DEPENDS LightsOut
            COMMENT "Building DMG installer..."
            VERBATIM
    )

    # Include CPack at the end of the file
    include(CPack)
endif()