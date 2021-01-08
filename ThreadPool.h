//
// Created by Mikhail on 24.12.2020.
//

#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>
#include <optional>

#include "ThreadManager.h"


class ThreadPool {
public:
    ThreadPool() :
            thread_manager(threads),
            done(false) {
        const unsigned hw_threads = std::thread::hardware_concurrency();
        for (unsigned i = 0; i < hw_threads; i++) {
            threads.push_back(std::thread(&ThreadPool::work, this));
        }
    }

    void submit(std::function<void()> f) {
        std::cout <<"submit\n";
        queue.push(f);
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> queue;
    //std::queue<std::function<RetType()>> queue; would be good
    ThreadManager thread_manager;
    bool done;

/*====================== Methods ======================*/

    void work() {
        std::cout << "work??\n";
        try {
            while (!done) {
                //std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
                //std::this_thread::sleep_for(std::chrono::seconds(1));
                // TODO replace with selfmade threadsafe queue
                if (!queue.empty()) {
                    std::cout << "work\t" << std::this_thread::get_id() << std::endl;
                    auto func = queue.front();
                    queue.pop();
                    func();
                } else {
                    std::this_thread::yield();
                }
            }
        } catch (...) {

        }
    }
};


