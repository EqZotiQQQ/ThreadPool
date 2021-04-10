cmake_minimum_required(VERSION 3.16)

project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

find_package(Threads REQUIRED)

set(HEADERS
        headers/ThreadPool.h
        headers/ThreadManager.h
        headers/ThreadsafeQueue.h)

set(SOURCES src/ThreadPool.cpp)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_library(ThreadPool STATIC ${HEADERS} ${SOURCES})

target_link_libraries(ThreadPool PUBLIC Threads::Threads)






set(CMAKE_CXX_CPPCHECK "cppcheck")

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

if (CMAKE_CXX_CPPCHECK)
    list(
            APPEND CMAKE_CXX_CPPCHECK
            "--enable=warning"
            "--inconclusive"
            "--force"
            "--inline-suppr"
    )
endif()