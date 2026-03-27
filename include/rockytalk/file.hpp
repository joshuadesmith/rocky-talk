//
// Created by jjjjo on 3/26/2026.
//

#ifndef ROCKY_TALK_FILE_HPP
#define ROCKY_TALK_FILE_HPP

struct AudioFileData {
    double* data;
    unsigned int size;
};

void ingestAudioFile(const char filePath[], AudioFileData* file_data_output);

#endif //ROCKY_TALK_FILE_HPP