#include "Component.h"

Component::Component(EntityRef boundEntity): entity(boundEntity) {}

const CallbackMap* Component::getCallbacks() const {
	return nullptr;
}

void Component::triggerEvent(Events::EventType e) {
	const CallbackMap* callbacks = getCallbacks();

	if (callbacks) {
		EventCallback func = callbacks->at(e);
		if (func) func(this);
	}
}
