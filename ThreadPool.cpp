//
// Created by Mikhail on 24.12.2020.
//

#include "ThreadPool.h"

void f() {
    std::cout << "tst\n";
}


ThreadPool::ThreadPool() :
        thread_manager(threads),
        done(false) {
    unsigned hw_threads = std::thread::hardware_concurrency();
    for (unsigned i = 0; i < hw_threads; i++) {
        //threads.push_back(std::thread(f));
        threads.push_back(std::thread());
    }
}

void ThreadPool::work() {
    {
        try {
            while (!done) {

            }
        } catch (...) {

        }
    }
}
