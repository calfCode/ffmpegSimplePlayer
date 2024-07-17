//
// Created by Lenovo on 2024/7/15.
//
# include "SDL.h"
#include <string>
#include <unistd.h>
#include "SDL_ttf.h"
#include "../util/alog.h"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

// gWindow 用于记录应用程序的窗口指针
SDL_Window *gWindow;
// gScreenSurface 用于记录窗口表面的指针
SDL_Surface *gScreenSurface;


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

int main ( int argc , char * argv [])
{
    if ( !init())
        return 1;

    if(TTF_Init()<0){ // 初始化TTF模块
        LOGD("TTF_Init fail:%s ",TTF_GetError());
    }
    TTF_Font *font;
    // 打开字体
    font = TTF_OpenFont("/data/user/0/org.libsdl.app/app_picture/simhei.ttf",28);
    if (font){
        LOGD("TTF_OpenFont ok");
    } else{
        LOGD("TTF_OpenFont fail:%s ",TTF_GetError());
    }


    SDL_Color sdlColor ;
    sdlColor.a = 0xff;
    sdlColor.r = 0x00;
    sdlColor.g = 0x00;
    sdlColor.b = 0xff;
//    SDL_Surface* textSurface = TTF_RenderText_Solid(font,"test",sdlColor);
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font,"中文测试",sdlColor);
    if (textSurface==NULL){
        LOGD("TTF_RenderText_Solid fail:%s ",TTF_GetError());
    }else{
        gScreenSurface = SDL_GetWindowSurface(gWindow);
        SDL_BlitSurface(textSurface, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);

    }


// Give us time to see the window .
    SDL_Delay (5000) ;
// Always be sure to clean up
    SDL_Quit () ;
    return 0;
}