#pragma once

#include <string>
#include <vector>
#include <sndfile.h>

class AudioFile {
public:
    AudioFile(const std::string& path);
    ~AudioFile();

    bool isOpen() const;

    int getSampleRate() const;
    int getChannels() const;
    sf_count_t getTotalFrames() const;

    sf_count_t readFrames(std::vector<float>& buffer, sf_count_t frames);
    void rewind();

private:
    SNDFILE* file;
    SF_INFO info;
};