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
    bool quit = false;


    // SDL初始化 记住：在SDL 初始化之前，不能调用任何 SDL 函数
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        // SDL_GetError 是一个非常有用的函数。无论何时当 SDL 不正常的时候，都可以调用该函数，获取 SDL 的内部错误信息
        LOGE("SDL_Init error:%s", SDL_GetError());
        return 0;
    }
    LOGD("SDL_Init ok");
    // 创建窗口  SDL_WINDOWPOS_UNDEFINED
    window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH,
                              WIN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        LOGE("SDL_CreateWindow fail");
        return 0;
    }
    LOGD("SDL_CreateWindow ok");
    // 获取窗口表面
    surface = SDL_GetWindowSurface(window);

    if (!surface) {
        LOGE("SDL_GetWindowSurface fail");
        return 0;
    }
    LOGD("SDL_GetWindowSurface ok");
    // 在表面上填充颜色
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0X00, 0X00));
    //在窗口表面上进行绘
    //制之后，但是并不能立刻看得见所绘制的东西。为了能看见它们，还需要
    //在完成所有的绘制之后更新窗口表面。在 SDL 中更新窗口表面的函数是：
    //SDL_UpdateWindowSurface

    // 更新窗口
    SDL_UpdateWindowSurface(window);

    Uint32 exitEvent=-1;
    while (!quit) {
        /*
        根据事件队列中是否有等待处理的事件，该函数的返回值为 1 或 0。该
        函数有一个参数 e，其类型是 SDL_Event 指针。如果参数 e 不是 NULL，那
        么当事件队列中有等待处理的事件时，它从事件队列中提取最早的事件，并保存于参数 e 所指向的 SDL_Event 结构。如果参数 e 是 NULL，那么它将
        不对事件队列进行任何操作。因此，通过调用 SDL_PollEvent(NULL) 用户
        可以查询事件队列中是否有等待处理的事件
        */
        while (SDL_PollEvent(&event)) {
            LOGD("event.type=%X", event.type);
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (exitEvent!=-1){
                if (event.type == exitEvent){
                    quit = true;
                }
                exitEvent = -1;
            }
            if (event.type == SDL_KEYDOWN) {// || event.type == SDL_KEYUP){
                LOGD("event.key.keysym.scancode=%d", event.key.keysym.scancode);
                if (event.key.keysym.scancode == 40) {
                    /*
                     为了添加用户自定义的事件，首先需要调用 SDL_RegisterRvents 函数，
                    申请一个事件类型 ID。如果申请不成功，那么函数 SDL_RegisterRvents 将
                    返回一个所有二进制位都为 1 的一个整数，即 (Uint32)-1。
                     */
                    Uint32 myevent = SDL_RegisterEvents(1);//自定义事件
                    if (myevent != (Uint32) -1) {
                        exitEvent = myevent;
                        SDL_Event event;
                        SDL_memset(&event, 0, sizeof(event));
                        event.type = myevent;
                        event.user.code = 123;
                        event.user.data1 = (void *) "data1";
                        event.user.data2 = 0;
                        /*
                        事件添加成功时，该函数返回值 1；否则返回值 0。事件添加失败意味
                        着想要添加的事件被 SDL 系统过滤掉了，或者发生了内部错误。用户可以
                        调用函数 SDL_GetError 获取错误信息。常见的错误原因时事件队列已经
                        满了，无法添加更多的事件。
                         */
                        SDL_PushEvent(&event);
                    }
                }

            }
        }
    }

    // 销毁窗口
    SDL_DestroyWindow(window);

    // SDL 退出
    SDL_Quit();

    return 0;
}
