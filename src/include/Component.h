#pragma once

#include <unordered_map>

#include "ComponentMeta.h"
#include "EntityRef.h"
#include "Events.h"

class Component {
	public:
	const static ComponentKey key;

	private:
	EntityRef entity;

	std::unordered_map<Events::EventType, Events::EventCallback> callbacks;

	void registerEventCallback(Events::EventType event, Events::EventCallback callback);

	virtual void init() = 0;
};
