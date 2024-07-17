
cmake_minimum_required(VERSION 3.22.1)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 ")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLOAD_BMP -DLOAD_GIF -DLOAD_LBM -DLOAD_PCX -DLOAD_PNM")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLOAD_SVG -DLOAD_TGA -DLOAD_XCF -DLOAD_XPM -DLOAD_XV")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLOAD_QOI")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshift-sign-overflow -Wstrict-prototypes -Wkeyword-macro")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-sign-compare")
#add_definitions(-DGL_GLEXT_PROTOTYPES)

add_definitions(-DLOAD_PNG)

include_directories(./)
include_directories(./android)

# General source files
file(GLOB SOURCE_FILES
        png.c
        pngerror.c
	    pngget.c
        pngmem.c
        pngpread.c
        pngread.c
        pngrio.c
        pngrtran.c
        pngrutil.c
	    pngset.c
        pngtrans.c
        pngwio.c
        pngwrite.c
        pngwtran.c
        pngwutil.c
        ./arm/arm_init.c
        ./arm/filter_neon.S
        ./arm/filter_neon_intrinsics.c
        ./arm/palette_neon_intrinsics.c
)


add_library(png SHARED ${SOURCE_FILES})


target_link_libraries(png
        # List libraries link to the target library
		z
        android
        log)
