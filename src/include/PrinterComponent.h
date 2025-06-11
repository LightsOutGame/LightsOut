#include "Component.h"

class PrinterComponent : public Component {
	public:
	PrinterComponent(EntityRef boundEntity);

	KEYDEF(printer)

	private:
	const CallbackMap* getCallbacks() const override;
};
