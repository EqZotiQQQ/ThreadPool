#include "ThreadPool.h"


ThreadPool::ThreadPool():
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

void ThreadPool::finish() {
    stop.store(true);
}

void ThreadPool::barrier() const {
    while (busy_threads_counter.load() || qsize.load()) {}
    return;
}

void ThreadPool::push(std::function<void()> task) {
    ++qsize;
    queue.push(std::move(task));
}

void ThreadPool::processor() {
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