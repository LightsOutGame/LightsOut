#pragma once

#include "Component.h"
#include "EntityRef.h"
#include "Events.h"
#include <SDL.h>

class TylerDoesntLikeTheGameClass;

class RendererComponent : public Component {
public:
    RendererComponent(EntityRef boundEntity, TylerDoesntLikeTheGameClass* game);

    virtual void onRender(TylerDoesntLikeTheGameClass* game) const = 0;

private:
    TylerDoesntLikeTheGameClass* game; // Reference to game for accessing renderer
};
