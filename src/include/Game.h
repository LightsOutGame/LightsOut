/**
 * Game.h
 * Defines the TylerDoesntLikeTheGameClass, which contains references to the window, renderer, and texture of the game.
 * It also handles component registration for rendering and event handling.
 */


#pragma once

#include <SDL3/SDL.h>

#include "engine/ResizeMode.h"
#include "engine/Component.h"
#include "engine/EntityRef.h"
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

    // Registers a component type in the system
	template <ComponentLike Type>
    void registerComponent();
 
	// Retrieves the component of the given type attached to the given entity.
	// If none exists, returns an empty ComponentRef.
	template<ComponentLike Type>
    ComponentRef getComponent(EntityRef entity);
};

// TEMPLATE DEFINITIONS
template<ComponentLike Type>
void TylerDoesntLikeTheGameClass::registerComponent() {
	components.emplace(Type::staticGetKey(), std::unordered_map<EntityRef, std::shared_ptr<Component>>());
}

template<ComponentLike Type>
ComponentRef TylerDoesntLikeTheGameClass::getComponent(EntityRef entity) {
	ComponentRef result = {};
	result.entity = entity;

	// Find the map for the given ComponentKey
	auto type_it = components.find(Type::staticGetKey());
	if (type_it != components.end()) {
		// Find the component for the given EntityRef
		auto entity_it = type_it->second.find(entity);
		if (entity_it != type_it->second.end()) {
			// Assign the shared_ptr to a weak_ptr
			result.ptr = entity_it->second;
		}
		// If not found, ptr remains an empty weak_ptr
	}
	// If type not found, ptr remains an empty weak_ptr
	return result;
}
