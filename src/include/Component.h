#pragma once

#include <unordered_map>

#include "ComponentMeta.h"
#include "EntityRef.h"
#include "Events.h"

typedef std::unordered_map<Events::EventType, Events::EventCallback> CallbackMap;

class Component {
	public:
	const static ComponentKey key;

	void triggerEvent(Events::EventType e);

	private:
	EntityRef entity;

	virtual const CallbackMap* getCallbacks() const;
};
