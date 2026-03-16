#pragma once

#include <atomic>
#include <chrono>
#include <sndfile.h>
#include <portaudio.h>
#include "PlayerState.h"

// AudioEngine class handles audio file playback using PortAudio and libsndfile
class AudioEngine
{
public:
    // Constructor: Initializes the audio engine
    AudioEngine();
    // Destructor: Cleans up resources
    ~AudioEngine();

    // Loads an audio file for playback
    bool loadFile(const char* path);

    // Playback control methods
    bool start();      // Starts audio playback
    void pause();      // Toggles between play and pause
    void stop();       // Stops playback
    void shutdown();   // Cleans up all resources

    // Audio control toggles
    void toggleLoop(); // Toggles loop mode on/off
    void toggleMute(); // Toggles mute on/off

    // Status and information
    void printStatus();        // Prints current playback status
    PlayerState getState() const; // Returns current playback state

private:
    // PortAudio callback function for audio data processing
    static int audioCallback(const void* input,
                             void* output,
                             unsigned long frameCount,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void* userData);

    // Audio file and stream handles
    SNDFILE* file = nullptr;    // Handle to the loaded audio file
    SF_INFO info{};             // Audio file information structure

    PaStream* stream = nullptr; // PortAudio stream handle

    // Playback position tracking
    std::atomic<sf_count_t> currentFrame{0}; // Current frame position (atomic for thread safety)

    // Status update timing
    std::chrono::steady_clock::time_point lastUpdateTime; // Last status update timestamp
    sf_count_t lastFramePosition = 0; // Frame position at last update

    // Playback state and options
    PlayerState state = PlayerState::Stopped; // Current playback state
    bool loop = false;     // Whether to loop playback
    bool muted = false;    // Whether audio is muted
};