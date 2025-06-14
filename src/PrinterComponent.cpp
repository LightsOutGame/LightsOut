/*
 * PrinterComponent.cpp
 * Implements the test component PrinterComponent
 * Provides event callback registration for printing "wow, cool function"
 */

#include <iostream>

#include "PrinterComponent.h"

// Callback function
static void my_test_function(Component* self) {
	std::cout << "wow, cool function" << std::endl;
}

// Initialize PrinterComponent
PrinterComponent::PrinterComponent(EntityRef boundEntity) : Component(boundEntity) {

}

// Returns the map of event callbacks for this component (PlayerUpdate: my_test_function)
const CallbackMap* PrinterComponent::getCallbacks() const {
	// Static map of event callbacks
	static CallbackMap printerCallbacks = {
		{ Events::PlayerUpdate, &my_test_function }
	};

	return &printerCallbacks;
}