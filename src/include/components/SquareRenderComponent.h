/*
* SquareRenderComponent.h
 * Defines the SquareRenderComponent class, the test component for
 * the RenderComponent. Renders a square shape.
 */

#pragma once

#include "engine/Component.h"

class SquareRenderComponent : public Component {
public:
    // Constructor, binds component to an entity
    SquareRenderComponent(EntityRef boundEntity);

    // Defines the unique key for this component type
    KEYDEF(square)
};