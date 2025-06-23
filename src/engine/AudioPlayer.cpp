#include "engine/AudioPlayer.h"
#include <stdexcept>
#include <iostream>

// Static member initialization
SDL_AudioDeviceID AudioPlayer::device_ = 0;
int AudioPlayer::instanceCount_ = 0;

AudioPlayer::AudioPlayer(const std::string& filePath) : stream_(nullptr), wavBuffer_(nullptr) {

    // Load WAV file
    if (!SDL_LoadWAV(filePath.c_str(), &wavSpec_, &wavBuffer_, &wavLength_)) {
		SDL_Log(SDL_GetError());
        throw std::runtime_error("SDL_LoadWAV failed: " + std::string(SDL_GetError()));
    }

    // Initialize shared device if not open
    if (instanceCount_ == 0) {
        initDevice();
    }

    // Create audio stream
    SDL_AudioSpec deviceSpec = { SDL_AUDIO_F32, 2, 44100 }; // Device format
    stream_ = SDL_CreateAudioStream(&wavSpec_, &deviceSpec);
    if (!stream_) {
        SDL_free(wavBuffer_);
        closeDevice();
        throw std::runtime_error("SDL_CreateAudioStream failed: " + std::string(SDL_GetError()));
    }

    // Bind stream to shared device
    if (SDL_BindAudioStreams(device_, &stream_, 1)) {
        SDL_DestroyAudioStream(stream_);
        SDL_free(wavBuffer_);
        closeDevice();
        throw std::runtime_error("SDL_BindAudioStreams failed: " + std::string(SDL_GetError()));
    }

    instanceCount_++;
}

AudioPlayer::~AudioPlayer() {
    stop();
    SDL_DestroyAudioStream(stream_);
    SDL_free(wavBuffer_);
    instanceCount_--;
    if (instanceCount_ == 0) {
        closeDevice();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}

void AudioPlayer::initDevice() {
    SDL_AudioSpec deviceSpec = { SDL_AUDIO_F32, 2, 44100 };
    device_ = SDL_OpenAudioDevice(NULL, &deviceSpec);
    if (!device_) {
        throw std::runtime_error("SDL_OpenAudioDevice failed: " + std::string(SDL_GetError()));
    }
    SDL_ResumeAudioDevice(device_); // Start device
}

void AudioPlayer::closeDevice() {
    if (device_) {
        SDL_CloseAudioDevice(device_);
        device_ = 0;
    }
}

void AudioPlayer::play() {
    stop(); // Clear and restart
    if (SDL_PutAudioStreamData(stream_, wavBuffer_, wavLength_)) {
        std::cerr << "SDL_PutAudioStreamData failed: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_FlushAudioStream(stream_);
    SDL_ResumeAudioDevice(device_);
}

void AudioPlayer::pause() {
    SDL_PauseAudioStreamDevice(stream_);
}

void AudioPlayer::resume() {
    SDL_ResumeAudioStreamDevice(stream_);
}

void AudioPlayer::stop() {
    SDL_PauseAudioStreamDevice(stream_);
    SDL_ClearAudioStream(stream_);
}

void AudioPlayer::setVolume(float volume) {
    if (volume < 0.0f || volume > 1.0f) {
        std::cerr << "Volume must be between 0.0 and 1.0" << std::endl;
        return;
    }
    SDL_SetAudioStreamGain(stream_, volume);
}