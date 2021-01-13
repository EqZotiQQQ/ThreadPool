#pragma once

#include <thread>
#include <vector>

class ThreadManager {
public:
    ThreadManager(std::vector<std::thread>& threads):threads(threads) {}
    ~ThreadManager() {
        for(auto& thread: threads) {
            if(thread.joinable()) {
                thread.join();
            }
        }
    }
private:
    std::vector<std::thread>& threads;
};

