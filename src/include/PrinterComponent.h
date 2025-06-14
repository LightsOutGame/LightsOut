/*
 * PrinterComponent.h
 * Defines the PrinterComponent class, a test component that does nothing but spams "ok, cool function"
 */

#include "Component.h"

class PrinterComponent : public Component {
	public:
	// Constructor, binds component to an entity
	PrinterComponent(EntityRef boundEntity);

	// Defines the unique key for this component type
	KEYDEF(printer)

	private:
	// Returns the map of event callbacks for this component
	const CallbackMap* getCallbacks() const override;
};