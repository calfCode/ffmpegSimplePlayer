
cmake_minimum_required(VERSION 3.22.1)



add_subdirectory(external/libpng)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLOAD_BMP -DLOAD_GIF -DLOAD_LBM -DLOAD_PCX -DLOAD_PNM")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLOAD_SVG -DLOAD_TGA -DLOAD_XCF -DLOAD_XPM -DLOAD_XV")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLOAD_QOI")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshift-sign-overflow -Wstrict-prototypes -Wkeyword-macro")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-sign-compare")
add_definitions(-DGL_GLEXT_PROTOTYPES)
add_definitions(-DLOAD_PNG)
include_directories(../SDL2/include)
include_directories(./external/libpng/)
include_directories(./external/libpng/android)
include_directories(include)

include_directories(./src)


# General source files
file(GLOB SOURCE_FILES
        ./src/*.c
)


add_library(SDL2_image SHARED ${SOURCE_FILES})


target_link_libraries(SDL2_image
        # List libraries link to the target library
        png
        SDL2
        GLESv1_CM
        GLESv2
        OpenSLES
        android
        log)
