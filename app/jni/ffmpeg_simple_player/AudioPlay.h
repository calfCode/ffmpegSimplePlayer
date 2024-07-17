//
// Created by Lenovo on 2024/7/16.
//

#ifndef SDLPROJECT_AUDIOPLAY_H
#define SDLPROJECT_AUDIOPLAY_H


#include <SDL.h>

class AudioPlay
{
public:
    AudioPlay();

    int openDevice(const SDL_AudioSpec *spec);

    void start();

    void stop();

private:
    SDL_AudioDeviceID m_devId = -1;
};


#endif //SDLPROJECT_AUDIOPLAY_H
