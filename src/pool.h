/* Copyright 2021 -- Jacob Dicken */

#ifndef SRC_POOL_H_
#define SRC_POOL_H_

#include <iostream>  // std::cout
#include <thread>  // std::thread


namespace threadpool {
/* Function prototypes */
int startPool();
void *workerThread(void *poolTemp);

/* structures */
typedef struct task {
    void *args;
    void *(function)(void *);
    task *next;
    task *prev;
    long id;
}task;

/* classes */

class pool {
 pool(int numThreads);

 public:
    int addTask(task *task);
    void sleep();
    int shutdown(int mode=3);

 private:
    enum poolState {
        "Working" = 1,
        "Sleeping" = 2,
    }

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
    int sleeping;
    int active;

    // conditions
    pthread_cond_t newTasks;  
};
 
}  // namespace threadpool
#endif  // SRC_POOL_H_
