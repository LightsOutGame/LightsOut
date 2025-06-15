/**
 * Game.cpp
 * Implements the core game functionality.
 * Provides SDL callback functions for initialization, event handling, game loop
 * iteration, and cleanup, along with component registration methods.
 */

#include "Game.h"

#include "engine/EntityRef.h"
#include "engine/Events.h"
#include "engine/Component.h"
#include "engine/RenderComponent.h"

template<ComponentLike Type>
void TylerDoesntLikeTheGameClass::registerComponent() {
	components.emplace(Type::staticGetKey(), std::unordered_map<EntityRef, std::shared_ptr<Component>>());

	// Component should have the render callbacks
	if (std::is_base_of_v<RenderComponent, Type>) {
		renderingComponents.push_back(Type::staticGetKey());
	}
}

template<ComponentLike Type, typename... Args>
void TylerDoesntLikeTheGameClass::registerComponent(Args... eventsToListenFor) {
	registerComponent<Type>();
	Events::registerListener(Type::staticGetKey(), eventsToListenFor...);
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