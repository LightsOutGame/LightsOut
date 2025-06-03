#include "Component.h"

void Component::registerEventCallback(Events::EventType event, Events::EventCallback callback) {
	callbacks.emplace(event, callback);
}
