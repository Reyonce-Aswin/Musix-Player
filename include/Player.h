#pragma once

#include "AudioFile.h"
#include "AudioEngine.h"

#include <thread>
#include <atomic>
#include <string>

class Player {
public:
    Player(const std::string& path);
    ~Player();

    void play();
    void pause();
    void resume();
    void stop();

    void togglePause();
    void toggleLoop();
    void toggleMute();

    void setLoop(bool enabled);

private:
    void playbackLoop();

    AudioFile audioFile;
    AudioEngine audioEngine;

    std::thread playbackThread;

    std::atomic<bool> playing;
    std::atomic<bool> paused;
    std::atomic<bool> stopRequested;
    std::atomic<bool> loopEnabled;

    std::atomic<bool> muted;
};