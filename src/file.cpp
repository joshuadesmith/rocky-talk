//
// Created by jjjjo on 3/26/2026.
//

#include <iostream>
#include <sndfile.h>

#include "../include/rockytalk/file.hpp"

void ingestAudioFile(const char filePath[], AudioFileData* file_data_output) {
    SF_INFO info = {};

    SNDFILE* sf = sf_open(filePath, SFM_READ, &info);
    if (sf == nullptr) {
        // error occurred
        const char* err = sf_strerror(nullptr);
        std::cerr << err << std::endl;
        exit(0);
    }

    printf("Frames: %lld, Sample rate: %d, Channels: %d\n...\n", info.frames, info.samplerate, info.channels);

    const unsigned int size = info.frames * info.channels;
    const auto buffer = new double[size];
    file_data_output->data = new double[size];
    file_data_output->size = size;

    int read_cnt;
    int total_read_count = 0;
    while ((read_cnt = static_cast<int>(sf_readf_double(sf, buffer, info.frames))) > 0) {
        total_read_count += read_cnt;
        // copy buffer into output
        for (unsigned int i = 0; i < read_cnt; ++i) {
            file_data_output->data[i] = buffer[i];
        }
    }
    std::cout << "Total read count: " << total_read_count << std::endl;
    std::cout << "..." << std::endl;
    sf_close(sf);
}
