/*
* RenderComponent.h
 * Defines the RenderComponent class, a different breed of component that is only used for rendering tasks.
 * Instead of implementing callbacks with getCallbacks, RenderComponents
 */

#pragma once

#include "Component.h"
#include "EntityRef.h"
#include "Game.h"
#include <SDL3/SDL.h>

class RenderComponent : public Component {
public:
    // Constructor, binds component to an entity
    RenderComponent(EntityRef boundEntity);

    // Pure virtual function for rendering the component
    virtual void onRender(SDL_Renderer* renderer) const = 0;
};