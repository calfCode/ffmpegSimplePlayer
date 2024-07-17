//
// Created by Lenovo on 2024/7/16.
//

#ifndef SDLPROJECT_THREADBASE_H
#define SDLPROJECT_THREADBASE_H

#include <thread>
#include <atomic>

class ThreadBase
{
public:
    ThreadBase();

    virtual void run() = 0;

    void stop();

    void start();

private:
    std::thread *m_th = nullptr;

protected:
    std::atomic<bool> m_stop = {false};
};

#endif //SDLPROJECT_THREADBASE_H
