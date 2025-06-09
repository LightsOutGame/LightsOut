#pragma once

#include <vector>

#include "ComponentMeta.h"

namespace Events {
	enum EventType {
		PlayerUpdate,
		EnemyUpdate,
		COUNT // Should always be placed last, not an actual event
	};

	void registerListener(EventType event, ComponentKey listener);

	std::vector<ComponentKey>& getEventListeners(EventType event);
}