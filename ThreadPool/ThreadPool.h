#pragma once

#include <thread>
#include <vector>

#include <functional>
#include <iostream>
#include <atomic>
#include <cassert>

#include "ThreadManager.h"
#include "FunctionWrapper.h"
#include "ThreadsafeQueue.h"

class ThreadPool {
    using task = std::function<void()>;
public:
    explicit ThreadPool() :
            thread_manager(threads) {
        hw_threads = 1;
        threads_free = std::vector(hw_threads, 1);
        for (unsigned i { 0 }; i < hw_threads; i++) {
            threads.emplace_back(&ThreadPool::work, this, i);
        }
    }

    bool are_threads_free() const {
        printf("empty{%d}\tfree{%d}\n", queue.empty(), threads_free[0]);
        std::mutex mutex;
        std::lock_guard l(mutex);
        for(int i = 0; i < hw_threads; i++) {
            if(!threads_free[i]) {
                printf("empty{%d}\tfree{%d}\n", queue.empty(), threads_free[i]);
                assert(!threads_free[i] && "thread not free");
                return false;
            } else {
                assert(threads_free[i] && "thread free");
            }
        }
        return true;
    }

    void barrier() {
        while(true) {
            std::mutex m;
            std::lock_guard lock(m);
            if (are_threads_free() && queue.empty()) {
                assert(queue.empty() && "Queue is not empty");
                assert(are_threads_free() && "Threads not free");
                return;
            } else {
                std::this_thread::yield();
            }
        }
    }

    void submit(task f) {
        queue.push(f);
        printf("task pushed\n");
    }


    void finish() { finish_jobs.store(true); }

private:
    unsigned hw_threads;
    std::vector<std::thread> threads;
    std::vector<int> threads_free;

    ThreadsafeQueue<task> queue;
    ThreadManager thread_manager;
    std::atomic<bool> finish_jobs{false};

    void work(int thread_number) {
        threads_free[thread_number] = 1;
        while(!finish_jobs.load()) {            // we work while no signal from main thread to finish
            task action;
            if (queue.try_pop(action)) {    //queue contains things
                threads_free[thread_number] = 0;
                printf("task in progress\n");
                action();
                threads_free[thread_number] = 1;
                printf("task done. {%d}\n", threads_free[thread_number]);
            } else {                            // queue is empty
                if(queue.empty()) {  // if no tasks in queue we notify the conveyor in main thread
                    threads_free[thread_number] = 1;
                    std::this_thread::yield();      // let control to another thread
                }
            }


        }
    }
};