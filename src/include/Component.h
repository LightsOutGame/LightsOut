#pragma once

#include <unordered_map>

#include "ComponentMeta.h"
#include "EntityRef.h"
#include "Events.h"


typedef void (*EventCallback)(Component* self);

typedef std::unordered_map<Events::EventType, EventCallback> CallbackMap;

class Component {
	public:
	const static ComponentKey key;

	Component(EntityRef boundEntity);

	void triggerEvent(Events::EventType e);

	private:
	EntityRef entity;

	virtual const CallbackMap* getCallbacks() const;
};
