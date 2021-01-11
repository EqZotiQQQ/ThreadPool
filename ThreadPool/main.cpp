#include <thread>

#include "ThreadManager.h"
#include "ThreadPool.h"
#include "FunctionWrapper.h"

using std::cout;
using std::endl;

void func1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
}
void func2(int j, int &s) {
    s = j;
}

int main() {
    for (int i = 0; i < 2; i++) {
        ThreadPool tp;
        int ret = 1;
        cout << ret << endl;


        tp.submit([&]() { func2(5, ret); });
        tp.wait_until_task_finished();
        cout << ret << endl;


        std::this_thread::sleep_for(std::chrono::seconds(1));

        tp.submit([&]() { func2(37, ret); });
        tp.wait_until_task_finished();
        cout << ret << endl;


        tp.finish();
    }
    return 0;
}
