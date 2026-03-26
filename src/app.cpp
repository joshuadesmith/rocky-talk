//
// Created by jjjjo on 3/26/2026.
//
#include "../include/rockytalk/app.hpp"

#include <RtAudio.h>

#include "../include/rockytalk/audio_capture.hpp"
#include "../include/rockytalk/device.hpp"

int startApplication() {
    constexpr RtAudioFormat format = RTAUDIO_FLOAT32;
    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int bufferFrames = 1024;

    auto *capture = new AudioCapture{
        .buffer = std::vector<float>(bufferFrames * 10),
        .writeIndex = 0,
    };

    captureDefaultInputStream(sampleRate, bufferFrames, format, capture);

    // check out what's in the capture?
    std::cout << "Captured audio buffer values: " << capture->buffer.size() << std::endl;
    std::cout << "Printing first 50 values..." << std::endl;
    for (unsigned int i = 0; i < 50; ++i) {
        std::cout << capture->buffer[i] << std::endl;
    }
    delete capture;
    return 0;
}
