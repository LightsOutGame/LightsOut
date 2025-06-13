#pragma once

#include <vector>

#include "ComponentMeta.h"

namespace Events {
	enum EventType {
		PlayerUpdate,
		EnemyUpdate,
		COUNT // Should always be placed last, not an actual event
	};

	void registerListener(ComponentKey listener, EventType evt);

	template<typename... Args>
	void registerListener(ComponentKey listener, EventType evt, Args... eventsToListenFor);

	std::vector<ComponentKey>& getEventListeners(EventType event);
}