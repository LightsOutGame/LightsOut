/*
* Game.h
 * Defines the TylerDoesntLikeTheGameClass, which contains references to the window, renderer, and texture of the game.
 * It also handles component registration for rendering and event handling.
 */


#pragma once

#include <SDL3/SDL.h>

#include "engine/ResizeMode.h"
#include "engine/Component.h"
#include "engine/EntityRef.h"
#include "engine/Events.h"
#include "engine/ComponentRef.h"


class TylerDoesntLikeTheGameClass {
public:
    // Default constructor
    TylerDoesntLikeTheGameClass() = default;

    // Member variables
	
    // Pointer to the SDL window
    SDL_Window* window = nullptr;
    // Pointer to the SDL renderer
    SDL_Renderer* renderer = nullptr;
    // Pointer to the buffer texture for rendering
    SDL_Texture* bufferTexture = nullptr;
    // Resize mode for handling window scaling
    ResizeMode resizeMode = ResizeMode::LETTERBOX;
    // Flag indicating if the game is running
    bool running = true;

    // Map of component keys to entity-component pairs
    std::unordered_map<ComponentKey, std::unordered_map<EntityRef, std::shared_ptr<Component>>> components;

    // List of component keys for components that handle rendering
    std::vector<ComponentKey> renderingComponents;

    // Registers a component type in the system
	template <ComponentLike Type>
    void registerComponent();

	// Registers a component type with associated events to listen for
    template<ComponentLike Type, typename... Args>
    void registerComponent(Args... eventsToListenFor);
 
	// Retrieves the component of the given type attached to the given entity.
	// If none exists, returns an empty ComponentRef.
	template<ComponentLike Type>
    ComponentRef getComponent(EntityRef entity);
};
