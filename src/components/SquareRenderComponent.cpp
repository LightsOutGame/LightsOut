/*
 * SquareRenderComponent.cpp
 * Implements the SquareRenderComponent class: the test RenderComponent
 * Provides rendering functionality to draw a red square using SDL.
 */


#include "components/SquareRenderComponent.h"

// Constructor, initializes component
SquareRenderComponent::SquareRenderComponent(EntityRef boundEntity) : RenderComponent(boundEntity) {

}

// Renders a red square at position (0,0) with size 100x100 (scaling will apply tho)
void SquareRenderComponent::onRender(SDL_Renderer* renderer) const
{
	// Set draw color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// Define square rectangle
    SDL_FRect rect = {0, 0, 150, 100};
	// Draw square outline
    SDL_RenderRect(renderer, &rect);
};