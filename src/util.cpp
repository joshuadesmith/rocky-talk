//
// Created by jjjjo on 3/26/2026.
//
#include "../include/rockytalk/util.hpp"

void printErr(const char* err_msg) {
    std::cerr << "Error: " << err_msg << std::endl;
}

void printErr(const std::string &err_msg) {
    std::cerr << "Error: " << err_msg << std::endl;
}

void printRtAudioErr(RtAudioErrorType err_type, const std::string &err_msg) {
    if (err_type != RTAUDIO_NO_ERROR) {
        std::cerr << "RtAudio Error: (code: " << err_type << ") " << err_msg << std::endl;
    }
}