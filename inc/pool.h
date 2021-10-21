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


typedef enum state {
    Working = 1,
    Sleeping = 2,
    Shutdown = 3,
    ForcefulShutdown = 4
}state;

/* classes */

class pool {
 pool(int numThreads);

 public:
    int addTask(task *task);
    void sleep();
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

    // conditions
    pthread_cond_t newTasks;  
};
 
}  // namespace threadpool
#endif  // SRC_POOL_H_
