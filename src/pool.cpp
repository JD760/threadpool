#include "pool.h"

#include <iostream>
#include <thread>


/* 
 * Create the threadpool
 * Creates a new thread in which to execute the threadpool else
 * the ability to control the pool would be lost 
 * when started, pool waits for tasks and a subsequent start execution
 * signal before beginning task processing
*/

threadpool::pool::pool(int numThreads) {  // constructor
    this->poolState = Sleeping;
    
    /* Set up mutexes */
    pthread_mutex_init(&this->queueLock, NULL);
    pthread_mutex_init(&this->returnLock, NULL);

    /* set up task queue */
    this->queueEnd = this->queueFront = NULL;
    this->queueLength = 0;

    /* set up conditions */
    pthread_cond_init(&this->newTasks, NULL);

    /* create the threads and start worker functions in sleep state */
    this->threads = (pthread_t *) std::malloc(sizeof(pthread_t) * numThreads);
    for (int i = 0; i < numThreads; i++) {
        pthread_create(
                &this->threads[i], NULL, threadpool::workerThread, (void *)this
        );
    }
    return;
}

 int threadpool::startPool() {
     return 0;
 }

void threadpool::pool::sleep() {
    this->poolState = Sleeping;
};

int threadpool::pool::addTask( threadpool::task *task) {
    if (this->queueLength != 0) {
        task->next = this->queueEnd;
        task->prev = NULL;
        this->queueEnd = task;
        task->id = task->prev->id + 1;
    } else {
        queueEnd = queueFront = task;
        task->id = 1;
    }
    this->queueLength++;
    
    std::cout << this->queueLength;
    return 0;
}

void *threadpool::workerThread(void *poolTemp) {
    threadpool::pool *pool = (threadpool::pool *)poolTemp;
    return NULL;
}

