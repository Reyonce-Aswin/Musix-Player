#pragma once

#include <portaudio.h>
#include <vector>

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    bool init(int sampleRate, int channels);
    void shutdown();

    bool start();
    void stop();

    bool write(const std::vector<float>& buffer, unsigned long frames);

private:
    PaStream* stream;
    int sampleRate;
    int channels;
};