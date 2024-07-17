//
// Created by Lenovo on 2024/7/15.
//
#include <jni.h>
#include <string>
#include <unistd.h>
#include "../util/alog.h"
#include "SDL.h"

#define WIN_WIDTH 100
#define WIN_HEIGHT 200
int main(int argc, char *argv[]) {  // 为了兼容多个运行平台，SDL 要求主函数 main 的返回值类型必须为整数类型
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    int done;
    SDL_Event event;

    // SDL初始化 记住：在SDL 初始化之前，不能调用任何 SDL 函数
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret<0){
        // SDL_GetError 是一个非常有用的函数。无论何时当 SDL 不正常的时候，都可以调用该函数，获取 SDL 的内部错误信息
        LOGE("SDL_Init error:%s",SDL_GetError());
        return 0;
    }
    LOGD("SDL_Init ok");
    // 创建窗口  SDL_WINDOWPOS_UNDEFINED
    window = SDL_CreateWindow("TEST",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIN_WIDTH,WIN_HEIGHT,SDL_WINDOW_SHOWN);
    if (!window){
        LOGE("SDL_CreateWindow fail");
        return 0;
    }
    LOGD("SDL_CreateWindow ok");
    // 获取窗口表面
    surface = SDL_GetWindowSurface(window);

    if (!surface){
        LOGE("SDL_GetWindowSurface fail");
        return 0;
    }
    LOGD("SDL_GetWindowSurface ok");
    // 在表面上填充颜色
    SDL_FillRect(surface,NULL, SDL_MapRGB(surface->format,0xFF,0X00,0X00));
    //在窗口表面上进行绘
    //制之后，但是并不能立刻看得见所绘制的东西。为了能看见它们，还需要
    //在完成所有的绘制之后更新窗口表面。在 SDL 中更新窗口表面的函数是：
    //SDL_UpdateWindowSurface

    // 更新窗口
    SDL_UpdateWindowSurface(window);

    LOGD("wait 5 seconds");

    sleep(5);

    // 销毁窗口
    SDL_DestroyWindow(window);

    // SDL 退出
    SDL_Quit();

    return 0;
}

