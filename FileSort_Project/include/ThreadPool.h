#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <pthread.h>
#include <stdexcept>

// 定义一个回调函数作为任务类型
typedef void (*TaskFunction)(void*);

// 定义用于表示任务的结构体
struct Task {
    TaskFunction function;
    void* arg;
};

class ThreadPool {
public:
    ThreadPool(size_t numThreads);  // 初始化线程
    ~ThreadPool();  // 销毁线程
    void enqueue(TaskFunction function, void* arg);  // 将任务加入到任务队列
    
private:
    std::vector<pthread_t> workers;  // 存储线程的数组
    std::queue<Task> tasks;           // 任务队列
    pthread_mutex_t queueMutex;        // 线程互斥锁，保护任务队列
    pthread_cond_t condition;         // 条件变量，用于线程同步
    bool stop;                        // 是否关闭线程池

    static void* workerThread(void* arg);   // 线程执行函数
    void run(); // 从队列中取出并执行任务
};

#endif