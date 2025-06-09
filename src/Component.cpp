#include "Component.h"

Component::Component(EntityRef boundEntity) {
	entity = boundEntity;
}

const CallbackMap* Component::getCallbacks() const {
	return nullptr;
}

void Component::triggerEvent(Events::EventType e) {
	const CallbackMap* callbacks = getCallbacks();

	if (callbacks) {
		Events::EventCallback c = callbacks->at(e);
		if (c) c();
	}
}
