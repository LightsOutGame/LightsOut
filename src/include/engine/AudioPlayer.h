#pragma once
#include <SDL3/SDL.h>
#include <string>

class AudioPlayer {
public:
    // Constructor: Load WAV file
    AudioPlayer(const std::string& filePath);
    ~AudioPlayer();

    // Playback control
    void play();
    void pause();
    void resume();
    void stop();

    // Audio effects
    void setVolume(float volume); // 0.0f to 1.0f

private:
    SDL_AudioStream* stream_;
    Uint8* wavBuffer_;
    Uint32 wavLength_;
    SDL_AudioSpec wavSpec_;

    // Static device management
    static SDL_AudioDeviceID device_;
    static int instanceCount_;
    static void initDevice();
    static void closeDevice();
};

