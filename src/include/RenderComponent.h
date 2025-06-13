#pragma once

#include "Component.h"
#include "EntityRef.h"
#include "Game.h"
#include <SDL3/SDL.h>

class RenderComponent : public Component {
public:
    RenderComponent(EntityRef boundEntity);

    virtual void onRender(SDL_Renderer* renderer) const = 0;
};
