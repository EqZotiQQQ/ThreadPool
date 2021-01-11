#include <thread>
#include <future>
#include <condition_variable>

#include "ThreadManager.h"
#include "ThreadPool.h"
#include "FunctionWrapper.h"

void func1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    printf("func1()\n");
}
void func2(int j, int &s) {
    std::this_thread::sleep_for(std::chrono::milliseconds (60));
    s = j;
    printf("func2()\n");
}

int main() {
    for(int i = 0; i < 2; i++) {
        printf("=================================\n");
        ThreadPool tp;
        int ret = 1;

        tp.submit([&]() { func2(5, ret); });
        tp.wait_until_task_finished();

        printf("1. Main thread ret = {%d}; should be {5}\n", ret);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        tp.submit([&]() { func2(37, ret); });
        tp.wait_until_task_finished();

        printf("2. Main thread ret = {%d}; should be {37}\n", ret);

        tp.finish();
        printf("+++++++++++++++++++++++++++++++++++++\n");
    }
    return 0;
}
