/*
 * Game.cpp
 * Implements the core game functionality.
 * Provides SDL callback functions for initialization, event handling, game loop
 * iteration, and cleanup, along with component registration methods.
 */

#define SDL_MAIN_USE_CALLBACKS 1

#include "Game.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <iostream>

#include "engine/EntityRef.h"
#include "engine/Events.h"
#include "engine/Component.h"
#include "engine/RenderComponent.h"

#include "components/PrinterComponent.h"
#include "components/SquareRenderComponent.h"
#include "components/AudioTestComponent.h"

// COMPONENT MANAGEMENT
// Registers a component type in the system
void TylerDoesntLikeTheGameClass::registerComponent(ComponentKey compKey) {
	components.emplace(compKey, std::unordered_map<EntityRef, std::shared_ptr<Component>>());
}

// Registers a component type with associated events to listen for
template<typename... Args>
void TylerDoesntLikeTheGameClass::registerComponent(ComponentKey compKey, Args... eventsToListenFor) {
	components.emplace(compKey, std::unordered_map<EntityRef, std::shared_ptr<Component>>());
	Events::registerListener(compKey, eventsToListenFor...);
}

// Registers a component type as a rendering component with associated events
template<typename... Args>
void TylerDoesntLikeTheGameClass::registerRenderingComponent(ComponentKey compKey, Args... eventsToListenFor) {
	renderingComponents.push_back(compKey);
	registerComponent(compKey, eventsToListenFor...);
}

// SDL callback functions

// Initializes the game and SDL resources
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	// Create game instance
	*appstate = new TylerDoesntLikeTheGameClass();
	TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(*appstate);

	// Initialize SDL video subsystem
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL initialization failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!Mix_Init(MIX_INIT_MP3)) { // Init MP3 functionality (for now)
		std::cerr << "Mix_Init failed: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return SDL_APP_FAILURE;

	}

	SDL_AudioSpec audioSpec = {};
	audioSpec.freq = 44100;
	audioSpec.format = SDL_AUDIO_F32;
	audioSpec.channels = 2;
	// audioSpec.samples = 2048;

	// Open audio device (no clue what these arguments mean :P)
	if (!Mix_OpenAudio(0, &audioSpec)) {
		std::cerr << "Mix_OpenAudio failed: " << SDL_GetError() << std::endl;
		Mix_Quit();
		SDL_Quit();
		return SDL_APP_FAILURE;
	}

	// Create window
	game->window = SDL_CreateWindow("Game", 800, 600, SDL_WINDOW_RESIZABLE);
	if (!game->window) {
		SDL_Log("Window creation failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
  // Create renderer
	game->renderer = SDL_CreateRenderer(game->window, NULL);
	if (!game->renderer) {
		SDL_Log("Renderer creation failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	// Create buffer texture for rendering
	game->bufferTexture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, 800, 600);
	if (!game->bufferTexture) {
		SDL_Log("Texture creation failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// // Register some components and callbacks
	// auto entity = EntityRef();
	// auto component = std::make_shared<Component>();
	// game->components["component1"] = {entity, component};
	// component->registerEventCallback(Events::EventType::PlayerUpdate, [](void* data) {
	//     SDL_Log("PlayerUpdate callback triggered");
	// });
	// component->registerRenderCallback([](SDL_Renderer* r) {
	//     SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
	//     SDL_FRect fRect = {100.0f, 100.0f, 50.0f, 50.0f};
	//     SDL_RenderFillRect(r, &fRect);
	// });
	//

	// Register components and their event listeners
	game->registerComponent(PrinterComponent::staticGetKey(), Events::PlayerUpdate);
	game->registerRenderingComponent(SquareRenderComponent::staticGetKey());
	game->registerComponent(AudioTestComponent::staticGetKey(), Events::PlayerUpdate);

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


	return SDL_APP_CONTINUE;
}

// Handles SDL events
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(appstate);
	// Handle quit event
	if (event->type == SDL_EVENT_QUIT) {
		game->running = false;
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

// Main game loop iteration
SDL_AppResult SDL_AppIterate(void* appstate) {
	TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(appstate);
	// Exit if game is not running
	if (!game->running) return SDL_APP_SUCCESS;

	// Process all events
	for (int i = 0; i < Events::EventType::COUNT; i++) {
		Events::EventType eventType = static_cast<Events::EventType>(i);
		std::vector<ComponentKey>& listeningComponents = Events::getEventListeners(eventType);
		// Trigger events for all listening components
		for (const ComponentKey& key : listeningComponents) {
			std::unordered_map<EntityRef, std::shared_ptr<Component>>& cmptInstances = game->components.at(key);
			for (auto& [entityRef, component] : cmptInstances) {
				component->triggerEvent(eventType);
			}
		}
	}

	// Rendering
	// Set render target to buffer texture
	SDL_SetRenderTarget(game->renderer, game->bufferTexture);
	// Clear buffer with black
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	// Render all rendering components
	for (const ComponentKey& key : game->renderingComponents) {
		std::unordered_map<EntityRef, std::shared_ptr<Component>>& cmptInstances = game->components.at(key);
		for (auto& [entityRef, component] : cmptInstances) {
			// Cast to RenderComponent for rendering
			RenderComponent* r = (RenderComponent*) component.get();
			r->onRender(game->renderer);
		}
	}

	// Handle window resize scaling
	SDL_SetRenderTarget(game->renderer, nullptr);
	int windowWidth, windowHeight;
	SDL_GetWindowSize(game->window, &windowWidth, &windowHeight);

	SDL_FRect dstRect;
	switch (game->resizeMode) {
		case ResizeMode::LETTERBOX: {
			// Maintain aspect ratio with letterboxing
			float aspectRatio = 800.0f / 600.0f;
			float windowAspect = static_cast<float>(windowWidth) / windowHeight;
			if (windowAspect > aspectRatio) {
				dstRect.h = windowHeight;
				dstRect.w = static_cast<int>(windowHeight * aspectRatio);
				dstRect.x = (windowWidth - dstRect.w) / 2;
				dstRect.y = 0;
			} else {
				dstRect.w = windowWidth;
				dstRect.h = static_cast<int>(windowWidth / aspectRatio);
				dstRect.x = 0;
				dstRect.y = (windowHeight - dstRect.h) / 2;
			}
			break;
		}
		case ResizeMode::STRETCH: {
			// Stretch to fill window
			dstRect.x = 0;
			dstRect.y = 0;
			dstRect.w = windowWidth;
			dstRect.h = windowHeight;
			break;
		}
		case ResizeMode::NONE: {
			// Use fixed size
			dstRect.x = 0;
			dstRect.y = 0;
			dstRect.w = 800;
			dstRect.h = 600;
			break;
		}
	}

	// Clear window and render buffer texture
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	SDL_RenderTexture(game->renderer, game->bufferTexture, nullptr, &dstRect);
	SDL_RenderPresent(game->renderer);

	// Reset render target to buffer
	SDL_SetRenderTarget(game->renderer, game->bufferTexture);
	return SDL_APP_CONTINUE;
}

// Cleans up game resources
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(appstate);
	if (!game) return;
	// Destroy SDL resources
	if (game->bufferTexture) SDL_DestroyTexture(game->bufferTexture);
	if (game->renderer) SDL_DestroyRenderer(game->renderer);
	if (game->window) SDL_DestroyWindow(game->window);
	SDL_Quit();
	// Delete game instance
	delete game;
}