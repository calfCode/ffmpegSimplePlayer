//
// Created by Lenovo on 2024/7/15.
//

#include <jni.h>
#include <string>
#include <unistd.h>
#include "../util/alog.h"
#include "SDL.h"

// gWindow 用于记录应用程序的窗口指针
SDL_Window *gWindow;
// gScreenSurface 用于记录窗口表面的指针
SDL_Surface *gScreenSurface;
// gHelloWorld 用于记录图像表面的指针
SDL_Surface *gCurrentSurface;
//SDL_Surface 既可以用于窗口的绘制表面，也可以用于2D 图像。本质上，窗口的绘制表面也是 2D 图像

//SDL_Surface 是 SDL 中定一个数据类型，表示 2D 图像。它包含了图像的像素数据，以及渲染图像所需所有信息。SDL_Surface 的渲染过程使用
//软件渲染算法，即使用 CPU 进行渲染。SDL 也可以利用图形硬件 GPU 渲
//染图像，然而过程和方法略显复杂


/*
为什么要使用 SDL_Surface 指针，而不是 SDL_Surface 本身呢？首先，
图像是在程序运行过程中动态申请的；其次，采用图像指针引用图像还有额
        外的好处。假如设计开发一款游戏程序，里面有一面墙由很多块相同的砖块
        组成。这时只需要创建一块砖的图像，然后重复利用它渲染整面墙即可。这
        样可以节省大量的内存开销，并且提高效率。
*/


#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 200

bool init() {
    // Initialization flag
    bool success = true;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(" SDL could not initialize ! SDL_Error : %s\n",
               SDL_GetError());
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial ",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf(" Window could not be created ! SDL_Error : %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia() {
    // Loading success flag
    bool success = true;
    // Load splash image
    //SDL_LoadBMP 以图像文件的路径作为参数，返回被载入的图像表面。如果该函数返回空指针 NULL，那么表明图像载入失败
    gCurrentSurface = SDL_LoadBMP ("/data/user/0/org.libsdl.app/app_picture/1.bmp");
    if (gCurrentSurface == NULL) {
        printf(" Unable to load image %s! SDL Error : %s\n",
               "/data/user/0/org.libsdl.app/app_picture/1.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close() {
    /*
     里调用函数 SDL_FreeSurface 释放图像 gHelloWorld。注意我们
无需处理窗口的图像表面（gScreenSurface），因为它是由 SDL 管理的资源，
SDL_DestroyWindow 函数会管它
     */
    // Deallocate surface
    SDL_FreeSurface(gCurrentSurface);
    gCurrentSurface = NULL;
    // Destroy window
    SDL_DestroyWindow(gWindow);
  //  在释放了指针所指向的资源之后，务必将指针置为 NULL，以防再次引用已经被释放的资源
    gWindow = NULL;
    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init()) {
        LOGE("init failed ");
    } else {
        if (!loadMedia()) {
            LOGE("loadMedia failed ");
        } else {

            /*
            它的第一参数 src 是被传送的表面，称为源表面；第二个参数 srcrect 指定
            图像表面中被传送的矩形域，该矩形域内的图像块将被传送。如果该参数为
            空指针 NULL，那么代表整幅图像将被传送。第三个参数是传送到达的表面，
            称为目的表面；最后一个参数指定目的表面上一个矩形域，被传送的图像块
            将被平铺在该矩形域内。如果该参数为空，那么被传送的图像将会平铺到整
            个目的表面。

             双缓存可以看作是两个图像，其中：一个是用户在窗口上看到了，称为前端缓存；另一个是程序渲染和处理的缓存，称为后端缓存


            */
            SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);


            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(5000);
        }

    }
    close();
    return 0;

}


