cmake_minimum_required(VERSION 3.22.1)

project(MY_APP)

find_library(SDL2 SDL2)
find_library(SDL2_image SDL2_image)
find_library(SDL2_mixer SDL2_mixer)

add_library(main SHARED)
include_directories(../SDL2/include)
include_directories(../SDL2_image/include)
include_directories(../SDL2_ttf/)
include_directories(../SDL2_mixer/include)
include_directories(../ffmpeg_simple_player)
file(GLOB ffmpeg_simple_player_srcs "../ffmpeg_simple_player/*.cpp")
target_sources(main PRIVATE
        ${ffmpeg_simple_player_srcs}
#        play_music.cpp
)

set(SDL2_ttf_lib_path ${CMAKE_CURRENT_SOURCE_DIR}/../SDL2_ttf/${ANDROID_ABI}/)

add_library( SDL2_ttf
        SHARED
        IMPORTED )

set_target_properties( SDL2_ttf
        PROPERTIES IMPORTED_LOCATION
        ${SDL2_ttf_lib_path}/libSDL2_ttf.so)

#USE_NEW_FFMPEG ON 7.0.1; OFF 6.0.1
set(USE_NEW_FFMPEG OFF)

if (USE_NEW_FFMPEG)
    set(VERSION 7.0.1)
    set(TYPE SHARED)
    set(LIB_EXT so)
    set(POSTPROC ON)

else ()
    set(VERSION 6.0.1)
    set(TYPE STATIC)
    set(LIB_EXT a)
    set(POSTPROC OFF)
endif (USE_NEW_FFMPEG)

#MESSAGE( STATUS "VERSION = ${VERSION}")
#MESSAGE( STATUS "TYPE = ${TYPE}")
#MESSAGE( STATUS "LIB_EXT = ${LIB_EXT}")
include_directories(../ffmpeg/${VERSION}/${ANDROID_ABI}/include)

set(ffmpeg_lib_path ${CMAKE_CURRENT_SOURCE_DIR}/../ffmpeg/${VERSION}/${ANDROID_ABI}/lib)

add_library( avcodec
        ${TYPE}
        IMPORTED )
add_library( avfilter
        ${TYPE}
        IMPORTED )
add_library( avformat
        ${TYPE}
        IMPORTED )
add_library( avutil
        ${TYPE}
        IMPORTED )
add_library( swresample
        ${TYPE}
        IMPORTED )
add_library( swscale
        ${TYPE}
        IMPORTED )
if (POSTPROC)
    add_library(postproc
            ${TYPE}
            IMPORTED )
endif (POSTPROC)


set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavcodec.${LIB_EXT} )
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavfilter.${LIB_EXT}  )
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavformat.${LIB_EXT}  )
set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavutil.${LIB_EXT}  )
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libswresample.${LIB_EXT}  )
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libswscale.${LIB_EXT}  )

if (POSTPROC)
    set_target_properties( postproc
            PROPERTIES IMPORTED_LOCATION
            ${ffmpeg_lib_path}/libpostproc.${LIB_EXT} )
    set(POSTPROCLIB postproc)
else ()
    unset(POSTPROCLIB)
endif (POSTPROC)


target_link_libraries(main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
        avformat
        avcodec
        avfilter
        avutil
        swresample
        swscale
        ${POSTPROCLIB}
        z
)







