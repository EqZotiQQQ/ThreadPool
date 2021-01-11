//
// Created by Mikhail on 26.12.2020.
//

#pragma once

#include <tuple>
#include <optional>
#include <any>



#if 0
// TODO make it workable
template<typename Function, typename... Args>
class FunctionWrapper {
public:
    FunctionWrapper(Function f, std::optional<std::tuple<Args...>>&& arguments = std::nullopt):
            f(f) {
        if (arguments.has_value()) {
            args = std::move(arguments.value());
        } else {
            args = {};
        }
    }
    std::any operator()() {
        return std::apply(f, args);
    }
private:
    Function f;
    std::tuple<Args...> args;
};

//invoke_result?

#endif