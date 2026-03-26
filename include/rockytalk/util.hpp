//
// Created by jjjjo on 3/26/2026.
//

#ifndef ROCKY_TALK_UTIL_HPP
#define ROCKY_TALK_UTIL_HPP
#include <RtAudio.h>
#include <string>

void printErr(const char* err_msg);
void printErr(const std::string &err_msg);
void printRtAudioErr(RtAudioErrorType err_type, const std::string &err_msg);

#endif //ROCKY_TALK_UTIL_HPP