//
// Created by jjjjo on 3/26/2026.
//

#ifndef ROCKY_TALK_AUDIO_CAPTURE_HPP
#define ROCKY_TALK_AUDIO_CAPTURE_HPP

#include <vector>
#include <atomic>

struct AudioCapture {
    std::vector<float> buffer;
    std::atomic<size_t> writeIndex{0};
};

#endif //ROCKY_TALK_AUDIO_CAPTURE_HPP