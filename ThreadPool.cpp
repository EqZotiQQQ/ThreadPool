//
// Created by Mikhail on 24.12.2020.
//

#include "ThreadPool.h"

#include <chrono>

ThreadPool::ThreadPool() :
        thread_manager(threads),
        done(false) {
    const unsigned hw_threads = std::thread::hardware_concurrency();
    for (unsigned i = 0; i < hw_threads; i++) {

        std::cout <<"creating threads\n";
        threads.push_back(std::thread(&ThreadPool::work, this));
    }
}

void ThreadPool::work() {
    {
        std::cout <<"work??\n";
        try {
            while (!done) {
                //std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
                //std::this_thread::sleep_for(std::chrono::seconds(1));
                // TODO replace with selfmade threadsafe queue
                if (!queue.empty()) {
                    std::cout <<"work\n";
                    auto func = queue.front();
                    queue.pop();
                    func();
                } else {
                    return;
                }
            }
        } catch (...) {

        }
    }
}
