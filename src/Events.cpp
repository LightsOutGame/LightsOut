#include "Events.h"

#include <vector>

namespace Events {

	static std::vector<ComponentKey> listeners[EventType::COUNT];
	
	void registerListener(EventType event, ComponentKey listener) {
		listeners[event].push_back(listener);
	}

	std::vector<ComponentKey>& getEventListeners(EventType event) {
		return listeners[event];
	}
}