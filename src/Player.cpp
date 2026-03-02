#include "Player.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

#define FRAMES_PER_BUFFER 512

Player::Player(const std::string& path)
    : audioFile(path),
      playing(false),
      paused(false),
      muted(false),
      stopRequested(false),
      loopEnabled(true)   // loop is default behavior
{
}

Player::~Player() {
    stop();
}

void Player::setLoop(bool enabled) {
    loopEnabled = enabled;
}

void Player::play() {
    if (playing) return;

    if (!audioFile.isOpen()) {
        std::cerr << "Audio file not open.\n";
        return;
    }

    audioFile.rewind();  // Always start from beginning

    if (!audioEngine.init(audioFile.getSampleRate(),
                          audioFile.getChannels())) {
        return;
    }

    if (!audioEngine.start()) {
        return;
    }

    stopRequested = false;
    paused = false;
    playing = true;

    playbackThread = std::thread(&Player::playbackLoop, this);
}

void Player::pause() {
    if (playing)
        paused = true;
}

void Player::resume() {
    if (playing)
        paused = false;
}

void Player::togglePause() {
    if (!playing) return;
    paused = !paused;
}

void Player::toggleLoop() {
    loopEnabled = !loopEnabled;
}

void Player::toggleMute() {
    muted = !muted;
}

void Player::stop() {

    stopRequested = true;

    if (playbackThread.joinable())
        playbackThread.join();

    audioEngine.stop();

    paused = false;
    playing = false;
}

void Player::playbackLoop() {

    std::vector<float> buffer;
    sf_count_t framesRead;

    while (!stopRequested) {

        if (paused) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        framesRead = audioFile.readFrames(buffer, FRAMES_PER_BUFFER);

        if (framesRead > 0) {

            if (!muted) {
                audioEngine.write(buffer, framesRead);
            }
            else {
                std::fill(buffer.begin(), buffer.end(), 0.0f);
                audioEngine.write(buffer, framesRead);
            }

        } else {

            if (loopEnabled) {
                audioFile.rewind();
            } else {
                break;
            }
        }
    }

    playing = false;
}