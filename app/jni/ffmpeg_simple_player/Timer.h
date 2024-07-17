//
// Created by Lenovo on 2024/7/16.
//

#ifndef SDLPROJECT_TIMER_H
#define SDLPROJECT_TIMER_H


#include "SDL.h"

typedef void (*TimerOutCb)();

class Timer
{
public:
    Timer();

    void start(void* cb, int interval);

    void stop();

private:
    SDL_TimerID m_timerId = 0;
};

#endif //SDLPROJECT_TIMER_H
