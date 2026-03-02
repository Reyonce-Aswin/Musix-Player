#include "AudioEngine.h"
#include <iostream>

#define FRAMES_PER_BUFFER 512

AudioEngine::AudioEngine()
    : stream(nullptr), sampleRate(0), channels(0)
{
}

AudioEngine::~AudioEngine() {
    shutdown();
}

bool AudioEngine::init(int sr, int ch) {
    sampleRate = sr;
    channels = ch;

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio init error: "
                  << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    err = Pa_OpenDefaultStream(
        &stream,
        0,              // no input
        channels,       // output channels
        paFloat32,      // 32-bit float
        sampleRate,
        FRAMES_PER_BUFFER,
        nullptr,        // blocking mode (no callback)
        nullptr
    );

    if (err != paNoError) {
        std::cerr << "Stream open error: "
                  << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    return true;
}

bool AudioEngine::start() {
    if (!stream) return false;

    PaError err = Pa_StartStream(stream);
    return err == paNoError;
}

void AudioEngine::stop() {
    if (stream) {
        Pa_StopStream(stream);
    }
}

bool AudioEngine::write(const std::vector<float>& buffer, unsigned long frames) {
    if (!stream) return false;

    PaError err = Pa_WriteStream(stream, buffer.data(), frames);
    return err == paNoError;
}

void AudioEngine::shutdown() {
    if (stream) {
        Pa_CloseStream(stream);
        stream = nullptr;
    }

    Pa_Terminate();
}