cmake_minimum_required(VERSION 3.16)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

set(headers 
        headers/ThreadPool.h
        headers/ThreadManager.h
        headers/ThreadsafeQueue.h)

add_executable(ThreadPool main.cpp headers)
target_link_libraries(${PROJECT_NAME} Threads::Threads)