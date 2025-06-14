/*
 * Events.h
 * Defines the event system for managing event types and listeners in the
 * entity-component system. Provides functionality for registering components
 * as listeners for specific events and retrieving listeners for events.
 */

#pragma once

#include <vector>

#include "ComponentMeta.h"

namespace Events {
	// Enumeration of event types in the system
	enum EventType {
		PlayerUpdate,  // Event for player-related updates
		EnemyUpdate,   // Event for enemy-related updates
		COUNT          // Placeholder for event count, not an actual event
	};

	// Registers a component as a listener for a specific event
	void registerListener(ComponentKey listener, EventType evt);

	// Registers a component as a listener for multiple events
	template<typename... Args>
	void registerListener(ComponentKey listener, EventType evt, Args... eventsToListenFor);

	// Retrieves the list of components listening for a specific event
	std::vector<ComponentKey>& getEventListeners(EventType event);
}