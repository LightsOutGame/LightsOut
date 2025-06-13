//
// Created by Julian Reder on 6/13/25.
//

#include "SquareRenderComponent.h"
#include <SDL3/SDL.h>
#include <iostream>




SquareRenderComponent::SquareRenderComponent(EntityRef boundEntity, TylerDoesntLikeTheGameClass* game) : RenderComponent(boundEntity, game) {

}


const void SquareRenderComponent::onRender() const
{
SDL_Renderer *renderer = game->renderer;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_FRect rect = {0, 0, 100, 100};
        SDL_RenderRect(*renderer, *rect);
};