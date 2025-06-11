#pragma once

#include <unordered_map>

#include "ComponentMeta.h"
#include "EntityRef.h"
#include "Events.h"

class Component;

typedef void (*EventCallback)(Component*);

typedef std::unordered_map<Events::EventType, EventCallback> CallbackMap;

class Component {
	public:
	virtual ComponentKey getKey() const = 0; // Need this so each component can tell you it's type

	Component(EntityRef boundEntity);

	void triggerEvent(Events::EventType e);

	private:
	EntityRef entity;

	virtual const CallbackMap* getCallbacks() const;
};

// NEED TO INCLUDE THIS IN EVERY COMPONENT DEFINITION
#define KEYDEF(key) \
	public: \
	static constexpr ComponentKey staticGetKey() { return #key ## ;} \
	ComponentKey Component::getKey() const override { return staticGetKey(); }
