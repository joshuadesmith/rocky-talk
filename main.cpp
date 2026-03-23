#include <iostream>
#include "RtAudio.h"

#define SCHIIT_MODIUS_OUTPUT 129;

int audioCallback(void *inputBuffer, void* outputBuffer, const unsigned int nFrames,
    double streamTime, RtAudioStreamStatus streamStatus, void *userData) {

    auto input = static_cast<float*>(inputBuffer);
    auto output = static_cast<float*>(outputBuffer);

    // just pass-through for now
    for (unsigned int i = 0; i < nFrames * 2; i++) {
        std::cout << input[i];
        output[i] = input[i];
    }

    return 0;
}

int probeDevices() {
    RtAudio audio;

    const std::vector<unsigned int> ids = audio.getDeviceIds();
    if (ids.empty()) {
        std::cout << "No devices found" << std::endl;
        return 0;
    }

    for (const unsigned int id : ids) {
        RtAudio::DeviceInfo info = audio.getDeviceInfo(id);

        std::cout << id << " device " << info.ID << ": " << info.name << std::endl;
        std::cout << "-- output channels: " << info.outputChannels << std::endl;
        std::cout << "-- input channels: " << info.inputChannels << std::endl;
    }

    return 1;
}

void openStream() {
    RtAudio audio;

    RtAudio::StreamParameters params;
    params.deviceId = audio.getDefaultOutputDevice();
    params.nChannels = 2;

    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256;

    RtAudio::StreamOptions options;
    options.flags = RTAUDIO_NONINTERLEAVED;

    if (audio.openStream(
        &params,
        nullptr,
        RTAUDIO_FLOAT32,
        sampleRate,
        &bufferFrames,
        &audioCallback,
        nullptr,
        &options)) {
        std::cout << '\n' << audio.getErrorText() << '\n' << std::endl;
        exit(0);
    }

    // this is where a stream would start or stop
}

int main() {
    openStream();
}