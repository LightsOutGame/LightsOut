/**
 * Setup.cpp
 * Contains non-generic setup code(code specific to the game, not the engine).
 */

#include "Setup.h"

#include "components/PrinterComponent.h"
#include "components/SquareRenderComponent.h"
#include "components/AudioTestComponent.h"

void InitializeComponentRegistry(TylerDoesntLikeTheGameClass* game) {
	// Register components and their event listeners
	game->registerComponent<PrinterComponent>(Events::PlayerUpdate);
	game->registerComponent<SquareRenderComponent>();
	game->registerComponent<AudioTestComponent>(Events::PlayerUpdate);
}

void InitializeScene(TylerDoesntLikeTheGameClass* game) {
	// Create an entity and attach components
	EntityRef e = makeEntity();

	// Add PrinterComponent to entity
	std::shared_ptr<Component> testComponent = std::make_shared<PrinterComponent>(e);
	game->components.at(testComponent->getKey()).emplace(e, testComponent);

	// Add SquareRenderComponent to entity
	testComponent = std::make_shared<SquareRenderComponent>(e);
	game->components.at(testComponent->getKey()).emplace(e, testComponent);

	testComponent = std::make_shared<AudioTestComponent>(e);
	game->components.at(testComponent->getKey()).emplace(e, testComponent);
}