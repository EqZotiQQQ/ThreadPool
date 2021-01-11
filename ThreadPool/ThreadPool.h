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
#include <atomic>
#include <map>

#include "ThreadManager.h"
#include "FunctionWrapper.h"
#include "ThreadsafeQueue.h"

class ThreadPool {
    using task = std::function<void()>;
public:
    explicit ThreadPool() :
            thread_manager(threads),
            cv(std::condition_variable{}),
            hw_threads(1),
            //hw_threads(std::thread::hardware_concurrency()) {
            free_threads(hw_threads) {
        for (unsigned i { 0 }; i < hw_threads; i++) {
            threads.emplace_back(&ThreadPool::work, this, i);
            threads_free.push_back(true);
        }
    }

    inline bool is_threads_free() const {
        std::mutex mutex;
        std::lock_guard l(mutex);
        for(const bool thread_free : threads_free) {
            if (thread_free == false) {
                return false;
            }
        }
        return queue.empty();
    }

    void wait_until_task_finished() {
        while(true) {
            if (is_threads_free()) {
                return;
            }
        }
    }

    void submit(task f) { queue.push(f); }

    void finish() { finish_jobs.store(true); }

private:
    std::vector<std::thread> threads;
    std::vector<bool> threads_free;

    ThreadsafeQueue<task> queue;
    ThreadManager thread_manager;
    const unsigned hw_threads;
    std::atomic<unsigned> free_threads;
    std::atomic<bool> finish_jobs{false};
    std::condition_variable cv;


    void work(int thread_number) {
        while(!finish_jobs.load()) {            // we work while no signal from main thread to finish
            task action;
            if (queue.try_pop(action)) {    //queue contains things
                threads_free[thread_number] = false;
                action();
                threads_free[thread_number] = true;
            } else {                            // queue is empty
                if(queue.empty()) {  // if no tasks in queue we notify the conveyor in main thread
                    cv.notify_all();
                    std::this_thread::yield();      // let control to another thread
                }
            }

        }
    }
};