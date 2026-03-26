//
// Created by jjjjo on 3/26/2026.
//

#ifndef ROCKY_TALK_DEVICE_HPP
#define ROCKY_TALK_DEVICE_HPP
#include <RtAudio.h>
#include "audio_capture.hpp"

#define SCHIIT_MODIUS_OUTPUT 129;
#define DEFAULT_SAMPLE_RATE 44100;
#define DEFAULT_BUFFER_FRAMES 256;

int probeDevices();

void validateDeviceExistence(RtAudio *audio);

int captureDeviceAudio(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                        double streamTime, RtAudioStreamStatus status, void *userData);

int captureDefaultInputStream(unsigned int sample_rate, unsigned int buffer_frames, RtAudioFormat format, AudioCapture *capture);

#endif //ROCKY_TALK_DEVICE_HPP