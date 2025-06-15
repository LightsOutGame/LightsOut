/*
 * Component.cpp
 * Implements the base Component class for the entity-component system.
 * Provides functionality for initializing components, handling events, and
 * managing callback mappings for derived components.
 */

#include "engine/Component.h"

// Constructor, initializes component with a reference to the Component's Entity
Component::Component(EntityRef boundEntity): entity(boundEntity) {}


// Returns the map of event callbacks for the Component. This must be defined by the child Component class.
const CallbackMap* Component::getCallbacks() const {
	return nullptr;
}

// triggerEvent: check if the EventType is registered in the callbacks for the Component, and call the function if so
void Component::triggerEvent(Events::EventType e) {
	const CallbackMap* callbacks = getCallbacks();

	if (callbacks) { // If callbacks are even defined
        //  (i.e. if we are in a child class with at least one callback registered)
		EventCallback func = callbacks->at(e);
		if (func) func(this);
	}
}