/*
* Game.h
 * Defines the TylerDoesntLikeTheGameClass, which contains references to the window, renderer, and texture of the game.
 * It also handles component registration for rendering and event handling.
 */


#pragma once

#include <SDL3/SDL.h>

#include "ResizeMode.h"
#include "Component.h"
#include "EntityRef.h"
#include "Events.h"

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
    void registerComponent(ComponentKey compKey);

    // Registers a component type with associated events to listen for
    template<typename... Args>
    void registerComponent(ComponentKey compKey, Args... eventsToListenFor);

    // Registers a component type as a rendering component with associated events
    template<typename... Args>
    void registerRenderingComponent(ComponentKey compKey, Args... eventsToListenFor);
};