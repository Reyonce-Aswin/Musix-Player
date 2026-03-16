#pragma once

#include "AudioEngine.h"
#include <string>

// Player class provides a high-level interface for audio playback
class Player
{
public:
    // Constructor: Initializes the player with an audio file path
    Player(const std::string& path);
    // Destructor: Cleans up player resources
    ~Player();

    // Playback control methods
    bool play();           // Starts audio playback
    void togglePause();    // Toggles between play and pause
    void toggleLoop();     // Toggles loop mode on/off
    void toggleMute();     // Toggles mute on/off
    void stop();           // Stops playback

    // Status and information methods
    bool isStopped() const; // Returns true if player is stopped
    void printStatus();     // Prints current playback status
    

private:
    std::string filePath;     // Path to the audio file
    AudioEngine audioEngine;  // Underlying audio engine instance
};