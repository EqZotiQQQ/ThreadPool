#include <iostream>
#include <thread>
#include "ThreadManager.h"

#include "ThreadPool.h"
void ss() {std::cout<<"ss()\n";}

struct zz {
    void operator()() {
        std::cout << "function\n";
    }
    template<class T>//, class = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    void operator()(const T& value) {
        std::cout << value ;
    }
};

int main() {
    ThreadPool tp;
    //std::function<void()> f = ss;
    //for(int i = 0 ; i < 50; ++i)
    std::cout <<"main()\n";
    tp.submit(zz());
    //tp.submit(zz()(22));
    std::cout << "Hello, World!!\n";
    return 0;
}
