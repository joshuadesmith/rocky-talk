//
// Created by jjjjo on 3/26/2026.
//

#include <iostream>
#include <sndfile.h>

#include "../include/rockytalk/file.hpp"

double* ingestAudioFile(const char filePath[]) {
    SF_INFO info = {};

    SNDFILE* sf = sf_open(filePath, SFM_READ, &info);
    if (sf == nullptr) {
        // error occurred
        const char* err = sf_strerror(nullptr);
        std::cerr << err << std::endl;
        exit(0);
    }

    printf("Frames: %lld, Sample rate: %d, Channels: %d\n", info.frames, info.samplerate, info.channels);

    const auto buffer = new double[info.frames * info.channels];

    int readCount;
    while (( readCount = static_cast<int>(sf_readf_double(sf, buffer, info.frames))) > 0) {
        for (int k = 0; k < readCount; k++) {
            for (int m = 0; m < info.channels; m++) {
                printf("%12.10f\n", buffer[k * info.channels + m]);
            }
        }
    }

    sf_close(sf);
    return buffer;
}
