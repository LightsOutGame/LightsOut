/*
 * AudioTestComponent.cpp
 * Implements the test component AudioTestComponent
 * Provides event callback registration for playing audio
 */

#include <iostream>

#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "components/AudioTestComponent.h"

// Callback function
static void play_audio(Component* self) {
	// Load audio files
	AudioTestComponent* audioComponent = dynamic_cast<AudioTestComponent*>(self);
	audioComponent->backgroundMusic = Mix_LoadMUS("src/assets/audio/Danger.mp3");
	if (!audioComponent->backgroundMusic) {
		std::cerr << "Mix_LoadMUS failed: " << SDL_GetError() << std::endl;
	}

	// Check if music is already playing to avoid restarting
    if (!Mix_PlayingMusic() && audioComponent->backgroundMusic) {
		std::cout << "audio file has just been started" << std::endl;
        Mix_PlayMusic(audioComponent->backgroundMusic, -1);
    }
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