#include "Component.h"

class PrinterComponent : Component {
	private:
	const CallbackMap* getCallbacks() const override;
};
