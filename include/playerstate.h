#pragma once

// Enumeration representing the possible states of the audio player
enum class PlayerState
{
    Stopped,  // Player is stopped and not playing
    Playing,  // Player is actively playing audio
    Paused    // Player is paused but can resume playback
};

// Converts a PlayerState enum value to its string representation
inline const char* stateToString(PlayerState state)
{
    switch (state)
    {
        case PlayerState::Playing: return "Playing";
        case PlayerState::Paused:  return "Paused";
        default:                   return "Stopped";
    }
}