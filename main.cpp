#include <iostream>
#include <thread>
#include <optional>

#include "ThreadManager.h"
#include "ThreadPool.h"
#include "FunctionWrapper.h"

void func1()             {std::cout<<"func1()\n";}
int  func2(int j, int s) {std::cout<<"func2(j:i32,s:i32)\n";return j;}

struct bar {
    int x, y;
    bar(int x,int y) :x(x),y(y){}
    int operator()(){
        std::cout<<"ope()\n";
        return x+y;
    }
};

int main() {




    /*FunctionWrapper fw1(func1);
    FunctionWrapper fw2(func2);
    ThreadPool tp;
    tp.submit(fw1);
    tp.submit([&](){   fw2(5, 5);   });
    for (int i = 0; i < 10; ++i) {
        tp.submit(fw1);
        tp.submit([&](){   fw2(rand(), rand());  });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    printf("++++++++++++++++++++++\n\n");
    for (int i = 0; i < 10; ++i) {
        tp.submit(fw1);
        tp.submit([&](){   fw2(rand(), rand());  });
    }*/
    /*ThreadPool tp;
    tp.submit([](){foo();});

    bar br(5,5);
    tp.submit(br);
    tp.submit([&](){br();});*/
    return 0;
}
