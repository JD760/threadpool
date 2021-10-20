/* Copyright 2021 -- Jacob Dicken */

#ifndef SRC_POOL_H_
#define SRC_POOL_H_

#include <iostream>  //std::cout
#include <thread>  // std::thread


namespace threadpool {
class task {
 public:
    void *args;
    void *(function)(void*);
 private:
    task *next;
    task *prev;
};


typedef enum state {
    Working=1,
    Sleeping=2,
    Shutdown=3
}state;


class pool {
 public:
    int numThreads;
    int addTask();
    int shutdown();

 private:
    int queueLength;
    state poolState;
    std::thread *threads;
    task *queueFront;
    task *queueEnd;
};

}  // namespace threadpool
#endif  // SRC_POOL_H_
