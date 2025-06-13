//
// Created by Julian Reder on 6/13/25.
//

#include "SquareRenderComponent.h"

SquareRenderComponent::SquareRenderComponent(EntityRef boundEntity) : RenderComponent(boundEntity) {

}

void SquareRenderComponent::onRender(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect rect = {0, 0, 100, 100};
    SDL_RenderRect(renderer, &rect);
};