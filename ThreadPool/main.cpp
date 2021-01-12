#include <thread>

#include "ThreadManager.h"
#include "ThreadPool.h"
#include <cassert>
#include "FunctionWrapper.h"

using std::cout;
using std::endl;

void func1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
}
void func2(int j, int &s) {
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    s = j;
}

int main() {
    for (int i = 0; i < 20; i++) {
        ThreadPool tp;
        int ret = 1;

        tp.submit([&]() { func2(5, ret); });
        tp.barrier();
        printf("Barrier!\n");
        //assert(ret==5 && "not equalt 5");
        cout << ret << endl;
        tp.submit([&]() { func2(37, ret); });
        tp.barrier();
        printf("Barrier!\n");
        //assert(ret==37 && "not equalt 37");
        cout << ret << endl;

        tp.finish();
        cout << "############################" << i << endl;
    }
    return 0;
}
