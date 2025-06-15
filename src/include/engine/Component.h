/*
 * Component.h
 * Defines the base Component class and related types for the entity-component system.
 * Components are modular data or behavior units attached to entities, supporting
 * event handling through callbacks and unique type identification.
 */

#pragma once

#include <unordered_map>

#include "engine/ComponentMeta.h"
#include "engine/EntityRef.h"
#include "engine/Events.h"

class Component;

// Function pointer for event handling callbacks, takes a Component pointer
typedef void (*EventCallback)(Component*);

// Maps event types to their callback functions
typedef std::unordered_map<Events::EventType, EventCallback> CallbackMap;

class Component {
	public:
	// Returns the unique key identifying the component type
	virtual ComponentKey getKey() const = 0;

	// Constructor, binds component to an entity
	Component(EntityRef boundEntity);

	// Triggers an event, calling the registered callback if it exists
	void triggerEvent(Events::EventType e);

	private:
	// Reference to the entity this component is attached to
	EntityRef entity;

	// Returns the map of event callbacks, or nullptr if none
	virtual const CallbackMap* getCallbacks() const;
};

// Macro to define component key, must be included in the definition
// of every component class
#define KEYDEF(key) \
	public: \
	static constexpr ComponentKey staticGetKey() { return #key;} \
	ComponentKey getKey() const override { return staticGetKey(); }


// Simple way of ensuring that types match requirements of a component
template<class T>
concept ComponentLike = std::is_base_of_v<Component, T> && requires {
	(ComponentKey)T::staticGetKey();
};