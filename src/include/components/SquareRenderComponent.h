/*
* SquareRenderComponent.h
 * Defines the SquareRenderComponent class, the test component for
 * the RenderComponent. Renders a square shape.
 */

#pragma once

#include "engine/Component.h"
#include "engine/Renderable.h"

class SquareRenderComponent : public Component, public Renderable {
public:
    // Constructor, binds component to an entity
    SquareRenderComponent(EntityRef boundEntity);

    // Defines the unique key for this component type
    KEYDEF(square)

    // Renders the square shape using the provided SDL renderer
    void onRender(SDL_Renderer* renderer) const override;
};