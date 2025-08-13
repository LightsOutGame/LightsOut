/**
 * Setup.cpp
 * Contains non-generic setup code(code specific to the game, not the engine).
 */

#include "Setup.h"

#include "components/SquareRenderComponent.h"

void InitializeComponentRegistry(TylerDoesntLikeTheGameClass* game) {
	// Register components
	game->registerComponent<SquareRenderComponent>();
}

void InitializeScene(TylerDoesntLikeTheGameClass* game) {
	// Create an entity and attach components
	EntityRef e = makeEntity();

	// Add SquareRenderComponent to entity
	std::shared_ptr<Component> testComponent = std::make_shared<SquareRenderComponent>(e);
	game->components.at(testComponent->getKey()).emplace(e, testComponent);
}