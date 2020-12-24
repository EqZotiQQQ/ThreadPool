//
// Created by Mikhail on 24.12.2020.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>

#include "ThreadManager.h"

class ThreadPool {
public:
    ThreadPool();

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> queue;
    ThreadManager thread_manager;
    bool done;

    void work();
};


#endif //THREADPOOL_THREADPOOL_H
