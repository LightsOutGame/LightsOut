#include "Events.h"

#include <vector>

namespace Events {

	static std::vector<ComponentKey> listeners[EventType::COUNT];
	
	void registerListener(ComponentKey listener, EventType evt) {
		listeners[evt].push_back(listener);
	}

	template<typename... Args>
	void registerListener(ComponentKey listener, EventType evt, Args... eventsToListenFor) {
		listeners[evt].push_back(listener);
		registerListener(listener, eventsToListenFor...);
	}

	std::vector<ComponentKey>& getEventListeners(EventType event) {
		return listeners[event];
	}
}