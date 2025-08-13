#pragma once

namespace AudioSystem {
	// Begins the audio system on a separate thread.
	void start(float targetInterval);

	// Shuts down the audio system
	void cleanup();
}