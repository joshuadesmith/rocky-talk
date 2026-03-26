cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 20)

project(rocky_talk)

include_directories(${PROJECT_SOURCE_DIR}/include/rockytalk ${PROJECT_SOURCE_DIR}/src)
file(GLOB ALL_FILES
        "${PROJECT_SOURCE_DIR}/include/rockytalk/*.h"
        "${PROJECT_SOURCE_DIR}/include/rockytalk/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

find_package(RtAudio CONFIG REQUIRED)
find_package(PortAudio CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)

add_executable(rocky_talk ${ALL_FILES})

target_link_libraries(rocky_talk PRIVATE RtAudio::rtaudio portaudio SndFile::sndfile)
