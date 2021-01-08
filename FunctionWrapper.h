//
// Created by Mikhail on 26.12.2020.
//

#pragma once

#include <tuple>
#include <iostream>
#include <any>

template<typename... Args>
class FunctionWrapperSTL {
public:
    FunctionWrapperSTL(std::function<std::any()> f, std::tuple<Args...>&& args):
            f(std::move(f)),
            args(std::forward(args)){
        printf("fw: args cnt: %d",sizeof...(Args));
    }
    auto operator()(Args... args) {
        return f(args...);
    }
private:
    std::tuple<Args...> args;
    std::function<std::any(std::tuple<Args...>)> f;
};

template<typename Function, typename... Args>
class FunctionWrapperTemplate {
public:

    FunctionWrapperTemplate(Function&& func, Args&&... args):
            f(std::forward(func)),
            args(std::forward(args)...){
        printf("fw: args cnt: %d",sizeof...(args));
    }
    auto operator()(Args... args) {
        return f(args...);
    }
private:
    Function f;
    std::tuple<Args...> args;
    std::function<std::any()> func;
};


