/*
* ResizeMode.h
 * Defines the ResizeMode enum class for specifying window scaling behavior.
 * Note that we probably want to force an aspect ratio, so this might be changed
 */


#pragma once

// Enum class for specifying window resize modes
enum class ResizeMode {
    LETTERBOX,  // Maintain aspect ratio
    STRETCH,    // Stretch to fill window, ignoring aspect ratio
    NONE        // No scaling applied
};

