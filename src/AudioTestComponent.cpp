/*
 * AudioTestComponent.cpp
 * Implements the test component AudioTestComponent
 * Provides event callback registration for playing audio
 */

#include <iostream>

#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "AudioTestComponent.h"

// Callback function
static void play_audio(Component* self) {
	std::cout << "wow, another cool function" << std::endl;
	// Load audio files
	Mix_Music* backgroundMusic = Mix_LoadMUS("src/audio/Danger.mp3");
	if (!backgroundMusic) {
		std::cerr << "Mix_LoadMUS failed: " << SDL_GetError() << std::endl;
	}

	Mix_PlayMusic(backgroundMusic, -1);
}

// Initialize AudioTestComponent
AudioTestComponent::AudioTestComponent(EntityRef boundEntity) : Component(boundEntity) {

}

// Returns the map of event callbacks for this component (PlayerUpdate: play_audio)
const CallbackMap* AudioTestComponent::getCallbacks() const {
	// Static map of event callbacks
	static CallbackMap printerCallbacks = {
		{ Events::PlayerUpdate, &play_audio }
	};

	return &printerCallbacks;
}