#include "pool.h"

#include <iostream>
#include <thread>

int threadpool::pool::addTask( threadpool::task *task) {
    if (this->queueLength != 0) {
        task->next = this->queueEnd;
        task->prev = NULL;
        this->queueEnd = task;
        this->queueLength++;
    } else {
        queueEnd = queueFront = task;
        this->queueLength++;
    }
    this->queueLength++;

    return 0;
}

int threadpool::pool::shutdown(int mode) {
    if (mode == 3) {
    this->poolState = Shutdown;
    } 
    else if (mode == 4) {
        this->poolState = ForcefulShutdown;
    }
    return 0;
}
