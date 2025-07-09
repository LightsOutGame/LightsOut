#include "engine/AudioEngine.h"

#include <SDL3/SDL.h>
#include <thread>
#include <filesystem>
#include <iostream>

#include "Utils.h"

namespace AudioEngine {
	std::thread audioThread;
	float targetInterval;

	void run(); // Forward declaration

	void start(float targetInterval) {
		AudioEngine::targetInterval = targetInterval;

		audioThread = std::thread(run);
	}

	void run() {
		SDL_AudioStream* stream_;
		Uint8* wavBuffer_;
		Uint32 wavLength_;
		SDL_AudioSpec wavSpec_;

		SDL_AudioDeviceID device_;

		// Connect to an audio device
		SDL_AudioSpec deviceSpec = { SDL_AUDIO_F32, 2, 44100 };
		device_ = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &deviceSpec);
		if (!device_) {
			RaiseError("SDL_OpenAudioDevice failed: " + std::string(SDL_GetError()));
		}
		SDL_ResumeAudioDevice(device_); // Start device

		// Save the format of the audio device
		int numFrames;
		SDL_GetAudioDeviceFormat(device_, &deviceSpec, &numFrames);
		// For testing, lets print these out
		SDL_Log("Device info -- Format: %d;  Channels: %d; Frequency: %d", deviceSpec.format, deviceSpec.channels, deviceSpec.freq);
		SDL_Log("Buffer size: %d", numFrames);

		// Load the WAV data
		// This will be replaced later by actually connected with the audio sources in game
		std::cout << std::filesystem::current_path() << std::endl;
		if (!SDL_LoadWAV("assets\\audio\\Danger.wav", &wavSpec_, &wavBuffer_, &wavLength_)) {
			RaiseError("SDL_LoadWAV failed: " + std::string(SDL_GetError()));
		}
	}
}
