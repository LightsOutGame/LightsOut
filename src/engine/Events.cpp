/*
* Events.cpp
 * Implements the event system functions for the entity-component system.
 * Manages registration and retrieval of component listeners for specific events.
 */

#include "engine/Events.h"

#include <vector>

namespace Events {
    // Array of listener lists for each event type
    static std::vector<ComponentKey> listeners[EventType::COUNT];

    // Registers a component as a listener for a specific event
    void registerListener(ComponentKey listener, EventType evt) {
        listeners[evt].push_back(listener);
    }

    // Registers a component as a listener for multiple events
    template<typename... Args>
    void registerListener(ComponentKey listener, EventType evt, Args... eventsToListenFor) {
        listeners[evt].push_back(listener);
        registerListener(listener, eventsToListenFor...);
    }

    // Retrieves the list of components listening for a specific event
    std::vector<ComponentKey>& getEventListeners(EventType event) {
        return listeners[event];
    }
}