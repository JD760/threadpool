/* Copyright 2021 -- Jacob Dicken */

#ifndef SRC_POOL_H_
#define SRC_POOL_H_

#include <iostream>  // std::cout
#include <thread>  // std::thread


namespace threadpool {
class task {
 public:
    void *args;
    void *(function)(void*);
    task *next;
    task *prev;
};


typedef enum state {
    Working = 1,
    Sleeping = 2,
    Shutdown = 3,
    ForcefulShutdown =4
}state;


class pool {
 public:
    int addTask(task *task);
    int startPool(int numThreads);
    int shutdown(int mode=3);

 private:
    state poolState;

    //  task queue
    int queueLength;
    task *queueFront;
    task *queueEnd;

    //  synchronisation - mutexes
    pthread_mutex_t queueLock;
    pthread_mutex_t returnLock;

    //  threads
    pthread_t poolThread;
    pthread_t *threads;
    int numThreads;
};

}  // namespace threadpool
#endif  // SRC_POOL_H_
