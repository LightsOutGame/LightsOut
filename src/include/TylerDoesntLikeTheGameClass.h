//
// Created by Julian Reder on 6/12/25.
//

#pragma once

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

};

