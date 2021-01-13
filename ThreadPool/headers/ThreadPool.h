#pragma once

#include <thread>
#include <vector>
#include <functional>
#include <atomic>

#include "ThreadManager.h"
#include "ThreadsafeQueue.h"

class ThreadPool {
private:
    const unsigned hw_threads;
    std::vector<std::thread> threads;
    ThreadManager tm;
    ThreadsafeQueue<std::function<void()>> queue;
    std::atomic<bool> stop;
    std::atomic<int> busy_threads_counter;
    std::atomic<int> qsize;
public:
    ThreadPool():
            hw_threads(std::thread::hardware_concurrency()),
            stop(false),
            tm(threads),
            busy_threads_counter(0),
            qsize(0)
    {
        for(unsigned i = 0; i < hw_threads; ++i)
        {
            threads.emplace_back(&ThreadPool::processor, this);
        }
    }

    void finish() {
        stop.store(true);
    }

    void barrier() const {
        while(busy_threads_counter.load() != 0 || qsize.load()) {}
        return;
    }

    void push(std::function<void()> task) {
        ++qsize;
        queue.push(std::move(task));
    }

private:
    void processor() {
        while(!stop) {
            std::function<void()> task;
            if(queue.try_pop(task)) {
                ++busy_threads_counter;
                task();
                --qsize;
                --busy_threads_counter;
            } else {
                std::this_thread::yield();
            }
        }
    }
};