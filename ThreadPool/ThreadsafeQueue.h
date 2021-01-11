//
// Created by Mikhail on 09.01.2021.
//

#ifndef THREADPOOL_THREADSAFEQUEUE_H
#define THREADPOOL_THREADSAFEQUEUE_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

template<class T>
class ThreadsafeQueue {
private:
    std::queue<std::shared_ptr<T>> data;
    mutable std::mutex mtx;
    std::condition_variable cv;
    std::atomic<int> size;  // can keep int, cuz of all actions under guards
public:
    ThreadsafeQueue():size(0) {}

    void push(T new_value) {
        std::shared_ptr<T> sptr(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> l(mtx);
        data.push(sptr);
        size.fetch_add(1);
        cv.notify_one();    //1
    }

    void wait_and_pop(T& value) {   //2
        std::lock_guard<std::mutex> l(mtx);
        cv.wait(l, [this]() {return !data.empty(); });
        value = std::move(*data.front());
        data.pop();
        size.fetch_sub(1);
    }

    std::shared_ptr<T> wait_and_pop() { //3
        std::lock_guard<std::mutex> l(mtx);
        cv.wait(l, [this]() {return !data.empty(); });  //4
        auto res(std::make_shared<T>(std::move(data.front())));
        data.pop();
        size.fetch_sub(1);
        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> l(mtx);
        if (data.empty()) {
            return false;
        }
        value = std::move(*data.front());
        data.pop();
        size.fetch_sub(1);
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> l(mtx);
        if (data.empty()) {
            return std::make_shared<T>();   //5
        }
        auto res = data.front();
        data.pop();
        size.fetch_sub(1);
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> l(mtx);
        return data.empty();
    }

    int len() const {
        std::lock_guard<std::mutex> l(mtx);
        return size;
    }
};

#endif //THREADPOOL_THREADSAFEQUEUE_H
