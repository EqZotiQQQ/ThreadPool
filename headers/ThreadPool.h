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
    ThreadPool();
    void finish();
    void barrier() const;
    void push(std::function<void()> task);
private:
    void processor();
};