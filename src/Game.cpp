/*
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


// COMPONENT MANAGEMENT
// Registers a component type in the system
template<ComponentLike T>
void TylerDoesntLikeTheGameClass::registerComponent() {
	components.emplace(T::staticGetKey(), std::unordered_map<EntityRef, std::shared_ptr<Component>>());

	// Component should have the render callbacks
	if (std::is_base_of_v<RenderComponent, T>) {
		renderingComponents.push_back(T::staticGetKey());
	}
}

// Registers a component type with associated events to listen for
template<ComponentLike T, typename... Args>
void TylerDoesntLikeTheGameClass::registerComponent(Args... eventsToListenFor) {
	registerComponent<T>();
	Events::registerListener(T::staticGetKey(), eventsToListenFor...);
}