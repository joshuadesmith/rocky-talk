//
// Created by jjjjo on 3/26/2026.
//
#include "app.hpp"

#include <RtAudio.h>

#include "file.hpp"
#include "audio_capture.hpp"
#include "device.hpp"
#include "fft.hpp"

int startStreamApplication() {
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

int runFileProcessing() {
    auto file_path = "../static/E-Mu-Proteus-FX-Whales-C1.wav";
    std::cout << "Processing audio file: " << file_path << std::endl;

    // ingest audio file as function of amplitude over time
    auto file_data = AudioFileData{};
    ingestAudioFile(file_path, &file_data);

    for (unsigned int i = 0; i < 50; ++i) {
        printf("%.4f\n", file_data.data[i]);
    }

    // transform data domain from time to frequency
    auto* transformed = fft(file_data.data, file_data.size);

    std::cout << "Printing first 100 transformed values..." << std::endl;
    for (unsigned int i = 0; i < 100; ++i) {
        printf("(%.4f, %.4f)\n", transformed[i][0], transformed[i][1]);
    }

    fftw_cleanup(transformed);
    return 0;
}

int startApplication() {
    return runFileProcessing();
}
