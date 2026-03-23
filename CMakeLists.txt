cmake_minimum_required(VERSION 4.0)
project(rocky_talk)

set(CMAKE_CXX_STANDARD 20)

find_package(RtAudio CONFIG REQUIRED)

add_executable(rocky_talk main.cpp)

target_link_libraries(rocky_talk PRIVATE RtAudio::rtaudio)
