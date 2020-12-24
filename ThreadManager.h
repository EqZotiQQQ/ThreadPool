//
// Created by Mikhail on 24.12.2020.
//

#pragma once

#include <thread>
#include <vector>

class ThreadManager {
public:
    ThreadManager() = delete;
    ThreadManager(std::vector<std::thread>& threads):threads(threads) {}
    ~ThreadManager() {
        for(auto& thread: threads) {
            if(thread.joinable()) {
                thread.join();
                std::cout <<"thread destroyed\n";
            }
        }
    }
private:
    std::vector<std::thread>& threads;
};

