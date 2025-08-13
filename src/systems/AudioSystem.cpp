#include "systems/AudioSystem.h"

#include <SDL3/SDL.h>
#include <thread>
#include <filesystem>
#include <iostream>
#include <ctime>
#include <chrono>

#include "Utils.h"
#include "engine/AudioTrack.h"

namespace AudioSystem {
	SDL_Thread* audioThread;
	float targetInterval;

	int run(void* data) {
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
		long iterationDurationMillis = 100; // in milliseconds
		double waitMultiplier = 0.95; // wait a litte less than target duration so we stay ahead of the audio
		int framesEachIteration = deviceSpec.freq * iterationDurationMillis / 1000;
		int bytesEachIteration = SDL_AUDIO_FRAMESIZE(wavSpec_) * framesEachIteration;

		while (!myTrack.isEmpty()) {
			long iterStart = SDL_GetTicks();

			uchar* dataThisFrame;
			bool fileEnded = false;
			int bytesToQueue;
			if ((bytesToQueue = myTrack.remove(&dataThisFrame, bytesEachIteration)) != bytesEachIteration) {
				fileEnded = true;
			}

			if (!SDL_PutAudioStreamData(stream_, dataThisFrame, bytesToQueue)) {
				std::cout << bytesToQueue << std::endl;
				RaiseError("We got a problem: " + std::string(SDL_GetError()));
			}
			free(dataThisFrame);
			std::cout << "Frame complete. " << std::endl;

			if (fileEnded) {
				break;
			}

			// sleep for the rest of the iteration
			long iterEnd = SDL_GetTicks();
			long milliRemaining = (iterationDurationMillis * waitMultiplier - (iterEnd - iterStart));
			if (milliRemaining > 0)
				SDL_Delay(milliRemaining);
		}

		// Track is finished, wait for stream to end
		while (SDL_GetAudioStreamQueued(stream_)) {
			SDL_Delay(1000);
		}

		std::cout << "Done!" << std::endl;
		return 0;
	}

	void start(float targetInterval) {
		AudioSystem::targetInterval = targetInterval;

		audioThread = SDL_CreateThread(run, NULL, NULL);
	}

	void cleanup() {
		int threadReturn;
		SDL_WaitThread(audioThread, &threadReturn);
	}
}
