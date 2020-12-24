//
// Created by Mikhail on 24.12.2020.
//

#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>

#include "ThreadManager.h"

class ThreadPool {
public:
    ThreadPool();

    template<class Functor>//, class... Args>
    void submit(Functor f) {
        std::cout <<"submit\n";
        queue.push(f);
    }
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> queue;
    ThreadManager thread_manager;
    bool done;

/*====================== Methods ======================*/

    void work();
};


