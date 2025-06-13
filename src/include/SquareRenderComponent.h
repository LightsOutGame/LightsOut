//
// Created by Julian Reder on 6/13/25.
//

#pragma once

#include "RenderComponent.h"

class SquareRenderComponent : public RenderComponent {
    public:
    SquareRenderComponent(EntityRef boundEntity);

    KEYDEF(square)

    void onRender(SDL_Renderer* renderer) const override;




};


