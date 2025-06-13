#include "RendererComponent.h"
#include "TylerDoesntLikeTheGameClass.h"

RendererComponent::RendererComponent(EntityRef boundEntity, TylerDoesntLikeTheGameClass* game)
    : entity(boundEntity), game(game) {}

const CallbackMap* RendererComponent::getCallbacks() const {
	return nullptr;
}