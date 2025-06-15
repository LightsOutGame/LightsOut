/*
 * AudioTestComponent.h
 * Defines the AudioTestComponent class, a test component that does nothing but play danger.mp3
 */

#include "Component.h"

class AudioTestComponent : public Component {
	public:
	// Constructor, binds component to an entity
	AudioTestComponent(EntityRef boundEntity);

	// Defines the unique key for this component type
	KEYDEF(audio_test)

	private:
	// Returns the map of event callbacks for this component
	const CallbackMap* getCallbacks() const override;
};