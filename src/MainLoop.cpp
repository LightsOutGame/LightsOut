#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

// Assuming these classes are defined elsewhere (based on previous context)
enum class EventType {
    PlayerUpdate,
    EnemyUpdate
};

enum class ResizeMode {
    LETTERBOX,
    STRETCH,
    NONE
};

class Component {
public:
    virtual ~Component() = default;
    void registerEventCallback(EventType event, std::function<void(void*)> callback) {
        eventCallbacks[event] = callback;
    }
    void triggerEvent(EventType event, void* data = nullptr) {
        auto it = eventCallbacks.find(event);
        if (it != eventCallbacks.end()) {
            it->second(data);
        }
    }
    void registerRenderCallback(std::function<void(SDL_Renderer*)> callback) {
        renderCallbacks.push_back(callback);
    }
    void draw(SDL_Renderer* renderer) {
        for (const auto& callback : renderCallbacks) {
            callback(renderer);
        }
    }

private:
    std::unordered_map<EventType, std::function<void(void*)>> eventCallbacks;
    std::vector<std::function<void(SDL_Renderer*)>> renderCallbacks;
};

class Entity {
public:
    bool isAlive() const { return alive; }
    void destroy() { alive = false; }
private:
    bool alive = true;
};

// Game class to hold state
class Game {
public:
    Game() = default;

    // Member variables
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* bufferTexture = nullptr;
    ResizeMode resizeMode = ResizeMode::LETTERBOX;
    bool running = true;

    std::unordered_map<std::string, std::pair<std::shared_ptr<Entity>, std::shared_ptr<Component>>> components;
};

// SDL callback functions

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    *appstate = new Game();
    Game* game = static_cast<Game*>(*appstate);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    game->window = SDL_CreateWindow("Game", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!game->window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    game->renderer = SDL_CreateRenderer(game->window, "Lights Out");
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

    // Register some components and callbacks
    auto entity = std::make_shared<Entity>();
    auto component = std::make_shared<Component>();
    game->components["component1"] = {entity, component};
    component->registerEventCallback(EventType::PlayerUpdate, [](void* data) {
        SDL_Log("PlayerUpdate callback triggered");
    });
    component->registerRenderCallback([](SDL_Renderer* r) {
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        SDL_FRect fRect = {100.0f, 100.0f, 50.0f, 50.0f};
        SDL_RenderFillRect(r, &fRect);
    });

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    Game* game = static_cast<Game*>(appstate);
    if (event->type == SDL_EVENT_QUIT) {
        game->running = false;
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    Game* game = static_cast<Game*>(appstate);
    if (!game->running) return SDL_APP_SUCCESS;

    // Game Logic: Trigger component callbacks
    for (auto it = game->components.begin(); it != game->components.end();) {
        auto& [key, pair] = *it;
        auto& [entity, component] = pair;
        if (!entity->isAlive()) {
            game->components.erase(it++); // Lazy destruction
        } else {
            component->triggerEvent(EventType::PlayerUpdate);
            ++it;
        }
    }

    // Rendering
    SDL_SetRenderTarget(game->renderer, game->bufferTexture);
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    for (const auto& [key, pair] : game->components) {
        auto& [entity, component] = pair;
        if (entity->isAlive()) {
            component->draw(game->renderer);
        }
    }

    // Handle Window Resize Scaling (idk if this works?)
    SDL_SetRenderTarget(game->renderer, nullptr);
    int windowWidth, windowHeight;
    SDL_GetWindowSize(game->window, &windowWidth, &windowHeight);

    SDL_FRect dstRect;
    switch (game->resizeMode) {
        case ResizeMode::LETTERBOX: {
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
            dstRect.x = 0;
            dstRect.y = 0;
            dstRect.w = windowWidth;
            dstRect.h = windowHeight;
            break;
        }
        case ResizeMode::NONE: {
            dstRect.x = 0;
            dstRect.y = 0;
            dstRect.w = 800;
            dstRect.h = 600;
            break;
        }
    }

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);
    SDL_RenderTexture(game->renderer, game->bufferTexture, nullptr, &dstRect);
    SDL_RenderPresent(game->renderer);

    SDL_SetRenderTarget(game->renderer, game->bufferTexture);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate) {
    Game* game = static_cast<Game*>(appstate);
    if (!game) return;
    if (game->bufferTexture) SDL_DestroyTexture(game->bufferTexture);
    if (game->renderer) SDL_DestroyRenderer(game->renderer);
    if (game->window) SDL_DestroyWindow(game->window);
    SDL_Quit();
    delete game;
}