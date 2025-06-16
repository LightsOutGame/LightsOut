/*
 * RenderComponent.h
 * Defines the RenderComponent class, a different breed of component that is only used for rendering tasks.
 * Instead of implementing callbacks with getCallbacks, RenderComponents
 */

#pragma once

#include <SDL3/SDL.h>

class Renderable {
public:
    // Pure virtual function for rendering the component
    virtual void onRender(SDL_Renderer* renderer) const = 0;
};