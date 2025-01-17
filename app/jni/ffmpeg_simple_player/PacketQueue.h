//
// Created by Lenovo on 2024/7/16.
//

#ifndef SDLPROJECT_PACKETQUEUE_H
#define SDLPROJECT_PACKETQUEUE_H


#include <list>
#include <atomic>

#ifdef __cplusplus
extern "C" {
#include <libavcodec/avcodec.h>
#include <SDL.h>
}
#endif

class PacketQueue
{
public:
    PacketQueue();

    int packetPut(AVPacket *pkt);

    int packetGet(AVPacket *pkt, std::atomic<bool> &quit);

    void packetFlush();

    int packetSize();

private:
    std::list<AVPacket> pkts;
    std::atomic<int> size = {0};
    SDL_mutex *mutex = nullptr;
    SDL_cond *cond = nullptr;
};


#endif //SDLPROJECT_PACKETQUEUE_H
