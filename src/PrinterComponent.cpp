#include <iostream>

#include "PrinterComponent.h"

static void my_test_function(Component* self) {
	std::cout << "wow, cool function" << std::endl;
}

const CallbackMap* PrinterComponent::getCallbacks() const {
	static CallbackMap printerCallbacks = {
		std::pair<Events::EventType, EventCallback> { Events::PlayerUpdate, (EventCallback)my_test_function }
	};
}