#include <iostream>
#include <thread>
#include "ThreadManager.h"
#include "ThreadPool.h"
void ss() {}
int main() {
    ThreadPool tp;
    std::thread th(ss);
    std::cout << "Hello, World!!" << std::endl;
    th.join();
    return 0;
}
