#include "AudioFile.h"
#include <iostream>

AudioFile::AudioFile(const std::string& path) : file(nullptr)
{
    info = {};
    file = sf_open(path.c_str(), SFM_READ, &info);

    if (!file) {
        std::cerr << "Failed to open audio file: "
                  << sf_strerror(nullptr) << std::endl;
    }
}

AudioFile::~AudioFile() {
    if (file) {
        sf_close(file);
    }
}

bool AudioFile::isOpen() const {
    return file != nullptr;
}

int AudioFile::getSampleRate() const {
    return info.samplerate;
}

int AudioFile::getChannels() const {
    return info.channels;
}

sf_count_t AudioFile::getTotalFrames() const {
    return info.frames;
}

sf_count_t AudioFile::readFrames(std::vector<float>& buffer, sf_count_t frames) {
    if (!file) return 0;

    buffer.resize(frames * info.channels);
    return sf_readf_float(file, buffer.data(), frames);
}

void AudioFile::rewind() {
    if (file) {
        sf_seek(file, 0, SEEK_SET);
    }
}