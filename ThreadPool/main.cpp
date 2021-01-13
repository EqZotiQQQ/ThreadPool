#include <cassert>

#include "ThreadManager.h"
#include "ThreadPool.h"

void func1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
}
void func2(int j, int &s) {
    //std::this_thread::sleep_for(std::chrono::milliseconds(250));
    s = j;
}

int main() {
    for (int i = 0; i < 100; i++) {
        ThreadPool tp;
        std::vector<int> ret(100000, 1);
        for(int i = 0; i < 100000; i++) {
            tp.push([&]() { func2(5, ret[i]); });
            tp.barrier();
        }
        for(int i = 0; i < 100000; i++) {
            assert(ret[i] == 5 && "not equalt 5");
        }

        tp.finish();
        printf("############################\t%d\n", i);
    }
    return 0;
}
