#include "engine/AudioEngine.h"

#include <SDL3/SDL.h>
#include <thread>
#include <filesystem>
#include <iostream>
#include <ctime>
#include <chrono>

#include "Utils.h"
#include "engine/AudioTrack.h"

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
		if (!SDL_LoadWAV("assets\\audio\\piano.wav", &wavSpec_, &wavBuffer_, &wavLength_)) {
			RaiseError("SDL_LoadWAV failed: " + std::string(SDL_GetError()));
		}

		// Create audio stream
		stream_ = SDL_CreateAudioStream(&wavSpec_, &deviceSpec);
		if (!stream_) {
			SDL_free(wavBuffer_);
			SDL_CloseAudioDevice(device_);
			device_ = 0;
			RaiseError("SDL_CreateAudioStream failed: " + std::string(SDL_GetError()));
		}

		// Bind stream to shared device
		if (!SDL_BindAudioStreams(device_, &stream_, 1)) {
			SDL_DestroyAudioStream(stream_);
			SDL_free(wavBuffer_);
			SDL_CloseAudioDevice(device_);
			device_ = 0;
			RaiseError("SDL_BindAudioStreams failed: " + std::string(SDL_GetError()));
		}

		AudioTrack myTrack(64);

		myTrack.add(wavBuffer_, wavLength_);
		double iterationDuration = 0.1;
		double waitMultiplier = 0.9; // wait a litte less than target duration so we stay ahead of the audio
		int framesEachIteration = deviceSpec.freq * iterationDuration;
		int bytesEachIteration = SDL_AUDIO_FRAMESIZE(wavSpec_) * framesEachIteration;

		while (!myTrack.isEmpty()) {
			time_t iterStart = time(nullptr);

			uchar* dataThisFrame = myTrack.remove(bytesEachIteration);
			if (!SDL_PutAudioStreamData(stream_, dataThisFrame, bytesEachIteration))
				RaiseError("We got a problem: " + std::string(SDL_GetError()));
			std::cout << "Frame complete. " << std::endl;

			time_t iterEnd = time(nullptr);

			// sleep for the rest of the iteration
			long milliRemaining = (iterationDuration * waitMultiplier - difftime(iterEnd, iterStart)) * 1000L;
			std::this_thread::sleep_for(std::chrono::milliseconds(milliRemaining));
		}
	}
}
