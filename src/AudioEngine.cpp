#include "AudioEngine.h"
#include <iostream>
#include <cstring>
#include <chrono>

#define FRAMES_PER_BUFFER 512

// Constructor: Initializes the AudioEngine object
AudioEngine::AudioEngine()
{
}

// Destructor: Cleans up resources when the object is destroyed
AudioEngine::~AudioEngine()
{
    shutdown();
}

// Loads an audio file for playback
bool AudioEngine::loadFile(const char* path)
{
    file = sf_open(path, SFM_READ, &info);

    if (!file)
    {
        std::cerr << "Error: Unable to open file\n";
        return false;
    }

    currentFrame = 0;
    state = PlayerState::Stopped;

    lastFramePosition = 0;
    lastUpdateTime = std::chrono::steady_clock::now();

    return true;
}

// PortAudio callback function that provides audio data for playback
int AudioEngine::audioCallback(const void*,
                               void* output,
                               unsigned long frameCount,
                               const PaStreamCallbackTimeInfo*,
                               PaStreamCallbackFlags,
                               void* userData)
{
    AudioEngine* engine = static_cast<AudioEngine*>(userData);
    float* out = static_cast<float*>(output);

    if (engine->state != PlayerState::Playing)
    {
        std::memset(out, 0, frameCount * engine->info.channels * sizeof(float));
        return paContinue;
    }

    sf_count_t framesRead =
        sf_readf_float(engine->file, out, frameCount);

    engine->currentFrame += framesRead;

    engine->lastFramePosition = engine->currentFrame.load();
    engine->lastUpdateTime = std::chrono::steady_clock::now();

    if (engine->muted)
    {
        for (unsigned int i = 0;
             i < framesRead * engine->info.channels;
             i++)
        {
            out[i] = 0.0f;
        }
    }

    if (framesRead < frameCount)
    {
        if (engine->loop)
        {
            sf_seek(engine->file, 0, SEEK_SET);

            engine->currentFrame = 0;
            engine->lastFramePosition = 0;
            engine->lastUpdateTime = std::chrono::steady_clock::now();
        }
        else
        {
            engine->state = PlayerState::Stopped;

            std::memset(
                out + framesRead * engine->info.channels,
                0,
                (frameCount - framesRead) *
                    engine->info.channels *
                    sizeof(float));

            return paComplete;
        }
    }

    return paContinue;
}

// Starts audio playback by initializing PortAudio and opening the stream
bool AudioEngine::start()
{
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError)
    {
        std::cerr << "PortAudio init error: "
                  << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    err = Pa_OpenDefaultStream(
        &stream,
        0,
        info.channels,
        paFloat32,
        info.samplerate,
        FRAMES_PER_BUFFER,
        audioCallback,
        this);

    if (err != paNoError)
    {
        std::cerr << "Stream open error: "
                  << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        std::cerr << "Stream start error: "
                  << Pa_GetErrorText(err) << std::endl;
        return false;
    }

    state = PlayerState::Playing;

    return true;
}

// Toggles between playing and paused states
void AudioEngine::pause()
{
    if (state == PlayerState::Playing)
        state = PlayerState::Paused;
    else if (state == PlayerState::Paused)
        state = PlayerState::Playing;
}

// Stops audio playback and closes the stream
void AudioEngine::stop()
{
    if (stream)
    {
        Pa_StopStream(stream);
        state = PlayerState::Stopped;
    }
}

// Toggles the loop playback mode on or off
void AudioEngine::toggleLoop()
{
    loop = !loop;
}

// Toggles the mute state on or off
void AudioEngine::toggleMute()
{
    muted = !muted;
}

// Returns the current playback state
PlayerState AudioEngine::getState() const
{
    return state;
}

// Cleans up all resources: stops stream, closes file, terminates PortAudio
void AudioEngine::shutdown()
{
    if (stream)
    {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        stream = nullptr;
    }

    if (file)
    {
        sf_close(file);
        file = nullptr;
    }

    Pa_Terminate();
}

// Prints the current playback status including progress bar and time
void AudioEngine::printStatus()
{
    double totalSeconds =
        (double)info.frames / info.samplerate;

    auto now = std::chrono::steady_clock::now();
    double elapsed =
        std::chrono::duration<double>(now - lastUpdateTime).count();

    double estimatedFrames =
        lastFramePosition + elapsed * info.samplerate;

    if (estimatedFrames > info.frames)
        estimatedFrames = info.frames;

    double currentSeconds =
        estimatedFrames / info.samplerate;

    static int lastSecond = -1;
    int currentSecond = (int)currentSeconds;

    if (currentSecond == lastSecond)
        return;

    lastSecond = currentSecond;

    int progressWidth = 30;

    double progress =
        estimatedFrames / info.frames;

    int pos = progress * progressWidth;

    if (pos >= progressWidth)
        pos = progressWidth - 1;

    std::cout << "\rState: ";

    if (state == PlayerState::Playing)
        std::cout << "Playing";
    else if (state == PlayerState::Paused)
        std::cout << "Paused";
    else
        std::cout << "Stopped";

    std::cout << " | Mute: " << (muted ? "Yes" : "No")
              << " | Loop: " << (loop ? "On" : "Off")
              << " [";

    for (int i = 0; i < progressWidth; i++)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << "-";
    }

    std::cout << "] ";

    int curMin = currentSeconds / 60;
    int curSec = (int)currentSeconds % 60;

    int totMin = totalSeconds / 60;
    int totSec = (int)totalSeconds % 60;

    printf("%02d:%02d/%02d:%02d",
           curMin, curSec,
           totMin, totSec);

    std::cout << "   " << std::flush;
}