
cmake_minimum_required(VERSION 3.22.1)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 ")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wdocumentation -Wmissing-prototypes -Wunreachable-code-break")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunneeded-internal-declaration -Wmissing-variable-declarations")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfloat-conversion -Wshorten-64-to-32 -Wunreachable-code-return")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshift-sign-overflow -Wstrict-prototypes -Wkeyword-macro")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-sign-compare")
add_definitions(-DGL_GLEXT_PROTOTYPES)


include_directories(include)

include_directories(./src)
include_directories(./src/audio)
include_directories(./src/audio/android)
include_directories(./src/audio/dummy)
include_directories(./src/audio/aaudio)
include_directories(./src/audio/openslES)
include_directories(./src/atomic)
include_directories(./src/atomic)
include_directories(./src/core/android)
include_directories(./src/cpuinfo)
include_directories(./src/dynapi)
include_directories(./src/events)
include_directories(./src/file)
include_directories(./src/haptic)
include_directories(./src/haptic/android)
include_directories(./src/hidapi)
include_directories(./src/hidapi/android)
include_directories(./src/joystick)
include_directories(./src/joystick/android)
include_directories(./src/joystick/hidapi)
include_directories(./src/joystick/virtual)
include_directories(./src/loadso/dlopen)
include_directories(./src/locale)
include_directories(./src/locale/android)
include_directories(./src/misc)
include_directories(./src/misc/android)
include_directories(./src/power)
include_directories(./src/power/android)
include_directories(./src/filesystem/android)
include_directories(./src/sensor)
include_directories(./src/sensor/android)
include_directories(./src/render)
include_directories(./src/render/)
include_directories(./src/stdlib)
include_directories(./src/thread)
include_directories(./src/thread/pthread)
include_directories(./src/timer)
include_directories(./src/timer/unix)
include_directories(./src/video)
include_directories(./src/video/android)
include_directories(./src/video/yuv2rgb)
include_directories(./src/test)
include_directories(${ANDROID_NDK}/sources/android/cpufeatures)
# General source files
file(GLOB SOURCE_FILES
        ./src/*.c
        ./src/audio/*.c
        ./src/audio/android/*.c
        ./src/audio/dummy/*.c
        ./src/audio/aaudio/*.c
        ./src/audio/openslES/*.c
        ./src/atomic/SDL_atomic.c
        ./src/atomic/SDL_spinlock.c
        ./src/core/android/*.c
        ./src/cpuinfo/*.c
        ./src/dynapi/*.c
        ./src/events/*.c
        ./src/file/*.c
        ./src/haptic/*.c
        ./src/haptic/android/*.c
        ./src/hidapi/*.c
        ./src/hidapi/android/*.cpp
        ./src/joystick/*.c
        ./src/joystick/android/*.c
        ./src/joystick/hidapi/*.c
        ./src/joystick/virtual/*.c
        ./src/loadso/dlopen/*.c
        ./src/locale/*.c
        ./src/locale/android/*.c
        ./src/misc/*.c
        ./src/misc/android/*.c
        ./src/power/*.c
        ./src/power/android/*.c
        ./src/filesystem/android/*.c
        ./src/sensor/*.c
        ./src/sensor/android/*.c
        ./src/render/*.c
        ./src/render/*/*.c
        ./src/stdlib/*.c
        ./src/thread/*.c
        ./src/thread/pthread/*.c
        ./src/timer/*.c
        ./src/timer/unix/*.c
        ./src/video/*.c
        ./src/video/android/*.c
        ./src/video/yuv2rgb/*.c
        ./src/test/*.c
        ${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c
)


add_library(SDL2 SHARED ${SOURCE_FILES})


target_link_libraries(SDL2
        # List libraries link to the target library
        dl
        GLESv1_CM
        GLESv2
        OpenSLES
        android
        log)
