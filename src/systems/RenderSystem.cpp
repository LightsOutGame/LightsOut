#include "systems/RenderSystem.h"

#include "components/SquareRenderComponent.h"

namespace RenderSystem {

	void run(TylerDoesntLikeTheGameClass* game) {
		SDL_Renderer* renderer = game->renderer;

		std::unordered_map<EntityRef, std::shared_ptr<Component>>& cmptInstances = game->components.at(SquareRenderComponent::staticGetKey());
		for (auto& [entityRef, component] : cmptInstances) {

			// Set draw color to red
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			// Define square rectangle
			SDL_FRect rect = { 0, 0, 150, 100 };
			// Draw square outline
			SDL_RenderRect(renderer, &rect);
		}
	}
}