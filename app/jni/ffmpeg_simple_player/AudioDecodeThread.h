//
// Created by Lenovo on 2024/7/16.
//

#ifndef SDLPROJECT_AUDIODECODETHREAD_H
#define SDLPROJECT_AUDIODECODETHREAD_H

#include "ThreadBase.h"

struct FFmpegPlayerCtx;

class AudioDecodeThread : public ThreadBase
{
public:
    AudioDecodeThread();

    void setPlayerCtx(FFmpegPlayerCtx *ctx);

    void getAudioData(unsigned char *stream, int len);

    void run();

private:
    int audio_decode_frame(FFmpegPlayerCtx *is, double *pts_ptr);

private:
    FFmpegPlayerCtx *is = nullptr;
};

#endif //SDLPROJECT_AUDIODECODETHREAD_H
