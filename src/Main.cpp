/** 
 * Main.cpp
 * Contains initialization of all subsystems, definitions for the SDL callbacks
 * main loop logic, and exit handling.
 */ 

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>

#include "Game.h"
#include "Setup.h"

// Game Systems
#include "systems/RenderSystem.h"
#include "systems/AudioSystem.h"

// SDL callback functions

// Initializes the game and SDL resources
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	// Create game instance
	*appstate = new TylerDoesntLikeTheGameClass();
	TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(*appstate);

	// Initialize SDL video subsystem
	if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("SDL initialization failed: %s", SDL_GetError());
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

	// Initialize Audio system
	AudioSystem::start(0.1f);

	InitializeComponentRegistry(game);
	InitializeScene(game);

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

	// Process systems
	// empty for now because we have none

	// Rendering
	// Set render target to buffer texture
	SDL_SetRenderTarget(game->renderer, game->bufferTexture);
	// Clear buffer with black
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	// Render scene to the buffer
	RenderSystem::run(game);

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
			}
			else {
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

	// Stop extra threads
	AudioSystem::cleanup();

	// Destroy SDL resources
	if (game->bufferTexture) SDL_DestroyTexture(game->bufferTexture);
	if (game->renderer) SDL_DestroyRenderer(game->renderer);
	if (game->window) SDL_DestroyWindow(game->window);
	SDL_Quit();

	// Delete game instance
	delete game;
}