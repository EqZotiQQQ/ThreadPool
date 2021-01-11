cmake_minimum_required(VERSION 3.17)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ThreadPool main.cpp ThreadPool.h ThreadManager.h FunctionWrapper.h StacksafeQueue.h)