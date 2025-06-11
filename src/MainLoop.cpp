#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include "EntityRef.h"
#include "Component.h"
#include "Events.h"




enum class ResizeMode {
    LETTERBOX,
    STRETCH,
    NONE
};



class TylerDoesntLikeTheGameClass {
public:
    TylerDoesntLikeTheGameClass() = default;

    // Member variables
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* bufferTexture = nullptr;
    ResizeMode resizeMode = ResizeMode::LETTERBOX;
    bool running = true;

    std::unordered_map<ComponentKey, std::unordered_map<EntityRef, Component>> components;

};


// SDL callback functions

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    *appstate = new TylerDoesntLikeTheGameClass();
    TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(*appstate);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    game->window = SDL_CreateWindow("Game", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!game->window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    game->renderer = SDL_CreateRenderer(game->window, NULL);
    if (!game->renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
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
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(appstate);
    if (event->type == SDL_EVENT_QUIT) {
        game->running = false;
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(appstate);
    if (!game->running) return SDL_APP_SUCCESS;


    for (int i=0; i < Events::EventType::COUNT; i++) {
        // not poetry
        Events::EventType eventType = static_cast<Events::EventType>(i);
        std::vector<ComponentKey>& listeningComponents = Events::getEventListeners(eventType);
        for (const ComponentKey& key : listeningComponents) {
            std::unordered_map<EntityRef, Component>& entities = game->components.at(key);
            for (auto& [entityRef, component] : entities) {
                component.triggerEvent(eventType);
            }
        }
    }

    // // Rendering
    // SDL_SetRenderTarget(game->renderer, game->bufferTexture);
    // SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    // SDL_RenderClear(game->renderer);
    //
    // for (const auto& [key, pair] : game->components) {
    //     auto& [entity, component] = pair;
    //     if (entity->isAlive()) {
    //         component->draw(game->renderer);
    //     }
    // }
    //
    // // Handle Window Resize Scaling (idk if this works?)
    // SDL_SetRenderTarget(game->renderer, nullptr);
    // int windowWidth, windowHeight;
    // SDL_GetWindowSize(game->window, &windowWidth, &windowHeight);
    //
    // SDL_FRect dstRect;
    // switch (game->resizeMode) {
    //     case ResizeMode::LETTERBOX: {
    //         float aspectRatio = 800.0f / 600.0f;
    //         float windowAspect = static_cast<float>(windowWidth) / windowHeight;
    //         if (windowAspect > aspectRatio) {
    //             dstRect.h = windowHeight;
    //             dstRect.w = static_cast<int>(windowHeight * aspectRatio);
    //             dstRect.x = (windowWidth - dstRect.w) / 2;
    //             dstRect.y = 0;
    //         } else {
    //             dstRect.w = windowWidth;
    //             dstRect.h = static_cast<int>(windowWidth / aspectRatio);
    //             dstRect.x = 0;
    //             dstRect.y = (windowHeight - dstRect.h) / 2;
    //         }
    //         break;
    //     }
    //     case ResizeMode::STRETCH: {
    //         dstRect.x = 0;
    //         dstRect.y = 0;
    //         dstRect.w = windowWidth;
    //         dstRect.h = windowHeight;
    //         break;
    //     }
    //     case ResizeMode::NONE: {
    //         dstRect.x = 0;
    //         dstRect.y = 0;
    //         dstRect.w = 800;
    //         dstRect.h = 600;
    //         break;
    //     }
    // }
    //
    // SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    // SDL_RenderClear(game->renderer);
    // SDL_RenderTexture(game->renderer, game->bufferTexture, nullptr, &dstRect);
    // SDL_RenderPresent(game->renderer);
    //
    // SDL_SetRenderTarget(game->renderer, game->bufferTexture);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    TylerDoesntLikeTheGameClass* game = static_cast<TylerDoesntLikeTheGameClass*>(appstate);
    if (!game) return;
    if (game->bufferTexture) SDL_DestroyTexture(game->bufferTexture);
    if (game->renderer) SDL_DestroyRenderer(game->renderer);
    if (game->window) SDL_DestroyWindow(game->window);
    SDL_Quit();
    delete game;
}