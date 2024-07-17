
cmake_minimum_required(VERSION 3.22.1)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 ")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshift-sign-overflow -Wstrict-prototypes -Wkeyword-macro")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-sign-compare")
add_definitions(-DMUSIC_WAV)

include_directories(../SDL2/include)
include_directories(include)

include_directories(./src)
include_directories(./src/codecs)

# General source files
file(GLOB SOURCE_FILES
        ./src/*.c
        ./src/codecs/*.c
)


add_library(SDL2_mixer SHARED ${SOURCE_FILES})


target_link_libraries(SDL2_mixer
        # List libraries link to the target library
        SDL2
        GLESv1_CM
        GLESv2
        OpenSLES
        android
        log)
