//
// Created by Lenovo on 2024/7/16.
//

#ifndef SDLPROJECT_VIDEODECODETHREAD_H
#define SDLPROJECT_VIDEODECODETHREAD_H

#include "ThreadBase.h"

struct FFmpegPlayerCtx;
struct AVFrame;

class VideoDecodeThread : public ThreadBase
{
public:
    VideoDecodeThread();

    void setPlayerCtx(FFmpegPlayerCtx *ctx);

    void run();

private:
    int video_entry();
    int queue_picture(FFmpegPlayerCtx *is, AVFrame *pFrame, double pts);

private:
    FFmpegPlayerCtx *playerCtx = nullptr;
};

#endif //SDLPROJECT_VIDEODECODETHREAD_H
