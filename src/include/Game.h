//
// Created by Julian Reder on 6/12/25.
//

#pragma once

#include <SDL3/SDL.h>

#include "ResizeMode.h"
#include "Component.h"
#include "EntityRef.h"
#include "Events.h"


class TylerDoesntLikeTheGameClass {
public:
    TylerDoesntLikeTheGameClass() = default;

    // Member variables
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* bufferTexture = nullptr;
    ResizeMode resizeMode = ResizeMode::LETTERBOX;
    bool running = true;

    std::unordered_map<ComponentKey, std::unordered_map<EntityRef, std::shared_ptr<Component>>> components;

	std::vector<ComponentKey> renderingComponents;

	void registerComponent(ComponentKey compKey);

	template<typename... Args>
	void registerComponent(ComponentKey compKey, Args... eventsToListenFor);

	template<typename... Args>
	void registerRenderingComponent(ComponentKey compKey, Args... eventsToListenFor);
};
