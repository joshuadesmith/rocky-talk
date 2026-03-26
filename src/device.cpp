//
// Created by jjjjo on 3/26/2026.
//
#include "../include/rockytalk/device.hpp"

#include <thread>
#include <chrono>

#include "../include/rockytalk/audio_capture.hpp"
#include "../include/rockytalk/util.hpp"

void validateDeviceExistence(RtAudio *audio) {
    if (std::vector<unsigned int> deviceIds = audio->getDeviceIds(); deviceIds.empty()) {
        std::cerr << "No audio devices found" << std::endl;
        exit(0);
    }
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
        std::cout << "-- max output channels: " << info.outputChannels << std::endl;
        std::cout << "-- max input channels: " << info.inputChannels << std::endl;
        std::cout << "-- max duplex channels: " << info.duplexChannels << std::endl;
        std::cout << "-- preferred sample rate:" << info.preferredSampleRate << " Hz" << std::endl;
        std::cout << "-- native formats: [";

        if( info.nativeFormats | RTAUDIO_SINT8 ) {
            std::cout << "8-bits signed int; ";
        }

        if( info.nativeFormats | RTAUDIO_SINT16 ) {
            std::cout << "16-bits signed int; ";
        }

        if( info.nativeFormats | RTAUDIO_SINT24 ) {
            std::cout << "24-bits signed int; ";
        }

        if( info.nativeFormats | RTAUDIO_SINT32 ) {
            std::cout << "32-bits signed int; ";
        }

        if( info.nativeFormats | RTAUDIO_FLOAT32 ) {
            std::cout << "32-bits normalized float; ";
        }

        if( info.nativeFormats | RTAUDIO_FLOAT64 ) {
            std::cout << "64-bits normalized fload; ";
        }

        std::cout << "]" << std::endl;

        std::cout << "-- supported sample rates: [";
        for (const auto sample_rate : info.sampleRates) {
            std::cout << sample_rate << ", ";
        }
        std::cout << "]" << std::endl;

    }

    return 1;
}

int captureDefaultInputStream(
    unsigned int sample_rate,
    unsigned int buffer_frames,
    RtAudioFormat format,
    AudioCapture *capture) {
    auto *audio = new RtAudio();

    RtAudioErrorCallback errorCallback = &printRtAudioErr;
    audio->setErrorCallback(errorCallback);

    validateDeviceExistence(audio);

    std::cout << "Backend: " << audio->getCurrentApi() << std::endl;

    RtAudio::StreamParameters *outputParams = nullptr;
    RtAudio::StreamParameters inputParams = {
        .deviceId = audio->getDefaultInputDevice(),
        .nChannels = 1,
        .firstChannel = 0
    };

    const RtAudioCallback callback = &captureDeviceAudio;
    RtAudio::StreamOptions *options = nullptr;

    if (audio->openStream(
        outputParams,
        &inputParams,
        format,
        sample_rate,
        &buffer_frames,
        callback,
        capture,
        options)) {
        // if openStream returns a non-zero value, an error has occurred
        std::cerr << "Error occurred while opening stream: " << std::endl;
        std::cout << audio->getErrorText() << '\n' << std::endl;
        exit(0);
        }

    if (audio->startStream()) {
        std::cerr << "Error occurred while starting stream: " << std::endl;
        std::cout << audio->getErrorText() << '\n' << std::endl;
        exit(0);
    }

    for (auto t = 0; t < 3; ++t) {
        std::cout << "Waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    audio->stopStream();
    audio->closeStream();
    delete audio;
    return 0;
}

int captureDeviceAudio(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                        double streamTime, RtAudioStreamStatus status, void *userData) {
    if (status & RTAUDIO_INPUT_OVERFLOW) {
        // don't print
        return -1;
    }

    auto *input = static_cast<float *>(inputBuffer);
    auto *capture = static_cast<AudioCapture *>(userData);

    size_t index = capture->writeIndex.load(std::memory_order_relaxed);

    for (unsigned int i = 0; i < nBufferFrames; ++i) {
        capture->buffer[index] = input[i];
        index = (index + 1) % capture->buffer.size();
        // capture->buffer.push_back(input[i]);
        // index = index + 1;
    }

    return 0;
}