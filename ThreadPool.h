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
#include "StacksafeQueue.h"

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
        }
    }

    inline bool get_thread_availability() const {
        bool a = std::any_of(threads_free.cbegin(), threads_free.cend(), [](const auto& element){ return !element.second;});
        return a;
    };

    void wait_until_task_finished() {
        while(true) {
            if(!get_thread_availability()) {
                for(const auto& i: threads_free) {
                    printf("thread available? = %d\n",i.second);
                }
                return;
            }
        }
    }

    void submit(task f) { queue.push(f); }

    void finish() { finish_jobs.store(true); }

    int get_free_threads_cnt() const { return free_threads; }

private:
    inline static thread_local bool thread_busy = false;
    
    std::vector<std::thread> threads;

    ThreadsafeQueueV2<task> queue;
    ThreadManager thread_manager;
    const unsigned hw_threads;
    std::atomic<unsigned> free_threads;
    std::atomic<bool> finish_jobs{false};
    std::condition_variable cv;
    std::mutex m;
    std::map<int, bool> threads_free;


    void work(int thread_number) {
        threads_free[thread_number] = true;
        while(!finish_jobs.load()) {
            task action;
            if (queue.try_pop(action)) {
                ThreadPool::thread_busy = true;
                action();
            } else {
                ThreadPool::thread_busy = false;
            }
            threads_free[thread_number] = ThreadPool::thread_busy;
            if(get_thread_availability()) {
                cv.notify_all();
                std::this_thread::yield();
            }
        }
    }
};