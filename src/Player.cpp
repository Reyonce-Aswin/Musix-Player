#include "Player.h"
#include <iostream>

// Constructor: Initializes the Player with the audio file path
Player::Player(const std::string& path)
    : filePath(path)
{
}

// Destructor: Stops playback when the Player object is destroyed
Player::~Player()
{
    stop();
}

// Starts audio playback by loading the file and starting the engine
bool Player::play()
{
    if (!audioEngine.loadFile(filePath.c_str()))
    {
        std::cerr << "Failed to load file\n";
        return false;
    }

    return audioEngine.start();
}

// Toggles between play and pause states
void Player::togglePause()
{
    audioEngine.pause();
}

// Toggles loop playback mode on or off
void Player::toggleLoop()
{
    audioEngine.toggleLoop();
}

// Toggles mute state on or off
void Player::toggleMute()
{
    audioEngine.toggleMute();
}

// Stops audio playback
void Player::stop()
{
    audioEngine.stop();
}

// Checks if the player is in stopped state
bool Player::isStopped() const
{
    return audioEngine.getState() == PlayerState::Stopped;
}

// Prints the current playback status
void Player::printStatus()
{
    audioEngine.printStatus();
}